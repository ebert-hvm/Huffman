#ifndef compactor_h
#define compactor_h
#define ERROR 1

#include "heap.h"
#include "tree.h"




/**
 * @brief checa se o arquivo lido em "file_path.txt" está vazio
 * 
 * @return "ERROR" para um erro e "!ERROR" em qualquer outro caso
 */
int check_path();


/**
 * @brief Obtém o tamanho do lixo
 * 
 * @param map hash table para os cálculos necessários
 * @param trash_size contador para obter o tamanho do lixo
 */
void get_trash_size(hash *map, unsigned long *trash_size);

/**
 * @brief substitui um bit por 1 em um caractere
 * 
 * @param c Um caractere ou byte
 * @param i posição, da esquerda para a direita, do bit a substituir
 * @return o byte atualizado
 */
unsigned char set_bit(unsigned char c, int i);

/**
 * @brief Salva os dois primeiros bytes no arquivo compactado
 * 
 * @param trash_size ponteiro para o tamanho do lixo
 * @param tree_size ponteiro para o tamanho da árvore
 * @param compacted_file arquivo para salvar
 */
void save_first_2_bytes(unsigned long *trash_size, unsigned long *tree_size, FILE *compacted_file);

/**
 * @brief Salva os bytes do arquivo recém codificado no arquivo compactado
 * 
 * @param map hash table com as informações dos bytes do arquivo 
 * @param compacted_file arquivo para salvar
 */
void save_file(hash *map, FILE *compacted_file);

/**
 * @brief Cria uma heap a partir dos bytes do arquivo, e , a partir dela,
 * cria-se uma árvore cujas folhas são os diferentes bytes do arquivo
 * 
 * @return O ponteiro para a árvore pronta
 */
node *build_tree();

/**
 * @brief lê o arquivo a ser compactado em "file_path.txt" e salva na pasta
 * na mesma pasta com a extensção ".huff"
 * 
 */
void compact();

#endif