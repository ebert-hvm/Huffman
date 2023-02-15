#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "tree.h"
#include "heap.h"
#include "hash.h"

#include "compactor.h"



int check_path()
{
    FILE *path_file = fopen("file_path.txt", "r");
    char path[150];
    fscanf(path_file, "%s", path);
    fclose(path_file);

    FILE* file = fopen(path, "r");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);

        if (size == 0)
        {
            system("clear");
            printf("\033[0;31m"); //Set the text to the color red
            printf("ERRO!");
            printf("\033[0m"); //Resets the text to default color
            printf(" O arquivo a compactar está vazio. Por favor checar \"file_path.txt\"\n");
            return ERROR;
        }
        else
        {
            return !ERROR;
        }
    }
    else
    {
        system("clear");
        printf("\033[0;31m"); //Set the text to the color red
        printf("ERRO!");
        printf("\033[0m"); //Resets the text to default color
        printf(" O arquivo a compactar não existe. Por favor checar \"file_path.txt\"\n");
        return ERROR;
    }
    
}

void get_trash_size(hash *map, unsigned long *trash_size)
{
    for (int i = 0; i < 256; i++)
    {
        if (map->table[i] != NULL)
        {
            *trash_size += map->table[i]->depth * map->table[i]->frequency;
        }
    }
    *trash_size = (8 - *trash_size % 8) % 8;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << 7 - i;
    return mask | c;
}

void save_first_2_bytes(unsigned long *trash_size, unsigned long *tree_size, FILE *compacted_file)
{
    unsigned char ch1 = 0, ch2 = 0;
    //printf("trash size %d\ntree size %d\n", *trash_size, *tree_size);
    ch2 += *tree_size;
    *tree_size >>= 8;
    ch1 += *tree_size;
    ch1 += *trash_size << 5;
    //printf("chars %d %d\n", ch1, ch2);
    fprintf(compacted_file, "%c%c", ch1, ch2);
}

void save_file(hash *map, FILE *compacted_file)
{
    unsigned char ch, compacted_ch = 0;
    int set_bit_index = 0, bits_index = 0;

    char path_string[150];
    FILE *path = fopen("file_path.txt", "r");
    fscanf(path, "%s", path_string);
    fclose(path);
    FILE *file_to_compact = fopen(path_string, "r");

    while (fscanf(file_to_compact, "%c", &ch) != EOF)
    {

        for (bits_index = 0; bits_index < map->table[ch]->depth; bits_index++)
        {
            if (map->table[ch]->bits[bits_index])
            {
                //printf("1");
                compacted_ch = set_bit(compacted_ch, set_bit_index);
            }
            else
            {
                //printf("0");
            }
            if (set_bit_index == 7)
            {
                fprintf(compacted_file, "%c", compacted_ch);
                compacted_ch = 0;
                //printf(" ");
            }
            set_bit_index = (set_bit_index + 1) % 8;
        }
    }
    //printf("\nultimo set_bit_index: %d\nch: %d\n", set_bit_index, compacted_ch);
    if (set_bit_index != 0)
        fprintf(compacted_file, "%c", compacted_ch);

    fclose(file_to_compact);
}

node *build_tree(heap *heap)
{

    unsigned char ch;
    char path_string[150];
    FILE *path = fopen("file_path.txt", "r");
    fscanf(path, "%s", path_string);
    fclose(path);
    printf("\nLendo arquivo...\n");
    FILE *file = fopen(path_string, "r");

    while (fscanf(file, "%c", &ch) != EOF)
    {
        node *node = create_node();
        if (ch == '*')
        {
            *(unsigned char *)node->item = '\\';
            *((unsigned char *)node->item + 1) = '*';
        }
        else if (ch == '\\')
        {
            *(unsigned char *)node->item = '\\';
            *((unsigned char *)node->item + 1) = '\\';
        }
        else
        {
            *(unsigned char *)node->item = ch;
        }
        enqueue(heap, node);
    }
    fclose(file);
    //print_heap(heap);    
    printf("\nConstruindo árvore...\n");
    node *left, *right, *parent;
    while (heap->size != 1)
    {
        left = dequeue(heap);
        right = dequeue(heap);
        parent = create_node();
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;
        enqueue(heap, parent);
    }
    node *returned = dequeue(heap);
    return returned;
}

void compact()
{
    if(check_path() != ERROR)
    {
        heap *heap = create_heap();
        node *tree = build_tree(heap);
        printf("\nÁrvore feita\n");
        //print_tree(tree);
        //printf("\n\n");

        hash *map = create_hash_table();
        bool bits[MAX_DEPTH];
        unsigned long *tree_size, *trash_size;
        tree_size = allocate_counter();
        trash_size = allocate_counter();
        printf("\nConstruindo hash table...\n");
        build_map(tree, map, -1, bits, START_JUMP, tree_size);
        printf("\nHash table feita.\n");
        //print_map(map);
        printf("\nObtendo o tamanho do lixo...\n");
        get_trash_size(map, trash_size);
        //printf("tree size: %d, trash size: %d\n\n", *tree_size, *trash_size);

        FILE *path_fp = fopen("file_path.txt", "r");
        char path[150];
        fscanf(path_fp, "%s", path);
        fclose(path_fp);
        
        strcat(path, ".huff");
        FILE *compacted_file = fopen(path, "w");
        FILE *comp_path_fp  = fopen("compacted_file_path.txt", "w");
        fprintf(comp_path_fp, "%s", path);
        fclose(comp_path_fp);

        printf("\nSalvando...\n");
        system("clear");
        save_first_2_bytes(trash_size, tree_size, compacted_file);
        save_tree(tree, compacted_file);
        //deallocate_heap(heap);
        save_file(map, compacted_file);
        fclose(compacted_file);
        //deallocate_hash(map);
        printf("Compactação finalizada. ");
    }
}