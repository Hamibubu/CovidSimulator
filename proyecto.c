//Abraham de León Gutiérreez
//Luis Santiago Zamora Vargas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <windows.h>

#define NEGRO 0
#define AMARILLO 6
#define BLANCO 15
#define GRIS 7
#define GRISOS 8
#define AZUL 1
#define AZULBJ 3
#define VERDE 2
#define ROJO 4
#define filas 30
#define columnas 30

unsigned long long system_current_time_millis()
{
#if defined(_WIN32) || defined(_WIN64)
    struct _timeb timebuffer;
    _ftime(&timebuffer);
    return (unsigned long long)(((timebuffer.time * 1000) + timebuffer.millitm));
#else
    struct timeb timebuffer;
    ftime(&timebuffer);
    return (unsigned long long)(((timebuffer.time * 1000) + timebuffer.millitm));
#endif
}

struct CELDA{
    int ocupa;
    int id;
    int edad;
    int status;
    int vacunado;
    int dias;
    int cubrebocas;
};
int inicia(struct CELDA mat[][columnas], int f, int c);
void enfermate(struct CELDA mat[][columnas], int infectar[]);
int cubrebocas(struct CELDA mat[][columnas], int f, int c);
void imprimirmatriz(struct CELDA mat[][columnas], int f, int c);
void infectar(struct CELDA mat[][columnas], int f, int c);
void recorredias(struct CELDA mat[][columnas], int f, int c);
int main(){
    srand((int) system_current_time_millis());
    struct CELDA arr[filas][columnas];
    inicia(arr, filas, columnas);
    cubrebocas(arr, filas, columnas);
    int pacientecero[3];
    enfermate(arr, pacientecero);
    int input;
    do{
        recorredias(arr, filas, columnas);
        imprimirmatriz(arr , filas, columnas);
        infectar(arr , filas, columnas);
        printf("\n Presiona 1 para continuar el siguiente dia, 0 para salir:\n> ");
        scanf("%d", &input);
        }while(input!=0);
    int fil=*(pacientecero+1), col=*(pacientecero+2);
    printf("\n-----------------------------------------------------------------------------------------------");
    printf("\n| Como se puede ver queda un enfermo ese es el paciente 0 DATOS:                              |");
    if(((*(arr+fil)+col)->cubrebocas) == 0){
        printf("\n| Cubrebocas: NO                                                                              |");
    }else if(((*(arr+fil)+col)->cubrebocas) == 1){
        printf("\n| Cubrebocas: SI                                                                              |");
    }
    if(((*(arr+fil)+col)->vacunado) == 0){
        printf("\n| Vacuna: NO                                                                                  |");
    }else if(((*(arr+fil)+col)->vacunado) == 1){
        printf("\n| Vacuna: SI                                                                                  |");
    }
    printf("\n| Edad:   %d                                                                                  |", (*(arr+fil)+col)->edad);
    printf("\n-----------------------------------------------------------------------------------------------\n");
    printf("\n\n GRACIAS!\n");
    return 0;
}
int inicia(struct CELDA mat[][columnas], int f, int c){
    int i, j, id=1, r, r1;
    int ocupa=0, solo=0;
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            (*(*(mat+i)+j)).ocupa=0;
            (*(*(mat+i)+j)).status=0;
            (*(*(mat+i)+j)).dias=0;
        }
    }
    while(ocupa!=540){
        r = rand()%f;
        r1 = rand()%c;
        if((*(*(mat+r)+r1)).ocupa==0){
            (*(*(mat+r)+r1)).ocupa=1;
            (*(*(mat+r)+r1)).id=id;
            (*(*(mat+r)+r1)).edad=rand() % (90+1);
            ocupa++;
            id++;
        }
    }
    return 0;
}
void enfermate(struct CELDA mat[][columnas], int infectar[]){
    int r, c;
    r = rand()%(filas-2)+1;
    c = rand()%(columnas-2)+1;
    if((*(*(mat+r)+c)).ocupa==0){
    while((*(*(mat+r)+c)).ocupa!=1){
        if((*(*(mat+r)+c)).ocupa==0){
            r = rand()%(filas-2)+1;
            c = rand()%(filas-2)+1;
        }
        else{
            break;
        }
        }
      }
    if((*(*(mat+r)+c)).ocupa!=0){
        (*(*(mat+r)+c)).dias = 0;
        (*(*(mat+r)+c)).status = 1;
        *infectar = (*(*(mat+r)+c)).id;
        *(infectar+1) = r;
        *(infectar+2) = c;
    }
}
int cubrebocas(struct CELDA mat[][columnas], int f, int c){
    int i, j, cubrevacuna=0, nocubrevacuna=0, cubrenovacuna=0, r, r1;
    printf("\n");
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            (*(*(mat+i)+j)).cubrebocas=0;
            (*(*(mat+i)+j)).vacunado=0;
        }
    }
    while(cubrevacuna!=((f*c)*0.25)){
        r = rand()%filas;
        r1 = rand()%columnas;
        if((*(*(mat+r)+r1)).cubrebocas==0 && (*(*(mat+r)+r1)).vacunado==0){
(*(*(mat+r)+r1)).cubrebocas=1;
            (*(*(mat+r)+r1)).vacunado=1;
            cubrevacuna++;
        }
    }
    while(nocubrevacuna!=((f*c)*0.25)){
        r = rand()%filas;
        r1 = rand()%columnas;
        if((*(*(mat+r)+r1)).cubrebocas==0 && (*(*(mat+r)+r1)).vacunado==0){
            (*(*(mat+r)+r1)).cubrebocas=0;
            (*(*(mat+r)+r1)).vacunado=1;
            nocubrevacuna++;
        }
    }
    while(cubrenovacuna!=((f*c)*0.25)){
        r = rand()%filas;
        r1 = rand()%columnas;
        if((*(*(mat+r)+r1)).cubrebocas==0 && (*(*(mat+r)+r1)).vacunado==0){
            (*(*(mat+r)+r1)).cubrebocas=1;
            (*(*(mat+r)+r1)).vacunado=0;
            cubrenovacuna++;
        }
    }
}
void imprimirmatriz(struct CELDA mat[][columnas], int f, int c){
	printf("\n");
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i =0; i<f;i++){
		for(int j=0; j<c;j++){
			if((*(*(mat+i)+j)).ocupa == 1){
				if((*(*(mat+i)+j)).vacunado == 1 && (*(*(mat+i)+j)).status == 0){
					if((*(*(mat+i)+j)).cubrebocas ==1){ 
                        SetConsoleTextAttribute(hConsole,NEGRO<<4 | AZULBJ);
						printf(" v ");
					}else if((*(*(mat+i)+j)).cubrebocas == 0){
                        SetConsoleTextAttribute(hConsole,NEGRO<<4 | AZUL);
						printf(" V ");
					}
				}else if((*(*(mat+i)+j)).status == 0 && (*(*(mat+i)+j)).vacunado == 0){
					if((*(*(mat+i)+j)).cubrebocas == 1){
                        SetConsoleTextAttribute(hConsole,NEGRO<<4 | GRIS);
						printf(" s ");
					}
                    else if((*(*(mat+i)+j)).cubrebocas == 0){
                        SetConsoleTextAttribute(hConsole,NEGRO<<4 | GRISOS);
						printf(" S ");
					}
				}else if((*(*(mat+i)+j)).status == 1 && (*(*(mat+i)+j)).cubrebocas == 1){
					SetConsoleTextAttribute(hConsole,NEGRO<<4 | VERDE);
                    printf(" e ");
                }
				else if((*(*(mat+i)+j)).status == 1 && (*(*(mat+i)+j)).cubrebocas == 0){
					    SetConsoleTextAttribute(hConsole,NEGRO<<4 | ROJO);
                        printf(" E ");
				    }
			    }if(((*(*(mat+i)+j)).status ==2) && ((*(*(mat+i)+j)).ocupa == 1)){
                    SetConsoleTextAttribute(hConsole,NEGRO<<4 | BLANCO);
					printf(" r ");
			    }
			    else if((*(*(mat+i)+j)).ocupa == 0){
				    printf("   ");
			}
		}
    printf("\n");
	}
}
void infectar(struct CELDA mat[][columnas], int f, int c){
    int i, j, k, l;
    struct CELDA *infectados[(f*c)];
    int corrida=0;
    for(i=1;i<f-1;i++){ //Primer ciclo para recorrer las filas
        for(j=1;j<c-1;j++){ //Ciclo para recorrer las columnas
            if((*(*(mat+i)+j)).status == 1){ //Checamos que este infectado
                for(k=-1;k<2;k++){ //For para las filas ya que pasaremos por las adyacentes
                    for(l=-1;l<2;l++){ // For para las columnas adyacentes
                    
                        if(((*(*(mat+i+k)+j+l)).status)== 0){ //Vemos si la persona a infectar está sana
                            if(  (((*(*(mat+i+k)+j+l)).cubrebocas)== 0) && (((*(*(mat+i)+j)).cubrebocas)== 0) && (((*(*(mat+i+k)+j+l)).vacunado)== 0) ){
                            // probabilidad de 90% de enfermarse
                            int prob = rand()%100+1;
                            if(prob >= 90 ){
                                *(infectados+corrida)= &(*(*(mat+i+k)+j+l));
                                corrida++;
                                }
                            }
                            else if(  (((*(*(mat+i+k)+j+l)).cubrebocas)== 1) && (((*(*(mat+i)+j)).cubrebocas)== 1) && (((*(*(mat+i+k)+j+l)).vacunado)== 0) ){
                            // probabilidad de 10% de enfermarse
                            int prob = rand()%100+1;
                            if(prob >= 10 ){
                                *(infectados+corrida)= &(*(*(mat+i+k)+j+l));
                                corrida++;
                                }
                            }
                            else if(  (((*(*(mat+i+k)+j+l)).cubrebocas)== 1) || (((*(*(mat+i)+j)).cubrebocas)== 1) && (((*(*(mat+i+k)+j+l)).vacunado)== 0) ){
                            // probabilidad de 20% de enfermarse
                            int prob = rand()%100+1;
                            if(prob >= 20 ){
                                *(infectados+corrida)= &(*(*(mat+i+k)+j+l));
                                corrida++;
                                }
                            }
                            else if(  (((*(*(mat+i+k)+j+l)).cubrebocas)== 0) && (((*(*(mat+i)+j)).cubrebocas)== 0) && (((*(*(mat+i+k)+j+l)).vacunado)== 1) ){
                            // probabilidad de 45% de enfermarse
                            int prob = rand()%100+1;
                            if(prob >= 45 ){
                                *(infectados+corrida)= &(*(*(mat+i+k)+j+l));
                                corrida++;
                                }
                            }
                            else if(  (((*(*(mat+i+k)+j+l)).cubrebocas)== 1) && (((*(*(mat+i)+j)).cubrebocas)== 1) && (((*(*(mat+i+k)+j+l)).vacunado)== 1) ){
                            // probabilidad de 5% de enfermarse
                            int prob = rand()%100+1;
                            if(prob >= 5 ){
                                *(infectados+corrida)= &(*(*(mat+i+k)+j+l));
                                corrida++;
                                }
                            }
                            else if(  (((*(*(mat+i+k)+j+l)).cubrebocas)== 1) || (((*(*(mat+i)+j)).cubrebocas)== 1) && (((*(*(mat+i+k)+j+l)).vacunado)== 1) ){
                            // probabilidad de 15% de enfermarse
                            int prob = rand()%100+1;
                            if(prob >= 15 ){
                                *(infectados+corrida)= &(*(*(mat+i+k)+j+l));
                                corrida++;
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    for(i=0;i<corrida;i++){
        if((**(infectados+i)).ocupa == 1){
            ((**(infectados+i)).status) = 1;
            ((**(infectados+i)).dias) = 1;
        }
    }
}
void recorredias(struct CELDA mat[][columnas], int f, int c){
    int i, j, k, l;
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            if( (((*(*(mat+i)+j)).dias) != 0) && (((*(*(mat+i)+j)).status) == 1)){
                ((*(*(mat+i)+j)).dias)++;
                if(((*(*(mat+i)+j)).dias) == 8){
                    ((*(*(mat+i)+j)).status) = 2;
                }
            }
        }
    }
}