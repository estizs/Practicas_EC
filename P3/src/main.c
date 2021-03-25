#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "intcontroller.h"
#include "timer.h"
#include "gpio.h"
#include "keyboard.h"

struct RLstat {
	int moving;
	int speed;
	int direction;
	int position;
	int contador;
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.direction = 0,
	.position = 0,
	.contador = 0,
};

void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void button_ISR(void) __attribute__ ((interrupt ("IRQ")));
void keyboard_ISR(void) __attribute__ ((interrupt ("IRQ")));

void timer_ISR(void)
{
	//COMPLETAR: tomar el c�digo de avance de posici�n del led rotante de la pr�ctica anterior
	if(RL.direction) ++RL.position;
	else --RL.position;
	if(RL.position < 0) RL.position = 5;
	if(RL.position > 5) RL.position = 0;

	D8Led_segment(RL.position);
}

void button_ISR(void)
{
	unsigned int whicheint = rEXTINTPND;
	unsigned int buttons = (whicheint >> 2) & 0x3;

	//COMPLETAR: usar el c�digo de la primera parte parte de atenci�n a los
	//pulsadores
	if (buttons & BUT1) {
		// Apagamos los leds
		led1_off();
		led2_off();
		// Invertimos la direcci�n del RL
		if(RL.direction) RL.direction = 0;
		else RL.direction = 1;
		}

	if (buttons & BUT2) {
		++RL.contador;
		if(RL.contador % 2 == 0) // Si este es par entonces conmuto el LED1
			led1_switch();
		else // Si es impar conmuto LED2
			led2_switch();
		// Conmuto el campo moving
		if(RL.moving) RL.moving = 0;
		else RL.moving = 1;
	}
	// eliminamos rebotes
	Delay(2000);
	// borramos el flag en extintpnd
	//COMPLETAR: debemos borrar las peticiones de interrupci�n en
			         //EXTINTPND escribiendo un 1 en los flags que queremos borrar (los
					 //correspondientes a los pulsadores pulsados)
	rEXTINTPND = rEXTINTPND | (0x1 << buttons);
}

// NO HAY QUE HACERLA
void keyboard_ISR(void)
{
	int key;

	/* Eliminar rebotes de presi�n */
	Delay(200);
	
	/* Escaneo de tecla */
	key = kb_scan();

	if (key != -1) {
		/* Visualizacion en el display */
		//COMPLETAR: mostrar la tecla en el display utilizando el interfaz
		//definido en D8Led.h

		switch (key) {
			case 0:
				//COMPLETAR: poner en timer0 divisor 1/8 y contador 62500
				break;
			case 1:
				//COMPLETAR: poner en timer0 timer divisor 1/8 y contador 31250
				break;
			case 2:
				//COMPLETAR: poner en timer0 timer divisor 1/8 y contador 15625
				break;
			case 3:
				//COMPLETAR: poner en timer0 timer divisor 1/4 y contador 15625
				break;
			default:
				break;
		}
		
		/* Esperar a que la tecla se suelte, consultando el registro de datos */
		//while (/*COMPLETAR: true si est� pulsada la tecla (leer del registro rPDATG)*/);
	}

    /* Eliminar rebotes de depresi�n */
    Delay(200);
     
    /* Borrar interrupciones pendientes */
	//COMPLETAR
	//borrar la interrupci�n por la l�nea EINT1 en el registro rI_ISPC
}

int setup(void)
{
	leds_init();
	D8Led_init();
	D8Led_segment(RL.position);

	/* Port G: configuraci�n para generaci�n de interrupciones externas,
	 *         botones y teclado
	 **/

	//COMPLETAR: utilizando el interfaz para el puerto G definido en gpio.h
	//configurar los pines 1, 6 y 7 del puerto G para poder generar interrupciones
	//externas por flanco de bajada por ellos y activar las correspondientes
	//resistencias de pull-up.

	// para generar interrupciones internas
	portG_conf(1, EINT);
	portG_conf(6, EINT);
	portG_conf(7, EINT);

	// flanco de bajada
	portG_eint_trig(1, FALLING);
	portG_eint_trig(6, FALLING);
	portG_eint_trig(7, FALLING);

	// activar resistencias pull-up
	portG_conf_pup(1, ENABLE);
	portG_conf_pup(6, ENABLE);
	portG_conf_pup(7, ENABLE);


	/********************************************************************/

	/* Configuraci�n del timer */

	//COMPLETAR: tomar el c�digo de la segunda parte

	if (RL.moving)
		tmr_start(TIMER0);
	/***************************/

	// Registramos las ISRs
	//COMPLETAR: registrar la RTI del timer
	pISR_TIMER0 = timer_ISR;
	//COMPLETAR: registrar la RTI de los botones
	pISR_EINT4567 = button_ISR;
	//pISR_EINT1    = //COMPLETAR: registrar la RTI del teclado

	/* Configuraci�n del controlador de interrupciones
	 * Habilitamos la l�nea IRQ, en modo vectorizado
	 * Configuramos el timer 0 en modo IRQ y habilitamos esta l�nea
	 * Configuramos la l�nea EINT4567 en modo IRQ y la habilitamos
	 * Configuramos la l�nea EINT1 en modo IRQ y la habilitamos
	 */

	ic_init();
	//COMPLETAR: utilizando el interfaz definido en intcontroller.h
	//		habilitar la l�nea IRQ en modo vectorizado
	//		deshabilitar la l�nea FIQ
	//		configurar la l�nea INT_TIMER0 en modo IRQ
	//		configurar la l�nea INT_EINT4567 en modo IRQ
	//		configurar la l�nea INT_EINT1 en modo IRQ
	//		habilitar la l�nea INT_TIMER0
	//		habilitar la l�nea INT_EINT4567
	//		habilitar la l�nea INT_EINT1

	/***************************************************/
	ic_conf_irq(ENABLE, VEC);
	ic_conf_fiq(DISABLE);
	ic_conf_line(INT_TIMER0, IRQ);
	ic_conf_line(INT_EINT4567, IRQ);
	ic_conf_line(INT_EINT1, IRQ);
	// habilitamos la l�nea 26 aqu� fuera si no puede que no funcione
	ic_enable(INT_GLOBAL);
	ic_enable(INT_TIMER0);
	ic_enable(INT_EINT4567);
	ic_enable(INT_EINT1);

	Delay(0);
	return 0;
}

int loop(void)
{
	return 0;
}


int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
