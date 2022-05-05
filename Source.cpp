#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "SerialClass/SerialClass.h"

#define MAX_BUFFER 200
#define PAUSA_MS 200 


int main(void) {

	Serial* Arduino;
	char puerto[] = "COM4"; // Puerto serie al que está conectado Arduino
	int opcion_menu;
	setlocale(LC_ALL, "es-ES");
	Arduino = new Serial((char*)puerto);



	return 0;
}