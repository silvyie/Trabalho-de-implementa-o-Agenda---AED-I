#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
===========================================================================
*pBuffer, variável global
===========================================================================
*/

#define TAM_NOME 50
#define TAM_EMAIL 50
#define TAM_PESSOA (TAM_NOME + sizeof(int) + TAM_EMAIL)

void *pBuffer;

/*
===========================================================================
Função adicionar_pessoa: Função principal, essa função aumenta o tamanho do buffer.
===========================================================================
*/

void adicionar_pessoa(void **pBuffer) {
    *pBuffer = realloc(*pBuffer, sizeof(int) + (*((int *)(*pBuffer)) + 1) * TAM_PESSOA);
    if (*pBuffer == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    (*((int *)(*pBuffer)))++;
    void *pPessoa = (char *)(*pBuffer) + sizeof(int) + ((*((int *)(*pBuffer)) - 1) * TAM_PESSOA);

    printf("Nome: ");
    fgets((char *)pPessoa, TAM_NOME, stdin);
    ((char *)pPessoa)[strcspn((char *)pPessoa, "\n")] = 0;

    pPessoa = (char *)pPessoa + TAM_NOME;
    printf("Idade: ");
    scanf("%d", (int *)pPessoa);
    getchar();
    
    pPessoa = (char *)pPessoa + sizeof(int);
    printf("Email: ");
    fgets((char *)pPessoa, TAM_EMAIL, stdin);
    ((char *)pPessoa)[strcspn((char *)pPessoa, "\n")] = 0;
}

/*
===========================================================================
Função remover_pessoa: O nome digitado fica temporariamente armazenado no final do 
buffer esperando ser encontrado para ser removido.
===========================================================================
*/

void remover_pessoa(void **pBuffer) {
    if (*((int *)(*pBuffer)) == 0) {
        printf("Nenhuma pessoa cadastrada para remover.\n");
        return;
    }
    
    printf("Digite o nome da pessoa a remover: ");
    fgets((char *)(*pBuffer) + sizeof(int) + (*((int *)(*pBuffer))) * TAM_PESSOA, TAM_NOME, stdin);
    ((char *)(*pBuffer) + sizeof(int) + (*((int *)(*pBuffer))) * TAM_PESSOA)[strcspn((char *)(*pBuffer) + sizeof(int) + (*((int *)(*pBuffer))) * TAM_PESSOA, "\n")] = 0;
    
    void *pPessoa = (char *)(*pBuffer) + sizeof(int);
    while (*((int *)(*pBuffer))) {
        if (strcmp((char *)pPessoa, (char *)(*pBuffer) + sizeof(int) + (*((int *)(*pBuffer))) * TAM_PESSOA) == 0) {
            memmove(pPessoa, (char *)pPessoa + TAM_PESSOA, (*((int *)(*pBuffer)) - 1) * TAM_PESSOA);
            (*((int *)(*pBuffer)))--;
            *pBuffer = realloc(*pBuffer, sizeof(int) + (*((int *)(*pBuffer))) * TAM_PESSOA);
            printf("Pessoa removida com sucesso.\n");
            return;
        }
        pPessoa = (char *)pPessoa + TAM_PESSOA;
    }
    printf("Pessoa nao encontrada.\n");
}

/*
===========================================================================
Função buscar_pessoa: O ponteiro começa na primeira pessoa, depois faz a compração 
com o nome buscado, e quando acha os dados são exibidos.
===========================================================================
*/

void buscar_pessoa(void *pBuffer) {
    if (*((int *)pBuffer) == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    
    printf("Digite o nome da pessoa que deseja buscar: ");
    fgets((char *)pBuffer + sizeof(int) + (*((int *)pBuffer)) * TAM_PESSOA, TAM_NOME, stdin);
    ((char *)pBuffer + sizeof(int) + (*((int *)pBuffer)) * TAM_PESSOA)[strcspn((char *)pBuffer + sizeof(int) + (*((int *)pBuffer)) * TAM_PESSOA, "\n")] = 0;
    
    void *pPessoa = (char *)pBuffer + sizeof(int);
    while (*((int *)pBuffer)) {
        if (strcmp((char *)pPessoa, (char *)pBuffer + sizeof(int) + (*((int *)pBuffer)) * TAM_PESSOA) == 0) {
            printf("Nome: %s\n", (char *)pPessoa);
            pPessoa = (char *)pPessoa + TAM_NOME;
            printf("Idade: %d\n", *((int *)pPessoa));
            pPessoa = (char *)pPessoa + sizeof(int);
            printf("Email: %s\n", (char *)pPessoa);
            return;
        }
        pPessoa = (char *)pPessoa + TAM_PESSOA;
    }
    printf("Pessoa nao encontrada.\n");
}

/*
===========================================================================
Função listar_pessoas: O ponteiro aponta pro primeiro do cadastro, percorre a lista
e exibe todas as pessoas.
===========================================================================
*/

void listar_pessoas(void *pBuffer) {
    if (*((int *)pBuffer) == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    
    void *pPessoa = (char *)pBuffer + sizeof(int);
    while (*((int *)pBuffer)) {
        printf("Nome: %s\n", (char *)pPessoa);
        pPessoa = (char *)pPessoa + TAM_NOME;
        printf("Idade: %d\n", *((int *)pPessoa));
        pPessoa = (char *)pPessoa + sizeof(int);
        printf("Email: %s\n", (char *)pPessoa);
        pPessoa = (char *)pPessoa + TAM_EMAIL;
        printf("-------------------\n");
        (*((int *)pBuffer))--;
    }
}

/*
===========================================================================
Função Main: O switch-case lê a opção digitada pelo usuário e executa, quando o usuário
digita a opção 5(Sair), o free do buffer é ativado.
===========================================================================
*/

int main() {
    pBuffer = malloc(sizeof(int));
    if (pBuffer == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    *((int *)pBuffer) = 0;
    
    do {
        printf("1- Adicionar Pessoa\n2- Remover Pessoa\n3- Buscar Pessoa\n4- Listar todos\n5- Sair\nEscolha: ");
        fgets((char *)pBuffer + sizeof(int) + (*((int *)pBuffer)) * TAM_PESSOA, 10, stdin);
        switch (atoi((char *)pBuffer + sizeof(int) + (*((int *)pBuffer)) * TAM_PESSOA)) {
            case 1: adicionar_pessoa(&pBuffer); break;
            case 2: remover_pessoa(&pBuffer); break;
            case 3: buscar_pessoa(pBuffer); break;
            case 4: listar_pessoas(pBuffer); break;
            case 5: free(pBuffer); return 0;
            default: printf("Opcao invalida!\n");
        }
    } while (1);
}

