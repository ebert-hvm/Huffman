#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

hash *create_hash_table()
{
    hash *new_hash = (hash *)malloc(sizeof(hash));
    int i;
    for (i = 0; i < 256; i++)
    {
        new_hash->table[i] = NULL;
    }
    new_hash->size = 0;
    return new_hash;
}

void print_bits(bool *bits, int size)
{
    for (int i = 1; i <= size; i++)
    {
        if (bits[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");
    printf("depth : %d\n", size);
}

void put(hash *hash, void *key, int depth, unsigned long frequency, bool *bits)
{
    if (hash->size >= 256)
    {
        //printf("hash table overflow\n");
    }
    else
    {
        int h;
        if(*(unsigned char *)key != '\\') h = *(unsigned char *)key;
        else h = *((unsigned char *)key + 1);

        hash_node *new_hash_node = (hash_node *)malloc(sizeof(hash_node));
        new_hash_node->key = key;
        new_hash_node->depth = depth;
        new_hash_node->frequency = frequency;
        for (int i = 0; i < depth; i++)
        {
            new_hash_node->bits[i] = bits[i];
        }
        hash->table[h] = new_hash_node;
        hash->size++;
    }
}

void build_map(node *tree, hash *map, int depth, bool *bits, int jump, unsigned long* tree_size)
{
    *tree_size+= 1;
    
    if(jump == START_JUMP && *(unsigned char*)tree->item != '*')
    {
        bits[0] = 1;
        put(map, tree->item, 1, tree->frequency, bits);
    }
    else
    {
        if (jump != START_JUMP)
            bits[depth] = jump;
        if (*(unsigned char *)tree->item == '*')
        {
            build_map(tree->left, map, depth + 1, bits, LEFT_JUMP, tree_size);
            build_map(tree->right, map, depth + 1, bits, RIGHT_JUMP, tree_size);
        }
        else
        {
            put(map, tree->item, depth + 1, tree->frequency, bits);
        }
    }
}

void print_map(hash* hash)
{
    //printf("blz\n");
    for(int i =0; i<256;i++)
    {
        if(hash->table[i]==NULL) printf(" %d (NULL)\n", i);
        else
        {
            printf("%d | key %c | depth %d | frequency %ld | bits ", i, *(unsigned char*)hash->table[i]->key, hash->table[i]->depth, hash->table[i]->frequency);
            for(int j=0;j<hash->table[i]->depth; j++)
            {
                printf("%d", hash->table[i]->bits[j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

