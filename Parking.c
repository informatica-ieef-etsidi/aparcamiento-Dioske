#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define SeatState 10
#define Nmatr 10
#define Tiempo 10


void main() {
	int plazas[SeatState];
	int fs = 0;			//free seats == plazas libres	||	 El numero de plazas libres al iniciar puede no ser el espacio total del aparcamiento
	char opcion;
	int timer;
	int state = 1;
	int randomizer;
	char matriculas[Nmatr];
	char matric[8];
	int variable = 0; //variable de uso libre para cualquier detalle

	for (timer = 0; timer < SeatState; timer++) {
		plazas[timer] = 0;
		if (plazas[timer] == 0) {
			fs = fs + 1;
		}
	}

	while (state==1) {
		printf("Bienvenido. Que operacion desea realizar?\n");
		printf("Para pedir una plaza pulse                         R\n");
		printf("Para abandonar el aparcamiento pulse               A\n");
		printf("Si desea ver el estado del aparcamiento pulse      E\n");
		printf("Si desea buscar por matricula pulse                B\n");
		printf("Si quiere salir pulse                              S\n");
		scanf_s("%c", &opcion);
		getchar();


		
		if (opcion >= 'a' || opcion >= 'z') {
			opcion -= 32;
		}
		system("cls");

		switch (opcion) {
		case 'R':
			if (fs == 0) {
				printf("No quedan plazas libres\n");
				Sleep(1500);
				system("cls");
				break;
			}
			else {
				variable = 1;
				while (variable == 1) {
				srand(time(NULL));
				randomizer = rand() % 11;
				if (plazas[randomizer] == 0) {
					plazas[randomizer] = 1;
					printf("Cual es la matricula de su vehiculo?\n");
					scanf_s("%c", &matric);
					matriculas[randomizer] = matric;
					printf("Se le ha asignado la plaza numero %d\n", randomizer + 1);
					fs--;
					variable = 0;
				}
			}
				Sleep(1500);
				system("cls");
				getchar();
				break;
		}

		case 'A':
			if (fs < SeatState) {
				printf("Que plaza ocupaba su vehiculo?\n");
				scanf_s("%d", &variable);
				plazas[variable-1] = 0;
				fs++;
				printf("El numero de plazas libres es ahora %d\n", fs);
				Sleep(1000);
				system("cls");
				break;
			}
			else {
				printf("No hay ninguna plaza ocupada\n");
				Sleep(1000);
				system("cls");
				break;
			}

		case 'E':
			printf("Este es el estado del aparcamiento\n\n");
			for (timer = 0; timer < SeatState; timer++) {
				printf("  Plaza %d \t", timer + 1);
				if (plazas[timer] == 0) {
					printf("Libre\n");
				}
				else{
					printf("Ocupada");
					printf("%c\n", matriculas[timer]);
				}
			}
			printf("\n");
			system("PAUSE");
			system("cls");
			break;

		case 'S':
			state = 0;
			system("cls");
			break;

		case 'B':
			printf("Introduzca la matricula de su vehiculo");
			scanf_s("%c", &matric);

			break;

		default:
			printf("No se reconoce la opccion seleccionada.\nIntroduzca una de las opciones listadas por favor.\n");
			Sleep(1250);
			system("cls");
			break;
		}
	}
	system("PAUSE");
	return 0;
}