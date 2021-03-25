/*-------------------------------------------------------------------
**
**  Fichero:
**    intcontroller.c  3/3/2016
**
**    Estructura de Computadores
**    Dpto. de Arquitectura de Computadores y Automática
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Contiene las implementación del módulo intcontroller
**
**-----------------------------------------------------------------*/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "intcontroller.h"

void ic_init(void)
{
	/* Configuraci�n por defecto del controlador de interrupciones:
	 *    Lineas IRQ y FIQ no habilitadas
	 *    Linea IRQ en modo no vectorizado
	 *    Todo por la l�nea IRQ
	 *    Todas las interrupciones enmascaradas
	 **/
	rINTMOD = 0x0; // Configura las linas como de tipo IRQ
	rINTCON = 0x7; // IRQ y FIQ enmascaradas, IRQ en modo no vectorizado
	rINTMSK = ~(0x0); // Enmascara todas las lineas
}

int ic_conf_irq(enum enable st, enum int_vec vec)
{
	int conf = rINTCON;

	if (st != ENABLE && st != DISABLE)
		return -1;

	if (vec == VEC)
		//COMPLETAR: poner la linea IRQ en modo vectorizado
		// bit[2] = 0 => habilitar modo vectorizado
		// bit[1] = 1 => deshabilitar l�nea IRQ
		// bit[0] = 1 => deshabilitar l�nea FIQ
		// 0x1 << 2 = 100 => ~(0x1 << 2) = 011
		// 111 & 011 = 011
		conf = conf & ~(0x1 << 2);

	else {
		//COMPLETAR: poner la linea IRQ en modo no vectorizado
		// bit[2] = 1
		// bit[1] = 0
		// bit[0] = 1
		// 101 = 0x5
		// (0x1 << 2) = 100
		// 111 | 100 = 111
		// (0x1 << 1) = 010 => ~(0x1 << 1) = 101
		// 111 & 101 = 101
		conf = conf | (0x1 << 2);
		conf = conf & ~(0x1 << 1);
	}

	if (st == ENABLE)
		//COMPLETAR: habilitar la linea IRQ
		// bit[2] = 1
		// bit[1] = 0
		// bit[0] = 1
		conf = conf & ~(0x1 << 1);
	else
		//COMPLETAR: deshabilitar la linea IRQ
		conf = conf | (0x1 << 1);

	rINTCON = conf;
	return 0;
}

int ic_conf_fiq(enum enable st)
{
	int ret = 0;

	if (st == ENABLE)
		//COMPLETAR: habilitar la linea FIQ
		// la l�nea FIQ es el bit menos significativo
		// para habilitar tiene que estar a 0
		ret = ret & ~(0x1 << 0);
	else if (st == DISABLE)
		//COMPLETAR: deshabilitar la linea FIQ
		ret = ret | (0x1 << 0);
	// es necesario poner el << 0? supongo que no
	else
		ret = -1;

	return ret;
}

int ic_conf_line(enum int_line line, enum int_mode mode)
{
	unsigned int bit = INT_BIT(line);

	if (line < 0 || line > 26)
		return -1;

	if (mode != IRQ && mode != FIQ)
		return -1;
	/*
	INTMOD Interrupt Mode Register (0x01E00008). Registro con un bit por l�nea: a �0�
	para que active IRQ o a �1� para que active FIQ.
	*/
	if (mode == IRQ)
		//COMPLETAR: poner la linea line en modo IRQ
		rINTMOD = rINTMOD & ~(0x1 << line);

	else
		//COMPLETAR: poner la linea line en modo FIQ
		rINTMOD = rINTMOD | (0x1 << line);

	return 0;
}

int ic_enable(enum int_line line)
{
	if (line < 0 || line > 26)
		return -1;

	//COMPLETAR: habilitar las interrupciones por la linea line
	/*
	INTMSK Interrupt Mask Register (0x01E0000C). Registro con 28 bits. El bit 27 est�
	reservado. El bit 26 permite enmascarar todas las l�neas (m�scara global). El resto
	de los bits, uno por l�nea, cuando toman valor �0� habilitan la interrupci�n de la l�nea
	correspondiente y cuando toman valor �1� la enmascaran.
	*/
	rINTMSK = rINTMSK & ~(0x1 << line);
	// se llama desde fuera con el valor line = 26
	//rINTMSK = rINTMSK & ~(0x1 << 26);

	return 0;
}

int ic_disable(enum int_line line)
{
	if (line < 0 || line > 26)
		return -1;

	//COMPLETAR: enmascarar las interrupciones por la linea line
	rINTMSK = rINTMSK | (0x1 << line);
	
	return 0;
}

int ic_cleanflag(enum int_line line)
{
	int bit;

	if (line < 0 || line > 26)
		return -1;

	bit = INT_BIT(line);

	if (rINTMOD & bit)
		//COMPLETAR: borrar el flag de interrupcion correspondiente a la linea line
		//con la linea configurada por FIQ
		// se borra poniendo un 1
		rF_ISPC = rF_ISPC | (0x1 << line);

	else
		//COMPLETAR: borrar el flag de interrupcion correspondiente a la linea line
		//con la linea configurada por IRQ
		rI_ISPC = rI_ISPC | (0x1 << line);
	return 0;
}



