#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_NOME 20

typedef enum{false, true}bool;

typedef struct no{
    char nome[TAM_NOME];
    int matricula, turma;
    float coef;
    struct no *prox;
    struct no *ant;
}noAluno;
noAluno *prim=NULL;
noAluno *ult=NULL;

bool insereAluno(noAluno aluno);

void imprimeLista();

bool removeAluno(int matricula);

int buscaMatricula(int matricula);

int main()
{
    noAluno aluno;
    int i;
    for(i=0;i<3;i++){
        printf("Digite a matricula: ");
        scanf("%d", &aluno.matricula);
        getchar();
        while(buscaMatricula(aluno.matricula)!=-1){
            printf("Aluno já encontrado, digite matrícula novamente: ");
            scanf("%d", &aluno.matricula);
            getchar();
        }
        printf("Digite o nome: ");
        gets(aluno.nome);
        printf("Digite o coeficiente: ");
        scanf("%f", &aluno.coef);
        getchar();
        printf("Digite a turma: ");
        scanf("%d", &aluno.turma);
        getchar();
        insereAluno(aluno);
        printf("\n\n");
    }
    printf("Insira a matricula que deseja remover: ");
    scanf("%d", &aluno.matricula);
    getchar();
    removeAluno(aluno.matricula);
    imprimeLista();
    return 0;
}

bool insereAluno(noAluno aluno){
    noAluno *aux = NULL;
    noAluno *atual = prim;
    noAluno *novo = (noAluno *)malloc(sizeof(noAluno));

    if(prim == NULL){
        prim = novo;
        ult = novo;
        novo->coef = aluno.coef;
        novo->matricula = aluno.matricula;
        novo->turma = aluno.turma;
        strcpy(novo->nome, aluno.nome);
        novo->prox = novo;
    }
    else{
        while(strcmp(atual->nome, aluno.nome)<0){
            aux = atual;
            atual = aux->prox;

            if(atual == prim)
                break;
        }
        if(aux == NULL){
            prim = novo;
            ult->prox = prim;
        }
        else{
            aux->prox = novo;
        }

        novo->coef = aluno.coef;
        novo->matricula = aluno.matricula;
        novo->turma = aluno.turma;
        strcpy(novo->nome, aluno.nome);
        novo->prox = atual;

        if(atual==prim){
            ult = novo;
        }
    }
    return true;
}

void imprimeLista(){
    noAluno *atual = prim;
    if(atual!=NULL){
        while(true){
            printf("\n\nNome: %s", atual->nome);
            printf("\nMatrícula: %d", atual->matricula);
            printf("\nTurma: %d", atual->turma);
            printf("\nCoeficiente: %f", atual->coef);
            atual = atual->prox;

            if(atual == prim)
                break;
        }
    }
}

bool removeAluno(int matricula){
    noAluno *aux = NULL;
    noAluno *atual=prim;
    while(atual->matricula!=matricula){
        aux = atual;
        atual = atual->prox;

        if(atual == prim)
            break;
    }
    if(atual->matricula != matricula) return false;
    else{
        if(atual == prim){
            prim = atual->prox;
            ult->prox = prim;
            free(atual);
        }
        else {
            aux->prox = atual->prox;
            if(atual == ult){
                ult = aux;
            }
            free(atual);
        }
        return true;
    }
}

int buscaMatricula(int matricula){
    int i=0;
    noAluno *atual = prim;
    if(atual!= NULL){
        while(atual->matricula != matricula){
            atual = atual->prox;
            i++;

            if(atual = prim){
                break;
            }
        }
        if(atual->matricula!= matricula){
            return -1;
        }
        else{
            return i;
        }
    }
    else{
        return -1;
    }
}
