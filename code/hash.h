#ifndef hash_h
#define hash_h

#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DEPTH 255
#define LEFT_JUMP 0
#define RIGHT_JUMP 1
#define START_JUMP -1


/**
 * @brief struct do nó da hash table
 * 
 */
typedef struct hash_node
{
    void *key;
    int depth;
    unsigned long frequency;
    bool bits[MAX_DEPTH];
} hash_node;


/**
 * @brief struct da hash table
 * 
 */
typedef struct hash_table
{
    hash_node *table[256];
    int size;
} hash;


/**
 * @brief Cria uma hash table cujos elementos são ponteiros para NULL
 * 
 * @return O ponteiro para a hash table
 */
hash *create_hash_table();


/**
 * @brief Imprime o array "bits" na tela
 * 
 * @param bits Um array de bits
 * @param size O tamanho do array
 */
void print_bits(bool *bits, int size);

/**
 * @brief Coloca um novo elemento na hash table
 * 
 * @param hash O ponteiro para a hash table
 * @param key O ponteiro para void do item de uma folha na árvore 
 * @param depth A profundidade da folha para salvar na hash table
 * @param frequency the frequency do item na folha para salvar na hash table
 * @param bits Um array de bits para salvar na hash table
 */
void put(hash *hash, void *key, int depth, unsigned long frequency, bool *bits);

/**
 * @brief Cria uma hash table a partir de folhas da árvore
 * 
 * @param tree O ponteiro da árvore
 * @param map O ponteiro da hash table
 * @param depth Um contador inteiro
 * @param bits Um array de bits a ser preenchido
 * @param jump A informação para preencher o array de bits
 * @param tree_size Um ponteiro de contador para inteiro para obter o tamanho da árvore
 */
void build_map(node *tree, hash *map, int depth, bool *bits, int jump, unsigned long *tree_size);

/**
 * @brief imprime a hash table na tela
 * 
 * @param hash O ponteiro apara a hash table
 */
void print_map(hash *hash);

//void deallocate_hash(hash *hash);

#endif