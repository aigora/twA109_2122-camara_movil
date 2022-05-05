#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "SerialClass/SerialClass.h"

#define MAX_BUFFER 200
#define PAUSA_MS 200 

int Enviar_y_Recibir(Serial* Arduino, const char* mensaje_enviar, char* mensaje_recibir);

int main(void) {

	Serial* Arduino;
	char puerto[] = "COM4"; // Puerto serie al que está conectado Arduino
	int opcion_menu;
	setlocale(LC_ALL, "es-ES");
	Arduino = new Serial((char*)puerto);



	return 0;
}



int Enviar_y_Recibir(Serial* Arduino, const char* mensaje_enviar, char* mensaje_recibir)
{
 int bytes_recibidos=0,total=0;
 int intentos = 0,fin_linea=0;
 Arduino->WriteData((char *)mensaje_enviar,strlen(mensaje_enviar));
 Sleep(PAUSA_MS);
 bytes_recibidos = Arduino->ReadData(mensaje_recibir,sizeof(char)*MAX_BUFFER-1);
 while ((bytes_recibidos > 0 || intentos < 5) && fin_linea==0)
 {
 if (bytes_recibidos > 0)
 {
 total += bytes_recibidos;
 if (mensaje_recibir[total - 1] == 13 || mensaje_recibir[total - 1] == 10)
 fin_linea = 1;
 }
 else
 intentos++;
 Sleep(PAUSA_MS);
 bytes_recibidos = Arduino->ReadData(mensaje_recibir+total, sizeof(char)*MAX_BUFFER-1);
 }
 if (total > 0)
 mensaje_recibir[total - 1] = '\0';
 return total;
} 
