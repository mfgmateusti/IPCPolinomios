#include <stdio.h>
#include <stdlib.h>

struct termo{
    int constante;
    int expoente;
};

typedef struct termo termo;

int main()
{

    struct termo t[5];

    char polinomio1[100];
    char polinomio2[100];
    strcpy(polinomio1, "3x2+2x1+5");
    strcpy(polinomio2, "3x3+2");

    /*setbuf(stdin, NULL);
    scanf("%s",polinomio1);
    setbuf(stdin, NULL);
    scanf("%s",polinomio2);*/

    int tamanho1 = formulasSize(polinomio1);
    int tamanho2 = formulasSize(polinomio2);

    int tamanho;

    if(tamanho1 > tamanho2)
        tamanho = tamanho1;
    else
        tamanho = tamanho2;

    struct termo termos1[tamanho];
    struct termo termos2[tamanho];
    setTermos(termos1, tamanho);
    setTermos(termos2, tamanho);

    lerPolinomio(polinomio1, termos1, 0, tamanho);
    lerPolinomio(polinomio2, termos2, 0, tamanho);

    printf("\nPolinomio 1: ");
    mostraPolinomio(termos1,tamanho);

    printf("Polinomio 2: ");
    mostraPolinomio(termos2,tamanho);

    struct termo resultado[tamanho];
    soma(termos1, termos2, resultado, tamanho);
    printf("Soma: ");
    mostraPolinomio(resultado,tamanho);

    sub(termos1, termos2, resultado, tamanho);
    printf("Subtr: ");
    mostraPolinomio(resultado,tamanho);

    int tR = (tamanho)+(tamanho)-1;

    struct termo r2[tR];
    setTermos(r2, tR);
    mult(termos1, termos2, r2, tamanho);
    printf("Mult: ");
    mostraPolinomio(r2,tR);

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
void setTermos(termo *t, int tamanho){
    int ex = 0;
    int i;
    tamanho--;

    for(i = tamanho; i >= 0; i--){
        t[i].constante = 0;
        t[i].expoente = ex;
        ex++;
    }

}

void mostraPolinomio(struct termo *t, int tamanho){

    int i = 0;
    for(i = 0; i < tamanho; i++){

        if(t[i].constante != 0){

            printf("%+d", t[i].constante);

            if(t[i].expoente != 0){
                printf("x");
                if(t[i].expoente < 0)
                    printf("%+d",t[i].expoente);
                else
                    printf("%d",t[i].expoente);
            }
        }
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

void lerPolinomio(char *polinomio, struct termo *termos, int inicio, int tMaior){

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

                termos[p].constante = atoi(constante);

                copia(parte, polinomio[indice]);
            }
            else{
                junta(parte, polinomio[indice]);
            }
        }
    }
}
void soma(struct termo *t1, struct termo *t2, struct termo *resultado, int tamanho){
    int i = 0;
    for(;i < tamanho; i++){
        resultado[i].expoente = t1[i].expoente;
        resultado[i].constante = t1[i].constante + t2[i].constante;
    }

}
void sub(struct termo *t1, struct termo *t2, struct termo *resultado, int tamanho){
    int i = 0;
    for(;i < tamanho; i++){
        resultado[i].expoente = t1[i].expoente;
        if(t1[i].constante == 0)
            resultado[i].constante = t2[i].constante;
        else
            resultado[i].constante = t1[i].constante - t2[i].constante;
    }

}
void mult(struct termo *t1, struct termo *t2, struct termo *resultado, int tamanho){
    int i = 0;
    int j = 0;

        for(i = 0;i < tamanho; i++){
            for(j = 0;j < tamanho; j++){

                if(t1[i].constante != 0 && t2[j].constante != 0){

                    int constante = t1[i].constante * t2[j].constante;
                    int expoente = t2[i].expoente + t2[j].expoente;
                    int indice = tamanho+tamanho-expoente-2;

                    resultado[indice].constante += constante;
                    resultado[indice].expoente = expoente;
                }
            }
    }

}
