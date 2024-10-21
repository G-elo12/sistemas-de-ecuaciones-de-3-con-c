#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int potencia(int,int);
int maximoComunDivisor(int,int);
void imprimerFormato(float);
float entradaDeDatos(char*);
float determinate(float[3][3]);
void nuevaMatriz(float[3][3],int,float[3][3],float[3]);
void resolucion(float[3][3],float[3]);
int contarDigitos(int);

int contarDigitos(int numero){
    if (numero < 0) {
        numero = -numero;
    }
    if (numero == 0) {
        return 1;
    }
    int digitos = 0;
    while (numero != 0) {
        numero /= 10;  
        digitos++;
    }
    return digitos;
}

int main(){
    printf("Ingresa los coeficientes de las ecuaciones:\n");
    float vector[3][3];
    float array[3];
    for (int i = 0; i < 3; i++) {        
        for (int j = 0; j < 3; j++) {
            char input[20];
            if (j==0){
                printf("Ingrese el valor para la posición (%d, x): ", i + 1);
                scanf("%s", input);
                vector[i][j] = entradaDeDatos(input);
            }    
            else if (j==1){
                printf("Ingrese el valor para la posición (%d, y): ", i + 1);
                scanf("%s", input);
                vector[i][j] = entradaDeDatos(input);
            }  
            else if (j==2){
                printf("Ingrese el valor para la posición (%d, z): ", i + 1);
                scanf("%s", input);
                vector[i][j] = entradaDeDatos(input);
            }   
        }
    }
    for (int i = 0; i < 3; i++) {
        char input[20];
        printf("Ingrese el valor para la posición (%d): ", i + 1);
        scanf("%s", input);
        array[i] = entradaDeDatos(input);
    }
    printf("\nMatriz ingresada:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", vector[i][j]);
        }
        printf("\n");
    }
    resolucion(vector, array);
    return 0;
}

int potencia(int base,int exponente){
    int i;
    int aux = base;
    for ( i = 1; i < exponente; i++){
        base*=aux;
    }
    return base;
}

int maximoComunDivisor(int numero1,int numero2){
    while (numero2)
    {
       int aux = numero2;
       numero2 = numero1%numero2;
       numero1=aux;
    }
    return numero1;
}

void imprimerFormato(float valor){
    char aux[50];
    if((int)valor != valor){
        snprintf(aux,sizeof(aux),"%.4f",valor);
        int parteEntera,parteDecimal,numerador,denominador;
        char aux1[10],aux2[10];
        sscanf(aux,"%9[^.].%9s",aux1,aux2);
        parteDecimal = atoi(aux2);
        parteEntera = atoi(aux1);
        int numeroDeDigitos= contarDigitos(parteDecimal);
        denominador =1000;;
        numerador = (int)(parteEntera*denominador+parteDecimal);
        int divisorComn= maximoComunDivisor(numerador,denominador);
        numerador /=divisorComn;
        denominador/=divisorComn;
        float auxR = numerador/denominador;
        printf("%d/%d",numerador,denominador);
    }else{
        printf("%f",valor);
    }
}

float determinate(float vector[3][3]){
    float diagonal1 = vector[0][0] * vector[1][1] * vector[2][2] +
                      vector[1][0] * vector[2][1] * vector[0][2] +
                      vector[2][0] * vector[0][1] * vector[1][2];

    float diagonal2 = vector[0][2] * vector[1][1] * vector[2][0] +
                      vector[1][2] * vector[2][1] * vector[0][0] +
                      vector[2][2] * vector[0][1] * vector[1][0];

    return diagonal1 - diagonal2;
}

void nuevaMatriz(float original[3][3], int x, float nuevo[3][3], float array[3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == x) {
                nuevo[i][j] = array[i];
            } else {
                nuevo[i][j] = original[i][j];
            }
        }
    }
}

void resolucion(float vector[3][3],float array[3]){
    float deltaA,deltaX,deltaY,deltaZ,vectorAuxiliar[3][3];
    deltaA = determinate(vector);
    if(deltaA==0){
        printf("No tiene un unico resultado");
        exit(0);
    }
    nuevaMatriz(vector,0,vectorAuxiliar,array);
    deltaX = determinate(vectorAuxiliar);
    nuevaMatriz(vector,1,vectorAuxiliar,array);
    deltaY = determinate(vectorAuxiliar);
    nuevaMatriz(vector,2,vectorAuxiliar,array);
    deltaZ = determinate(vectorAuxiliar);
    printf("\nLas soluciones son:\n");
    printf("\nx = ");
    imprimerFormato((deltaX/deltaA));
    printf("\ny = ");
    imprimerFormato((deltaY/deltaA));
    printf("\nz = ");
    imprimerFormato((deltaZ/deltaA));
}

float entradaDeDatos(char*valor){
    char *aux;
    float resultado = strtof(valor, &aux);
    if (*aux == '\0') {  
        return resultado;
    } else if (strchr(valor, '/') != NULL) {  
        int numerador, denominador;
        if (sscanf(valor, "%d/%d", &numerador, &denominador) == 2) {
            return (float)numerador / denominador;
        }
    }
    printf("Entrada no válida.\n");
    exit(1);
}