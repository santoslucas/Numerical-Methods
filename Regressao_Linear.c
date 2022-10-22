#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//VARIÁVEIS GLOBAIS:
float a[3][4];
int n;
float b2, b1, b0;

//SOMA DOS VALORES DE UM VETOR:
float sum(float parcela[], int numParcelas){
    float soma=0;
    for(int i=0; i<numParcelas; i++){
        soma += parcela[i];
    }

    return soma;
}

//PRODUTO DOS ELEMENTOS DE DOIS VETORES (de acordo com o índice de sua posição):
float mul(float x[], float y[], int i){
    float produto=0;
    produto = x[i]*y[i];
    return produto;
}

//SOMA DOS QUADRADOS DOS ELEMENTOS DE UM VETOR:
float soma_quadrados(float parcela[], int numParcelas){
    float soma=0;    
    for(int i=0; i<numParcelas; i++){
        soma += pow(parcela[i], 2);
    }

    return soma;
}

//SOLUÇÃO DE UM SISTEMA LINEAR:
void forwardSubstitution() {
    int i, j, k, max;
    float t;
    for (i = 0; i < n; ++i) {
        max = i;
        for (j = i + 1; j < n; ++j)
            if (a[j][i] > a[max][i])
                max = j;
        
        for (j = 0; j < n + 1; ++j) {
            t = a[max][j];
            a[max][j] = a[i][j];
            a[i][j] = t;
        }
        
        for (j = n; j >= i; --j)
            for (k = i + 1; k < n; ++k)
                a[k][j] -= a[k][i]/a[i][i] * a[i][j];


    }
}

void reverseElimination() {
    int i, j;
    for (i = n - 1; i >= 0; --i) {
        a[i][n] = a[i][n] / a[i][i];
        a[i][i] = 1;
        for (j = i - 1; j >= 0; --j) {
            a[j][n] -= a[j][i] * a[i][n];
            a[j][i] = 0;
        }
    }
}

void gauss() {
    int i, j;

    forwardSubstitution();
    reverseElimination();
    
    b0 = a[0][3];
    b1 = a[1][3];
    b2 = a[2][3];
}

//QUADRADOS DOS RESÍDUOS
float quad_residuos(float b0, float b1, float b2, float y, float x1, float x2){
    return (pow((y-(b0+(b1*x1)+(b2*x2))), 2));
}

//FUNÇÃO MAIN:
int main(){
    int numX;
    n = 3; //Será utilizado na solução do sistema linear
    
    printf("Insira a quantidade de valores de X1/X2:\n");
    scanf("%i", &numX);

    float vetorX1[numX]; // X1_i's
    float vetorX2[numX]; // X2_i's    
    float vetorY[numX]; // Yi's

    printf("\nInsira as variaveis X1_i, X2_i e seus respectivos Yi (separados por um espaco):\n");

    for(int i = 0; i < numX; i++){
        scanf("%f %f %f", &vetorX1[i], &vetorX2[i], &vetorY[i]);
    }

    float variavelX1, variavelX2;
    printf("\nInsira os valores de X1 e X2 que serao aplicados no polinomio interpolador (separados por espaço):\n");
    scanf("%f %f", &variavelX1, &variavelX2);

    // Somatorios 
    float somaX1 = sum(vetorX1, numX);
    float somaX2 = sum(vetorX2, numX);
    float somaY = sum(vetorY, numX);
    float somaX1quad = soma_quadrados(vetorX1, numX);
    float somaX2quad = soma_quadrados(vetorX2, numX);
    float somaYquad = soma_quadrados(vetorY, numX);

    //Somatorio produtos
    float produtoX1Y[numX];
    float produtoX2Y[numX];
    float produtoX1X2[numX];
    for(int i=0; i<numX; i++){
        produtoX1Y[i] = mul(vetorX1, vetorY, i);
        produtoX2Y[i] = mul(vetorX2, vetorY, i);
        produtoX1X2[i] = mul(vetorX1, vetorX2, i);
    }
    float soma_X1Y = sum(produtoX1Y, numX);
    float soma_X2Y = sum(produtoX2Y, numX);
    float soma_X1X2 = sum(produtoX1X2, numX);

    // Preenche valores da matriz do sistema linear
    a[0][0] = numX;     a[0][1] = somaX1;       a[0][2] = somaX2;       a[0][3] = somaY; 
    a[1][0] = somaX1;   a[1][1] = somaX1quad;   a[1][2] = soma_X1X2;    a[1][3] = soma_X1Y;
    a[2][0] = somaX2;   a[2][1] = soma_X1X2;    a[2][2] = somaX2quad;   a[2][3] = soma_X2Y;

    // Calculo b0, b1, b2
    gauss();
    
    // Calculo soma dos quadrados residuos
    float residuos[numX];
    for (int i = 0; i < numX; i++)
    {
        residuos[i] = quad_residuos(b0, b1, b2, vetorY[i], vetorX1[i], vetorX2[i]);
    }
    // Calculo S(b0,b1,b2)
    float S = sum(residuos, numX);
    // Calculo do coeficiente de determinacao
    float coef_determinacao = (1 - (S / (somaYquad-((pow(somaY,2)/numX)))));
    // Calculo da variacia residual
    float var_residual = (S/(numX-3));
    
    // Calculo funcao
    printf("\nY(x) = (%f)(x2) + (%f)(x1) + (%f)\n", b2, b1, b0);
    printf("r² = %.4f\n", coef_determinacao);
    printf("variancia residual = %.4f\n", var_residual);
    
    //Calculo de Y para determinados valores de X1 e X2:
    float resultado = (b2*variavelX2) + (b1*variavelX1) + b0;
    printf("\nA área da superfície corporal é de: %f\n", resultado);

    return 0;
}



