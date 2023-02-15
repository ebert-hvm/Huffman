#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "tree.h"
#include "heap.h"
#include "hash.h"

#include "descompactor.h"

int check()
{
    FILE *path_fp = fopen("compacted_file_path.txt", "r");
    char path_str[100];
    fgets(path_str, 100, path_fp);
    FILE *file = fopen(path_str, "r");
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
            printf("\n O arquivo a descompactar está vazio.\n");
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
        printf("\n\033[0;31m"); //Set the text to the color red
        printf("ERRO!");
        printf("\033[0m"); //Resets the text to default color
        printf("\n O arquivo a descompactar não existe.\n");
        return ERROR;
    }
}

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << 7 - i;
    return mask & c;
}

void read_first_two_bytes(FILE *file, unsigned long *trash_size, unsigned long *tree_size)
{
    unsigned char ch[2];
    fscanf(file, "%c%c", &ch[0], &ch[1]);
    
    if (is_bit_i_set(ch[0], 0)) *trash_size += 4;
    if (is_bit_i_set(ch[0], 1)) *trash_size += 2;
    if (is_bit_i_set(ch[0], 2)) *trash_size += 1;
    ch[0] <<= 3;
    *tree_size += ch[0];
    *tree_size <<= 5;
    *tree_size += ch[1];
}

node *read_tree(FILE *file)
{
    node *tree;
    unsigned char ch;
    fscanf(file, "%c", &ch);
    void *item = (void *)malloc(2 * sizeof(unsigned char));
    *(unsigned char *)item = ch;
    if (ch == '\\')
    {
        fscanf(file, "%c", &ch);
        *((unsigned char *)item + 1) = ch;
    }
    if (*(unsigned char *)item == '*')
    {
        node *left = read_tree(file);
        node *right = read_tree(file);
        tree = create_tree(item, left, right);
    }
    else
    {
        tree = create_tree(item, NULL, NULL);
    }
    return tree;
}

void read_file(node* tree, unsigned long trash_size, FILE *file)
{
    node* aux = tree;
    unsigned char ch, next_ch;

    FILE *path_fp = fopen("compacted_file_path.txt", "r");
    char path[100];
    fscanf(path_fp, "%s", path);
    int i = strlen(path);
    while(path[i] != '.')
    {
        i--;
    }
    path[i] = '\0';
    fclose(path_fp);

    FILE *descompacted_file = fopen(path, "w");
    fscanf(file, "%c", &ch);
    while (fscanf(file, "%c", &next_ch) != EOF)
    {
       for(int j=0; j< 8;j++)
       {
           if(aux != tree || *(unsigned char *)aux->item == '*') //Se não é raiz folha
           {
                if(is_bit_i_set(ch, j)) aux = aux->right;
                else aux = aux->left;
           }
           if (*(unsigned char *)aux->item != '*')
           {
               if(*(unsigned char *)aux->item == '\\') fprintf(descompacted_file, "%c", *((unsigned char *)aux->item + 1));
               else fprintf(descompacted_file, "%c", *(unsigned char *)aux->item);
               aux = tree;
           }
       }
       ch = next_ch;
    }
    for (int j = 0; j < 8- trash_size; j++)
    {
        if(aux != tree || *(unsigned char *)aux->item == '*')
        {
            if(is_bit_i_set(ch, j)) aux = aux->right;
            else aux = aux->left;
        }
        if (*(unsigned char *)aux->item != '*')
        {
            if (*(unsigned char *)aux->item == '\\') fprintf(descompacted_file, "%c", *((unsigned char *)aux->item + 1));
            else fprintf(descompacted_file, "%c", *(unsigned char *)aux->item);
            aux = tree;
        }
    }
    fclose(descompacted_file);
}

void descompact()
{
    if (check() != ERROR)
    {
        FILE *path_fp = fopen("compacted_file_path.txt", "r");
        char path[100];
        fscanf(path_fp, "%s", path);
        fclose(path_fp);
        FILE *file = fopen(path, "r");

        unsigned long *trash_size = allocate_counter(), *tree_size = allocate_counter();
        read_first_two_bytes(file, trash_size, tree_size);
        printf("Obtendo árvore...");
        node *tree = read_tree(file);
        //printf("trash size: %d\ntree size: %d\n", *trash_size, *tree_size);
        //print_tree(tree);
        printf("\n");
        printf("Descompactando arquivo...\n");
        read_file(tree, *trash_size, file);
        fclose(file);
        system("clear");
        printf("Descompactação finalizada. ");    
    }
}