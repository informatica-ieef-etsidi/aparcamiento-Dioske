#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#define Nplazas 20

char menu();
int confirmacion();
int login();
int esDigitoValido(char caracter);
int esLetraValida(char caracter);
int esMatriculaValida(char matricula[]);
int existeUsuario(struct usuario usuarioValido, char username[], char password[]);

/////////////////////////////////////////////////////////////////////////////////////////          MAIN          ////////////////////////////////////////////////////////////////////////////////////////////


void main() {
	FILE * parking;
	errno_t parking_error404;

	int mfreeseats = 0, cfreeseats = 0, state = 1, random, i;
	char opcion, tipo, matric[8], vector[30], aux[30];

	struct Plaza {
		int estado;
		char tipo;
		char matricula[8];
	};
	struct usuario {
		char nickname[50];
		char password[50];
	};
	struct usuario user;
	struct Plaza plaza[Nplazas];

	// Usuario: admin		Password: password

	for (i = 0; i <= Nplazas/4; i++) {
		plaza[i].estado = 0;
		if (plaza[i].estado == 0)
			mfreeseats++;
	}
	for (i; i <= Nplazas; i++) {
		plaza[i].estado = 0;
		if (plaza[i].estado == 0)
			cfreeseats++;
	}

	parking_error404 = fopen_s(&parking, "parking.txt", "r");
	fclose(parking);

	if (parking_error404 != 0) {
		printf("No se ha podido abrir el registro del parking\n");
		Sleep(1500);
	}

	system("cls");

	while (state == 1) {
		int conf;
		printf("Register - R\t Login - L\n");
		scanf_s("%c", &opcion);
		getchar();

		if (opcion >= 'a' && opcion <= 'z')
			opcion -= 32;

		switch (opcion) {
		case 'R':
			printf("Introduzca su usuario\n");
			gets(vector);
			printf("Es este su usuario %s?\n", vector);
			conf = confirmacion();
			if (conf == 0) {
				fopen_s(&parking, "parking.txt", "a");
				fprintf_s(parking, "%s", vector);
			}

			else break;
			printf("Introduzca su contraseña\n");
			gets(vector);
			printf("Es esta su contraseña %s?\n\t Y  -  N", vector);
			conf = confirmacion();
			if (conf == 0) {
				fprintf_s(parking, "|");
				fprintf_s(parking, "%s", vector);
				fclose(parking);
				state = 0;
			}
			break;

		case 'L':
			printf("Introduzca su usuario");
			scanf_s("%s", user.nickname, 50);

			printf("Introduzca la contraseña");
			scanf_s("%s", user.password, 50);

			login(parking, user.nickname, user.password);

		default:
			printf("Opcion no valida");
			Sleep(1000);
			system("cls");
		}
	}

	state = 1;
	while (state == 1) {

		opcion = menu();

		switch (opcion) {

		case 'R':
			printf("Es su vehiculo un coche(C) o una moto(M)?\n");
			scanf_s("%c", &tipo);
			getchar();

			if (tipo >= 'a' && tipo <= 'z')
				tipo -= 32;

			switch (tipo) {
			case 'C':
				if (cfreeseats != 0) {
					int locker = 1;
					while (locker == 1) {
						srand(time(NULL));
						random = ceil ( (Nplazas / 4) + rand() % (Nplazas - (Nplazas/4)));
						if (plaza[random].estado == 0) {
							plaza[random].estado = 1;
							plaza[random].tipo = tipo;
							printf("Introduzca su numero de matricula por favor\n");
							scanf_s("%s", &plaza[random].matricula, 7);
							getchar();
							printf("Se le ha asignado la plaza %d\n", random);
							cfreeseats--;
							locker = 0;
						}
					}
				}
				else
					printf("No quedan plazas de coches libres\n");
				break;

			case 'M':
				if (mfreeseats != 0) {
					int locker = 1;
					while (locker == 1) {
						srand(time(NULL));
						random = rand() % (Nplazas / 4);
						if (plaza[random].estado == 0) {
							plaza[random].estado = 1;
							plaza[random].tipo = tipo;
							printf("Introduzca su numero de matricula por favor\n");
							scanf_s("%s", &plaza[random].matricula, 7);
							getchar();
							printf("Se le ha asignado la plaza %d\n", random);
							mfreeseats--;
							locker = 0;
						}
					}
				}
				else
					printf("No quedan plazas de motos libres\n");
				break;
			default:
				printf("No se reconoce la opccion seleccionada.\nIntroduzca una de las opciones listadas por favor.\n");
				break;
			}

			Sleep(1500);
			system("cls");
			break;

		case 'A':
			if (mfreeseats == 0 && cfreeseats == 0) {
				printf("No hay vehiculos estacionados en el aparcamiento\n");
			}
			else {
				printf("Introduzca el numero de plaza que ocupa su vehiculo\n");
				int pos;
				scanf_s("%d", &pos);
				getchar();
				if (plaza[pos].estado == 1) {
					plaza[pos].estado = 0;
					if (plaza[pos].estado == 'C')
						cfreeseats++;
					else
						mfreeseats++;
					system("cls");
				}
				else
					printf("No hay vehiculo estacionado en la plaza seleccionada\n");
			}
			Sleep(1500);
			system("cls");
			break;

		case 'E':
			printf("Estado actual del aparcamiento:\n");
			for (int i = 1; i <= Nplazas; i++) {
				printf("Plaza %d \t", i);
				if (plaza[i].estado == 1) {
					printf("Ocupada \t %s  ", plaza[i].matricula);
					if (plaza[i].tipo == 'C')
						printf("Coche\n");
					else
						printf("Moto\n");
				}
				else 
					printf("Libre\n");
			}
			system("PAUSE");
			system("cls");
			break;

		case 'B':
			printf("Introduzca la matricula de su vehiculo\n");
			gets(matric);
			for (int i = 0; i < Nplazas; i++) {
				if (plaza[i].matricula == matric) {
					printf("Su vehiculo se encuentra en la plaza %d\n", i + 1);
					Sleep(1250);
					system("cls");
					break;
				}
			}
			printf("No se ha encontrado ningun vehiculo con esa matricula\n");
			Sleep(1250);
			system("cls");
			break;

		case 'S':
			printf("Se cerrara la sesion\nDesea continuar?\n");
			state = confirmacion();
			break;

		default:
			printf("No se reconoce la opccion seleccionada.\nIntroduzca una de las opciones listadas por favor.\n");
			Sleep(1500);
			system("cls");
			break;

		}
	}

		system("PAUSE");
}


																						//  FUNCIONES

																						//	MENU
