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

	//COMPLETAR utilizando el interfaz del puerto G de gpio.h debemos leer los
	//pines 6 y 7 del puerto G (portG_read) debemos devolver un valor (buttons)
	//en el que el bit 0 (el menos significativo) representa el estado del botón
	//del pin 6 y el bit 1 representa el estado del botón del pin 7 (a 1 si
	//están pulsados a 0 si no lo están).

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


