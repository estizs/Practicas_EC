/*-------------------------------------------------------------------
**
**  Fichero:
**    button.c  10/6/2014
**
**    Estructura de Computadores
**    Dpto. de Arquitectura de Computadores y Automï¿½tica
**    Facultad de Informï¿½tica. Universidad Complutense de Madrid
**
**  Propï¿½sito:
**    Contiene las implementaciones de las funciones
**    para la gestiï¿½n de los pulsadores de la placa de prototipado
**
**  Notas de diseï¿½o:
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

	//COMPLETAR: tomar el cÃ³digo de prÃ¡cticas anteirores
	// Leemos la señal digital recibida en el pin 6
		portG_read(6, &val);
		// Si el botón está pulsado (a LOW) entonces lo señalamos en buttons y lo mismo para
		// el otro botón
		if(val == LOW)
			buttons = buttons | (0x1);
		else
			buttons = buttons & ~(0x1);
		// Leemos la señal digital recibida en el pin 7
		portG_read(7, &val);
		if(val == LOW)
			buttons = buttons | (0x1 << 1);
		else
			buttons = buttons & ~(0x1 << 1);

	return buttons;
}