char menu() {
	char opcion;
	printf("Bienvenido. Que operacion desea realizar?\n");
	printf("Para pedir una plaza pulse                         R\n");
	printf("Para abandonar el aparcamiento pulse               A\n");
	printf("Si desea ver el estado del aparcamiento pulse      E\n");
	printf("Si desea buscar por matricula pulse                B\n");
	printf("Si quiere salir pulse                              S\n");
	scanf_s("%c", &opcion);
	getchar();

	if (opcion >= 'a' && opcion <= 'z')
		opcion -= 32;
	system("cls");
	return opcion;
}
																						//  CONFIRMACION
int confirmacion() {		// 0 == TRUE    -    1 == FALSE
	char opcion;
	int loop = 1;
	while (loop == 1) {
		printf("\n Y (yes)   -   N (no)\n");
		scanf_s("%c", &opcion);
		getchar();
		if (opcion >= 'a' && opcion <= 'z') {
			opcion -= 32;
		}
		system("cls");
		switch (opcion) {
		case 'Y':
			return 0;
			break;

		case 'N':
			return 1;
			break;

		default:
			printf("No se reconoce la opccion seleccionada.\nIntroduzca una de las opciones listadas por favor.\n");
			Sleep(2000);
			break;
		}
	}
}

																						//	LOGIN

int login(FILE * parking, struct usuario *usuario) {

	struct usuario {
		char nickname[50];
		char password[50];
	};
	struct usuario user;

	char aux[30];
	int i = 0;
	while (fgetc(parking) != EOF) {
		for (i; fgetc(parking) != '|'; i++) {
			aux[i] = fgetc(parking);
		}
		if (aux == user.nickname) {

		}

	}
}

																						//	ValidDigit
int esDigitoValido(char caracter) {

}

																						//	ValidChar
int esLetraValida(char caracter) {

}

																						//	ValidMatricula
int esMatriculaValida(char matricula[]) {

}