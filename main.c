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
    strcpy(polinomio1, "");
    strcpy(polinomio2, "");


    setbuf(stdin, NULL);
    scanf("%s",polinomio1);
    setbuf(stdin, NULL);
    scanf("%s",polinomio2);

    int tamanho1 = formulasSize(polinomio1);
    int tamanho2 = formulasSize(polinomio2);

    int tamanho;

    if(tamanho1 > tamanho2)
        tamanho = tamanho1;
    else
        tamanho = tamanho2;

    struct quadro quadros1[tamanho];
    struct quadro quadros2[tamanho];

    int i = 0;
    int ex = 0;
    for(i = tamanho-1; i >= 0; i--){
        quadros1[i].constante = 0;
        quadros1[i].expoente = ex;
        quadros2[i].constante = 0;
        quadros2[i].expoente = ex;
        ex++;
    }

    lerPolinomio(polinomio1, quadros1, 0, tamanho);
    lerPolinomio(polinomio2, quadros2, 0, tamanho);

    printf("\nPolinomio 1: ");
    mostraPolinomio(quadros1,tamanho);

    printf("Polinomio 2: ");
    mostraPolinomio(quadros2,tamanho);

    struct quadro resultado[tamanho];
    soma(quadros1, quadros2, resultado, tamanho);
    printf("Soma: ");
    mostraPolinomio(resultado,tamanho);

    sub(quadros1, quadros2, resultado, tamanho);
    printf("Subtr: ");
    mostraPolinomio(resultado,tamanho);

    struct quadro r2[(tamanho*2)];
    mult(quadros1, quadros2, r2, tamanho);
    printf("Mult: ");
    mostraPolinomio(r2,tamanho);

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

            //if(q[i].expoente != 0){
                printf("x");
                if(q[i].expoente < 0)
                    printf("%+d",q[i].expoente);
                else
                    printf("%d",q[i].expoente);
            //}
        //}
    }
    printf("\n");
}
int formulasSize(char *polinomio){

    int qArr = 1;
    int i;
    int tamanhoStr = strlen(polinomio) +1;
    char expoente[10];
    limpa(expoente);
    int maior = 0;

        for(i = 1; i < tamanhoStr; i++){
            limpa(expoente);

            if(polinomio[i] == 'x'){
                for(i = (i+1); i < tamanhoStr; i++){
                    if(polinomio[i] == '-' || polinomio[i] == '+' || '\0')
                        break;
                    else
                        junta(expoente, polinomio[i]);
            }
            if(i == 0)
                maior = atoi(expoente);
            if(atoi(expoente) > maior)
                maior = atoi(expoente);
        }
            //printf("%c",polinomio[(i+1)]);
    }

    qArr = maior;
    qArr++;

    return qArr;
}

void lerPolinomio(char *polinomio, struct quadro *quadros, int inicio, int tMaior){

    char parte [3];
    char constante[3];
    char expoente[3];
    int indice = 0;
    int tamanhoStr = strlen(polinomio) + 1;

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

                int p = tMaior - (atoi(expoente)) - 1;

                printf("\n");
                printf("C %c \nE %c\n",constante[0],expoente[0]);

                quadros[p].constante = 1;
                quadros[p].constante = atoi(constante);

                copia(parte, polinomio[indice]);
            }
            else{
                junta(parte, polinomio[indice]);
            }
        }
    }
}
void soma(struct quadro *q1, struct quadro *q2, struct quadro *resultado, int tamanho){
    int i = 0;
    for(;i < tamanho; i++){
        resultado[i].expoente = q1[i].expoente;
        resultado[i].constante = q1[i].constante + q2[i].constante;
    }

}
void sub(struct quadro *q1, struct quadro *q2, struct quadro *resultado, int tamanho){
    int i = 0;
    for(;i < tamanho; i++){
        resultado[i].expoente = q1[i].expoente;
        resultado[i].constante = q1[i].constante - q2[i].constante;
    }

}
void mult(struct quadro *q1, struct quadro *q2, struct quadro *resultado, int tamanho){
    int i = 0;
    int j = 0;
        for(;i < tamanho; i++){
            for(;j < tamanho; j++){
                int expoente = q1[i].expoente + q2[i].expoente;
                int indice = abs(expoente - (tamanho *2));

                resultado[indice].expoente = expoente;
                resultado[indice].constante = q1[i].constante - q2[i].constante;
            }
    }

}
