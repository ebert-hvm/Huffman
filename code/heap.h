#ifndef heap_h
#define heap_h

#include "tree.h"

#include <stdlib.h>
#include <limits.h>



/**
 * @brief Struct da Heap
 * 
 */
typedef struct heap
{
    int size; 
    node *nodes[257];
} heap;


/**
 * @brief Monta a heap
 * 
 * @return Retorna o ponteiro pra Heap 
 */
heap *create_heap();


/**
 * @brief Pega o índice do nó Pai
 * 
 * @param heap O ponteiro para Heap
 * @param i Índice
 * @return Retorna o índice do nó Pai 
 */
int get_parent_index(heap *heap, int i);


/**
 * @brief Pega o índice do filho da esquerda
 * 
 * @param heap O ponteiro para Heap
 * @param i Índice
 * @return Retorna o índice do filho da esquerda  
 */
int get_left_index(heap *heap, int i);


/**
 * @brief Pega o índice do filho da direita
 * 
 * @param heap O ponteiro para Heap
 * @param i Índice
 * @return Retorna o índice do filho da direita 
 */
int get_right_index(heap *heap, int i);
/**
 * @brief Troca os valores contidos em dois ponteiros para void
 * 
 * @param u O ponteiro para void 
 * @param v O ponteiro para void
 * @param len O tamanho do dado dos ponteiros
 */
void swap(void *u, void *v, size_t len);


/**
 * @brief Imprime a Heap
 * 
 * @param heap O ponteiro para Heap
 */
void print_heap(heap *heap);


/**
 * @brief Ajeita a estrutura da Heap a partir do índice restaurando suas propriedades
 * 
 * @param heap O ponteiro para Heap
 * @param i Índice
 */
void min_heapify(heap *heap, int i);


/**
 * @brief Verifica se o item está na Heap
 * 
 * @param heap O ponteiro para Heap
 * @param item Item a ser verificado
 * @return Retorna a posição do item na Heap
 */
int is_in_heap(heap *heap, void *item);


/**
 * @brief Enfileira o nó na Heap enquanto não estiver cheia
 * 
 * @param heap O ponteiro para Heap
 * @param new_node Nó para árvore
 */
void enqueue(heap *heap, node *new_node);


/**
 * @brief Desenfileira o primeiro nó da Heap
 * 
 * @param heap O ponteiro para Heap 
 * @return Retorna o item desnfileirado e quando a Heap está vazia retorna NULL 
 */
node *dequeue(heap *heap);



#endif