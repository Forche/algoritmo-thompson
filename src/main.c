#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
;
char ** lista_palabras = NULL;
int cantidad_palabras = 0;
char tabla_transiciones[ROWS][COLS] = {
	{'-','0','1','2','3','4','5','6','7','8','9','.','F',OTHER_CHARACTER},
	{'0','1','1','1','1','1','1','1','1','1','1','6','6','6'},
	{'1','2','2','2','2','2','2','2','2','2','2','3','5','6'},
	{'2','2','2','2','2','2','2','2','2','2','2','6','5','6'},
	{'3','4','4','6','6','6','6','6','6','6','6','6','6','6'},
	{'4','5','5','6','6','6','6','6','6','6','6','6','6','6'},
	{'5','6','6','6','6','6','6','6','6','6','6','6','6','6'},
	{'6','6','6','6','6','6','6','6','6','6','6','6','6','6'},
};

int main(int argc, char *argv[]) {

    imprimir(tabla_transiciones);

	char buffer_palabra[30];
	int contador_caracter_palabra = 0;
	//Vacio memoria del array de palabras.
	memset( buffer_palabra, '\0', sizeof(buffer_palabra));

	char line[1024];
	printf("Ingrese cadena a evaluar (Centinela #) o '-' para salir:");
	scanf("%1023[^\n]", line);
	getchar();
	while(line[0] != '-') {
		printf("Entrada %s\n\n", *++argv);
		char estado_actual = '0';
		char caracter = '\0';
		int iteracion;
		for (iteracion = 0; iteracion < strlen(line); ++iteracion) {
			caracter = (line)[iteracion];
			if(caracter == CENTINELA) {
				if(estado_actual==ESTADO_ACEPTACION) {
					printf("\nReconoci palabra: %s, Longitud %d\n\n",buffer_palabra ,strlen(buffer_palabra));
					agregar_palabra(buffer_palabra);
				}
				memset( buffer_palabra, '\0', sizeof(buffer_palabra));
				contador_caracter_palabra = 0;
				estado_actual = '0';
				continue;
			}

			buffer_palabra[contador_caracter_palabra]=caracter;
			estado_actual = buscar_nuevo_estado(estado_actual,caracter);
			imprimir_caracter_y_estado(iteracion, caracter,estado_actual);
			contador_caracter_palabra++;
			contador_caracter_palabra = (estado_actual=='0') ? 0 : contador_caracter_palabra;
		}

		if(estado_actual==ESTADO_ACEPTACION){
			printf("\nReconoci palabra: %s, Longitud %d\n\n",buffer_palabra ,strlen(buffer_palabra));
			agregar_palabra(buffer_palabra);
		}
		memset( buffer_palabra, '\0', sizeof(buffer_palabra));
		contador_caracter_palabra = 0;
		estado_actual = 0;
		mostrar_palabras_reconocidas();
		liberar_recursos();
		printf("Ingrese cadena a evaluar (Centinela #) o '-' para salir:");
		scanf("%1023[^\n]", line);
		getchar();
	}
	liberar_recursos();
	printf("\nFin");
	return EXIT_SUCCESS;
}

void imprimir(char tabla[ROWS][COLS]){
	puts("<------TABLA TRANSICIONES------>");
	int i,j;
	for (i = 0; i < ROWS; ++i) {
		for (j = 0; j < COLS; ++j) {
			printf("%c ",tabla[i][j]);
		}
		puts("");
	}
	puts("<------FIN TABLA TRANSICIONES------>\n");
}

void imprimir_caracter_y_estado(char contador,char caracter, char estado) {
	printf("Caracter %d: %c Estado Actual: %c\n", contador, caracter,estado);
}

int obtener_row(char estado_actual) {
	return (estado_actual - '0') + 1;
}

int obtener_col(char caracter_leido) {
	int var;
	for (var = 0; var < COLS; ++var) {
		if(tabla_transiciones[0][var] == caracter_leido){
			return var;
		}
	}
	return tabla_transiciones[0][OTHER_CHARACTER];
}

char buscar_nuevo_estado(char estado_actual,char caracter_leido) {
	int row_number = obtener_row(estado_actual);
	int col_number = obtener_col(caracter_leido);
	return tabla_transiciones[row_number][col_number];
}


void agregar_palabra(char *palabra) {
	cantidad_palabras++;
	lista_palabras = (char**)realloc(lista_palabras, cantidad_palabras * sizeof(char *));
	lista_palabras[cantidad_palabras-1] = strdup(palabra);
}

void mostrar_palabras_reconocidas() {
	puts("\nPalabras Encontradas:\n");
	int i;
    for(i=0;i<cantidad_palabras;i++)
    {
        printf("%d palabra: %s\n",i+1,lista_palabras[i]);
    }
}

void liberar_recursos() {
	int i;
    for(i=0;i<cantidad_palabras;i++)
    {
    	memset(lista_palabras[i], '\0', sizeof(lista_palabras[i]));
    }
    cantidad_palabras = 0;
}
