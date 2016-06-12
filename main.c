#include <stdio.h>
#include <stdlib.h>

struct quadro{
    int constante;
    int expoente;
};

int main()
{

    struct quadro q[5];

    char polinomio1[100];
    char polinomio2[100];
    scanf("%s",polinomio1);
    scanf("%s",polinomio2);

    int tamanho1 = formulasSize(polinomio1);
    int tamanho2 = formulasSize(polinomio2);
    int tamanhoPolinomios = tamanho1;
    if(tamanho2 > tamanho1){
        tamanhoPolinomios = tamanho2;
    }

    int inicio1 = tamanhoPolinomios - tamanho1;
    int inicio2 = tamanhoPolinomios - tamanho2;

    struct quadro quadros1[tamanhoPolinomios];
    struct quadro quadros2[tamanhoPolinomios];

    //populaResto(quadros1, tamanho1, tamanhoPolinomios);
    //populaResto(quadros2, tamanho2, tamanhoPolinomios);
    //printf("%s\n", polinomio);
    lerPolinomio(polinomio1, quadros1,inicio1, tamanhoPolinomios);
    lerPolinomio(polinomio2, quadros2, inicio2, tamanhoPolinomios);

    mostraPolinomio(quadros1,tamanhoPolinomios);
    mostraPolinomio(quadros2,tamanhoPolinomios);

    return 0;
}

void junta(char *s, char c){
    char cToS[2];
    cToS[0] = c;
    cToS[1] = '\0';
    strcat(s,cToS);
}
void copia(char *s, char c){
    char cToS[2];
    cToS[0] = c;
    cToS[1] = '\0';
    strcpy(s,cToS);
}
void limpa(char *s){
    strcpy(s, "");
}
void mostraPolinomio(struct quadro *q, int tamanho){

    int i = 0;
    for(i = 0; i < tamanho; i++){

        //if(q[i].constante != 0){

            printf("%+d", q[i].constante);
            printf("x");
            if(q[i].expoente < 0)
                printf("%+d",q[i].expoente);
            else
                printf("%d",q[i].expoente);
        //}
    }
    printf("\n");
}
int formulasSize(char *polinomio){

    int qArr = 1;
    int i;
    int tamanhoStr = strlen(polinomio) +1;
    char expoente[100];
    limpa(expoente);

        for(i = 1; i < tamanhoStr; i++){
        //if(polinomio[i] == '-' || polinomio[i] == '+')
          //  qArr++;
        if(polinomio[i] == 'x'){
            for(i = (i+1); i < tamanhoStr; i++){
                if(polinomio[i] == '-' || polinomio[i] == '+')
                    break;
                else
                    junta(expoente, polinomio[i]);

            }
            break;
        }
            //printf("%c",polinomio[(i+1)]);
    }

    qArr = atoi(expoente);
    qArr++;

    return qArr;
}
void lerPolinomio(char *polinomio, struct quadro *quadros, int inicio, int tMaior){

    char parte [100];
    char constante[100];
    char expoente[100];
    int stLen = ((sizeof(quadros)) / 8);;
    int indice = 0;
    int indQ = inicio;
    int tamanhoStr = strlen(polinomio) + 1;

    printf("Inicio %d\n", ((inicio)));



    limpa(parte);


    for(indice = 0; indice < tamanhoStr; indice++){

        if(indice == 0)
            copia(parte, polinomio[indice]);

        if(!(indice == 0)){
            if(polinomio[indice] == '+' || polinomio[indice] == '-' || polinomio[indice] == '\0'){

                int tamanhoParte = strlen(parte) + 1;
                int j = 0;

                limpa(constante);
                limpa(expoente);

                    for(j = 0; j < tamanhoParte; j++){

                        if(parte[j] == 'x' || parte[j] == ' ')
                            break;
                        junta(constante, parte[j]);
                    }
                    for(j = j+1;j < tamanhoParte; j++){
                        if(parte[j] == '\0')
                            break;
                        junta(expoente, parte[j]);
                    }


                    if(indQ > 0 && atoi(expoente) >= 0){
                        int diferenca = (quadros[indQ-1].expoente) - atoi(expoente) -1;
                        while(diferenca > 0){
                            quadros[indQ].constante = 0;
                            quadros[indQ].expoente = quadros[(indQ-1)].expoente - 1;
                            diferenca --;
                            indQ++;
                        }
                    }


                quadros[indQ].constante = atoi(constante);
                quadros[indQ].expoente = atoi(expoente);
                indQ++;

                copia(parte, polinomio[indice]);
            }
            else{
                junta(parte, polinomio[indice]);
            }
        }
    }
    int l;
    for(l = 0; l < inicio; l++){
        quadros[l].constante = 0;
        quadros[l].expoente = tMaior - l-1;
    }


}
void populaResto(struct quadro *q, int inicio, int fim){

    for(;inicio < fim; inicio++){
        q[inicio].constante = 0;
        q[inicio].expoente = q[(inicio -1)].expoente + 1;
    }
}
