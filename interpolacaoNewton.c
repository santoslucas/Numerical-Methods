/*
    Alunos: Lara Gama Santos
            Lucas Santos Rodrigues
    
    Método: Interpolação de Newton
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int numX;
    printf("Insira a quantidade de valores de Xi:\n");
    scanf("%i", &numX);

    float vetorX[numX]; // Xi's
    float vetorY[numX]; // Yi's

    printf("\nInsira as variaveis Xi e seus respectivos Yi (separados por um espaço):\n");

    for(int i = 0; i < numX; i++){
        scanf("%f %f", &vetorX[i], &vetorY[i]);
    }

    float variavelX;
    printf("\nInsira o valor de X que será aplicado no polinômio interpolador:\n");
    scanf("%f", &variavelX);

    // Cria matriz dif_div que receberá as diferenças divididas
    int tamanho = numX;

    float **dif_div;
    // Alocacao dinamica das linhas da matriz
    dif_div = (float **) malloc (tamanho * sizeof (float *));

    // Alocacao dinamica das colunas da matriz
    for (int i = 0; i < numX; i++, tamanho--)
    {   
        dif_div[i] = (float *) malloc (tamanho * sizeof (float *));
    }
    
    // Calculo das diferenças divididas
    for (int i=0, tamanho=numX; i < numX; i++, tamanho--)
    {   
        for (int j = 0; j < tamanho; j++)
        {   
            if(i==0){ // Diferença dividida de ordem zero
                dif_div[i][j] = vetorY[j];
            }

            else{ // Diferença dividida de ordem maior que zero
                  // Usando a formula de diferenca dividida
                dif_div[i][j] = ((dif_div[i-1][j+1] - dif_div[i-1][j]) /
                                (vetorX[j+(numX-tamanho)] - vetorX[j]));
            }
        }
    }

    float parcelas[numX]; // Parcelas do polinomio interpolador P(x), ex: " f[x0, x1](x-x0) "
    
    for (int i=0, tamanho=0; i < numX; i++, tamanho++){
        if(i==0){
            parcelas[i] = dif_div[i][0]; // y0 ou f[x0]
        }

        else{
            parcelas[i] = dif_div[i][0]; // f[x0...]

            for(int j=0; j<tamanho; j++){
                float sub=0;
                sub = (variavelX - vetorX[j]); // (X - Xi)
                parcelas[i] = (parcelas[i] * sub); // f[x0...] * (X - Xi)
            }
        }
    }

    float resultado=0;
    for(int i=0; i<numX; i++){ // Calculo do P(x);
        resultado += parcelas[i];
    }

    printf("\nP(%.2f) = %.4f\n", variavelX, resultado);
}
//.
