#ifndef tree_h
#define tree_h

#include <stdio.h>

/**
 * @brief struct da árvore
 * 
 */
typedef struct node
{
    void *item;
    unsigned long frequency;
    struct node *left;
    struct node *right;
} node;

/**
 * @brief Cria um nó de árvores cujos filhos são ponteiros para NULL
 * e guarda os valores de frequencia e o ponteiro para o item
 * 
 * @param item caractere a ser salvado no ponteiro para item do nó
 * @param frequency frequencia do caractere a ser salvada no nó
 * @return O ponteiro para a árvore
 */
node *create_node_test(unsigned char item, unsigned long frequency);

/**
 * @brief Cria um nó de árvores cujos filhos são ponteiros para NULL
 * e aloca 2 bytes para o ponteiro para void de items
 * 
 * @return O ponteiro para a árvore
 */
node *create_node();


/**
 * @brief Cria uma árvore cujos filhos são "left" e "right"
 * 
 * @param item ponteiro para o item
 * @param left filho da esquerda
 * @param right filho da direita
 * @return ponteiro para a árvore
 */
node *create_tree(void *item, node *left, node *right);


/**
 * @brief imprime a árvore na tela
 * 
 * @param tree ponteiro para a árvore
 */
void print_tree(node *tree);


/**
 * @brief Salva a árvore no arquivo
 * 
 * @param tree ponteiro para a árvore
 * @param compacted_file ponteiro para o arquivo
 */
void save_tree(node *tree, FILE *compacted_file);


/**
 * @brief aloca um espaço para um contador que inicia de zero
 * 
 * @return O ponteiro do contador
 */
unsigned long *allocate_counter();

//void deallocate_tree(node *tree);

#endif