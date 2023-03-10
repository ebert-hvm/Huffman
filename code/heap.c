#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "heap.h"

heap *create_heap()
{
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->size = 0;
    for (int i = 1; i <= 256; i++)
    {
        new_heap->nodes[i] = create_node();
    }
    return new_heap;
}

int get_parent_index(heap *heap, int i)
{
    return i / 2;
}
int get_left_index(heap *heap, int i)
{
    return 2 * i;
}
int get_right_index(heap *heap, int i)
{
    return 2 * i + 1;
}

void swap(void *u, void *v, size_t len)
{
    unsigned char *p = u, *q = v, aux;
    for (size_t i = 0; i < len; i++)
    {
        aux = p[i];
        p[i] = q[i];
        q[i] = aux;
    }
}

void print_heap(heap *heap)
{
    int i;
    printf("\nheap size: %d\n", heap->size);
    for (i = 1; i <= heap->size; i++)
    {
        if (*(unsigned char *)heap->nodes[i]->item == '\\')
        {
            if (i == heap->size)
                printf("%c%c %ld\n", *(unsigned char *)heap->nodes[i]->item, *((unsigned char *)heap->nodes[i]->item + 1), heap->nodes[i]->frequency);
            else
                printf("%c%c %ld| ", *(unsigned char *)heap->nodes[i]->item , * ((unsigned char *)heap->nodes[i]->item + 1), heap->nodes[i]->frequency);
        }
        else
        {
            if (i == heap->size)
                printf("%c %ld\n", *(unsigned char *)heap->nodes[i]->item, heap->nodes[i]->frequency);
            else
                printf("%c %ld| ", *(unsigned char *)heap->nodes[i]->item, heap->nodes[i]->frequency);
        }
    }
    printf("\n");
}

void min_heapify(heap *heap, int i)
{
    int smaller_index;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);
    if (left_index <= heap->size && heap->nodes[left_index]->frequency <= heap->nodes[i]->frequency)
    {
        smaller_index = left_index;
    }
    else
    {
        smaller_index = i;
    }
    if (right_index <= heap->size && heap->nodes[right_index]->frequency <= heap->nodes[smaller_index]->frequency)
    {
        smaller_index = right_index;
    }
    if (i != smaller_index)
    {
        swap(heap->nodes[i], heap->nodes[smaller_index], sizeof(node));
        min_heapify(heap, smaller_index);
    }
}

int is_in_heap(heap *heap, void *item)
{
    int i;
    if (*(unsigned char *)item == '*') return 0;
    for (i = 1; i <= heap->size ; i++)
    {
        if (*(unsigned char *)item == '\\' && *(unsigned char *)heap->nodes[i]->item == '\\')
        {
            if(*((unsigned char *)heap->nodes[i]->item + 1) == *((unsigned char *)item + 1)) return i;
        }
        else if (*(unsigned char *)heap->nodes[i]->item == *(unsigned char *)item) return i;
    }
    return 0;
}

void enqueue(heap *heap, node *new_node)
{
    int i;
    i = is_in_heap(heap, new_node->item);
    if (i)
    {
        heap->nodes[i]->frequency++;
        min_heapify(heap, i);
        free(new_node);
    }
    else
    {
        if (heap->size >= 256)
        {
            //printf("Heap overflow");
        }
        heap->size++;
        heap->nodes[heap->size] = new_node;
        int key_index = heap->size;
        int parent_index = get_parent_index(heap, heap->size);
        while (parent_index >= 1 && heap->nodes[key_index]->frequency <= heap->nodes[parent_index]->frequency)
        {
            swap(heap->nodes[key_index], heap->nodes[parent_index], sizeof(node));
            key_index = parent_index;
            parent_index = get_parent_index(heap, key_index);
        }
    }
    //print_heap(heap);
}

node *dequeue(heap *heap)
{
    if (heap->size == 0)
    {
       // printf("Heap underflow");
        return NULL;
    }
    else
    {

        node *dequeued = heap->nodes[1];
        heap->nodes[1] = heap->nodes[heap->size];
        heap->size--;
        min_heapify(heap, 1);
        return dequeued;
    }
}

