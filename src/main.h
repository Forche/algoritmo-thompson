#ifndef MAIN_H_
#define MAIN_H_
#define ROWS 8
#define COLS 14
#define ESTADO_ACEPTACION '5'
#define OTHER_CHARACTER 'o'
#define CENTINELA '#'


void imprimir(char tabla[ROWS][COLS]);
void imprimir_caracter_y_estado(char contador,char caracter, char estado);
int obtener_row(char estado_actual);
int obtener_col(char caracter_leido);
char buscar_nuevo_estado(char estado_actual,char caracter_leido);
void agregar_palabra(char *palabra);
void mostrar_palabras_reconocidas();
void liberar_recursos();s


#endif /* MAIN_H_ */
