# Trabalho de implementação: Agenda - AED I
Nome: Silvana Dias
Turma: M2

O código implementa uma agenda de pessoas utilizando apenas um único bloco de memória (pBuffer) e manipulação manual de ponteiros.
O programa permite adicionar, remover, buscar e listar pessoas, armazenando todos os dados dinamicamente em um buffer contínuo.

O pBuffer armazena:
- Quantidade de pessoas cadastradas (int)
- Lista de pessoas, cada uma contendo:
Nome (50 chars)
Idade (int)
Email (50 chars)

A memória é redimensionada com realloc() toda vez que uma pessoa é adicionada ou removida.

# Funcionalidades

- Adicionar pessoa
Expande o buffer e grava nome, idade e email no final.

- Remover pessoa
Localiza pelo nome, remove e move os elementos seguintes com memmove().

- Buscar pessoa
Percorre o buffer e exibe os dados se encontrar o nome.

- Listar todas
Imprime todo o conteúdo cadastrado.

# Complexidade

- Tempo: O(n) para adicionar, remover, buscar e listar.
- Espaço: O(n), proporcional ao número de pessoas armazenadas.
