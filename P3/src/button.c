/*-------------------------------------------------------------------
**
**  Fichero:
**    button.c  10/6/2014
**
**    Estructura de Computadores
**    Dpto. de Arquitectura de Computadores y Autom�tica
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las implementaciones de las funciones
**    para la gesti�n de los pulsadores de la placa de prototipado
**
**  Notas de dise�o:
**
**-----------------------------------------------------------------*/

#include "44b.h"
#include "utils.h"
#include "button.h"
#include "leds.h"
#include "gpio.h"

unsigned int read_button(void)
{
	unsigned int buttons = 0;
	enum digital val;

	//COMPLETAR: tomar el código de prácticas anteirores
	// Leemos la se�al digital recibida en el pin 6
		portG_read(6, &val);
		// Si el bot�n est� pulsado (a LOW) entonces lo se�alamos en buttons y lo mismo para
		// el otro bot�n
		if(val == LOW)
			buttons = buttons | (0x1);
		else
			buttons = buttons & ~(0x1);
		// Leemos la se�al digital recibida en el pin 7
		portG_read(7, &val);
		if(val == LOW)
			buttons = buttons | (0x1 << 1);
		else
			buttons = buttons & ~(0x1 << 1);

	return buttons;
}