#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//VARIÁVEIS GLOBAIS:
float a[3][4];
int n;
float b2, b1, b0;

//SOMA DOS VALORES DE UM VETOR:
float sum(float parcela[], int numParcelas){
    float soma=0;
    for(int i=0; i<numParcelas; i++){
        soma += parcela[i];
    }

    return soma;
}

//PRODUTO DOS ELEMENTOS DE DOIS VETORES (de acordo com o índice de sua posição):
float mul(float x[], float y[], int i){
    float produto=0;
    produto = x[i]*y[i];
    return produto;
}

//SOMA DOS QUADRADOS DOS ELEMENTOS DE UM VETOR:
float soma_quadrados(float parcela[], int numParcelas){
    float soma=0;    
    for(int i=0; i<numParcelas; i++){
        soma += pow(parcela[i], 2);
    }

    return soma;
}

//SOLUÇÃO DE UM SISTEMA LINEAR:
void forwardSubstitution() {
    int i, j, k, max;
    float t;
    for (i = 0; i < n; ++i) {
        max = i;
        for (j = i + 1; j < n; ++j)
            if (a[j][i] > a[max][i])
                max = j;
        
        for (j = 0; j < n + 1; ++j) {
            t = a[max][j];
            a[max][j] = a[i][j];
            a[i][j] = t;
        }
        
        for (j = n; j >= i; --j)
            for (k = i + 1; k < n; ++k)
                a[k][j] -= a[k][i]/a[i][i] * a[i][j];


    }
}

void reverseElimination() {
    int i, j;
    for (i = n - 1; i >= 0; --i) {
        a[i][n] = a[i][n] / a[i][i];
        a[i][i] = 1;
        for (j = i - 1; j >= 0; --j) {
            a[j][n] -= a[j][i] * a[i][n];
            a[j][i] = 0;
        }
    }
}

void gauss() {
    int i, j;

    forwardSubstitution();
    reverseElimination();
    
    b0 = a[0][3];
    b1 = a[1][3];
    b2 = a[2][3];
}

//QUADRADOS DOS RESÍDUOS
float quad_residuos(float b0, float b1, float b2, float y, float x1, float x2){
    return (pow((y-(b0+(b1*x1)+(b2*x2))), 2));
}

//FUNÇÃO MAIN:
int main(){
    int numX;
    n = 3; //Será utilizado na solução do sistema linear
    
    printf("Insira a quantidade de valores de X1/X2:\n");
    scanf("%i", &numX);

    float vetorX1[numX]; // X1_i's
    float vetorX2[numX]; // X2_i's    
    float vetorY[numX]; // Yi's

    printf("\nInsira as variaveis X1_i, X2_i e seus respectivos Yi (separados por um espaco):\n");

    for(int i = 0; i < numX; i++){
        scanf("%f %f %f", &vetorX1[i], &vetorX2[i], &vetorY[i]);
    }

    float variavelX1, variavelX2;
    printf("\nInsira os valores de X1 e X2 que serao aplicados no polinomio interpolador (separados por espaço):\n");
    scanf("%f %f", &variavelX1, &variavelX2);

    // Somatorios 
    float somaX1 = sum(vetorX1, numX);
    float somaX2 = sum(vetorX2, numX);
    float somaY = sum(vetorY, numX);
    float somaX1quad = soma_quadrados(vetorX1, numX);
    float somaX2quad = soma_quadrados(vetorX2, numX);
    float somaYquad = soma_quadrados(vetorY, numX);

    //Somatorio produtos
    float produtoX1Y[numX];
    float produtoX2Y[numX];
    float produtoX1X2[numX];
    for(int i=0; i<numX; i++){
        produtoX1Y[i] = mul(vetorX1, vetorY, i);
        produtoX2Y[i] = mul(vetorX2, vetorY, i);
        produtoX1X2[i] = mul(vetorX1, vetorX2, i);
    }
    float soma_X1Y = sum(produtoX1Y, numX);
    float soma_X2Y = sum(produtoX2Y, numX);
    float soma_X1X2 = sum(produtoX1X2, numX);

    // Preenche valores da matriz do sistema linear
    a[0][0] = numX;     a[0][1] = somaX1;       a[0][2] = somaX2;       a[0][3] = somaY; 
    a[1][0] = somaX1;   a[1][1] = somaX1quad;   a[1][2] = soma_X1X2;    a[1][3] = soma_X1Y;
    a[2][0] = somaX2;   a[2][1] = soma_X1X2;    a[2][2] = somaX2quad;   a[2][3] = soma_X2Y;

    // Calculo b0, b1, b2
    gauss();
    
    // Calculo soma dos quadrados residuos
    float residuos[numX];
    for (int i = 0; i < numX; i++)
    {
        residuos[i] = quad_residuos(b0, b1, b2, vetorY[i], vetorX1[i], vetorX2[i]);
    }
    // Calculo S(b0,b1,b2)
    float S = sum(residuos, numX);
    // Calculo do coeficiente de determinacao
    float coef_determinacao = (1 - (S / (somaYquad-((pow(somaY,2)/numX)))));
    // Calculo da variacia residual
    float var_residual = (S/(numX-3));
    
    // Calculo funcao
    printf("\nY(x) = (%f)(x2) + (%f)(x1) + (%f)\n", b2, b1, b0);
    printf("r² = %.4f\n", coef_determinacao);
    printf("variancia residual = %.4f\n", var_residual);
    
    //Calculo de Y para determinados valores de X1 e X2:
    float resultado = (b2*variavelX2) + (b1*variavelX1) + b0;
    printf("\nA área da superfície corporal é de: %f\n", resultado);

    return 0;
}

