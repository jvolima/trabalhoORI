# Trabalho final de organização e recuperação da informação

## Estruturas utilizadas
- Tabela hash
- Lista encadeada
- Lista sequencial dinâmica
- Set
- Árvore AVL

## Separação das pastas
- hash:
  - hash.c contém o código da tabela hash, utilizada para armazenar as palavras (cada palavra armazena o RRN da postagem a qual está associada)
  - lista.c contém o código da lista sequencial dinâmica, utilizada por cada nó da hash de encadeamento lógico
- set:
  - set.c contém o código da set, utilizada para armazenar o resultado da query
  - arvoreAvl.c: contém o código da árvore AVL, utilizada na set
- files:
  - corpus.csv: contém os dados do arquivo de postagens do twitter
  - teste.csv: contém parte dos dados do arquivo de postagens do twitter