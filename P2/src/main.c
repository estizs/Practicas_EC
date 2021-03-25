#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "gpio.h"

struct RLstat {
	int moving;
	int speed;
	int iter;
	int direction;
	int position;
	int contador;
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.iter = 0,
	.direction = 0,
	.position = 0,
	.contador = 0,
};

int setup(void)
{
	leds_init();
	D8Led_init();
	D8Led_segment(RL.position);

	/* Port G: configuraci�n para espera activa */

	//COMPLETAR: utilizando el interfaz para el puerto G definido en gpio.h hay
	//que configurar los pines 6 y 7 del puerto G como pines de entrada y
	//activar las correspondientes resistencias de pull-up
	
	// Pines 6 y 7 como input
	portG_conf(6, INPUT);
	portG_conf(7, INPUT);
	// Activar pull-up
	portG_conf_pup(6, ENABLE);
	portG_conf_pup(7, ENABLE);

	/*******************************************/

	Delay(0);
	return 0;
}

int loop(void)
{
	unsigned int buttons = read_button();

	if (buttons & BUT1) {
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// hay que apagar ambos leds
		// Tambi�n hay que conmutar la direcci�n del movimiento del led rotante
		// representado por el campo direction de la variable RL

		// Apagamos los leds
		led1_off();
		led2_off();
		// Invertimos la direcci�n del RL
		if(RL.direction) RL.direction = 0;
		else RL.direction = 1;
	}

	if (buttons & BUT2) {
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// Incrementar contador de pulsaciones. Si es par, conmutar led1. Si es impar, conmutar el led2.
		// Tambi�n hay que comutar el estado de movimiento del led rotante
		// representado por el campo moving de la variable RL, y en caso de
		// ponerlo en marcha debemos reiniciar el campo iter al valor del campo
		// speed.
		++RL.contador;
		if(RL.contador % 2 == 0) // Si este es par entonces conmuto el LED1
			led1_switch();
		else // Si es impar conmuto LED2
			led2_switch();
		// Conmuto el campo moving
		if(RL.moving) RL.moving = 0;
		else RL.moving = 1;
		// Si se pone en marcha reset a iter con el valor por defecto de speed
		if(RL.moving)
			RL.iter = RL.speed;
	}

	if (RL.moving) {
		RL.iter--;
		if (RL.iter == 0) {
			// COMPLETAR: debemos hacer avanzar el led rotante una posici�n en
			// la direcci�n indicada por el campo direction de la variable RL.
			// La posici�n actual est� representada en el campo position.
			// Recordar que queremos un movimiento circular, representado por
			// las 6 primeras posiciones en el array Segmentes del display de 8
			// segmentos, por lo que position debe estar siempre entre 0 y 5.
			
			// Como queremos que sea circular entonces tenemos que hacerlo m�dulo el tama�o
			// La f�rmula general (independientemente de la direcci�n) es: pos = (pos+/-1) % 5;
			// Si la direcci�n es 0 => sentido antihorario entonces es pos - 1
			// En cambio si la direcci�n es 1 => sentido horario por lo que pos + 1
			if(RL.direction) ++RL.position;
			else --RL.position;
			if(RL.position < 0) RL.position = 5;
			if(RL.position > 5) RL.position = 0;
			RL.iter = RL.speed;
		}
	}
	D8Led_segment(RL.position);
	Delay(2000); // espera de 200ms para que el bucle se repita 5 veces por segundo
	return 0;
}


int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
