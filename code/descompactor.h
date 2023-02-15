#ifndef descompactor_h
#define descompactor_h
#define ERROR 1

#include <stdio.h>
#include <stdlib.h>


#include "tree.h"



/**
 * @brief checa se um bit vale 1
 * 
 * @param c caractere a ser checado
 * @param i posição, da esquerda para a direita, do bit a ser checado
 * @return "1", caso o bit valha 1, e "0" , caso contrário
 */
int is_bit_i_set(unsigned char c, int i);

/**
 * @brief lê os primeiros dois bytes do arquivo compactado
 * 
 * @param file arquivo compactado
 * @param trash_size contador do tamanho do lixo
 * @param tree_size contador do tamanho da árvore
 */
void read_first_two_bytes(FILE *file, unsigned long *trash_size, unsigned long *tree_size);

/**
 * @brief lê os caracteres da árvore escrita em pre-órdem no arquivo
 * 
 * @param file arquivo para ler
 * @return O ponteiro para a árvore
 */
node *read_tree(FILE *file);

/**
 * @brief lê o arquivo compactado e salva o arquivo descompactado
 * 
 * @param tree árvore para decodificar o arquivo compactado
 * @param trash_size tamanho do lixo
 * @param file arquivo compactado
 */
void read_file(node *tree, unsigned long trash_size, FILE *file);

/**
 * @brief descompacta o arquivo lido em "compacted_file_path"
 * e salva em "../files/
 * 
 */
void descompact();

#endif