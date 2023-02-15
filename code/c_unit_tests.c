/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "tree.h"
#include "heap.h"
#include "hash.h"

/* Pointer to the file used by the tests. */
static FILE *temp_file = NULL;
heap *h;
unsigned char str[50];
node* returned;


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if (NULL == (temp_file = fopen("temp.txt", "w+")))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (0 != fclose(temp_file))
    {
        return -1;
    }
    else
    {
        temp_file = NULL;
        return 0;
    }
}

void enqueue_heap()
{
    enqueue(h, create_node_test('A', 10000));
    enqueue(h, create_node_test('B', 613));
    enqueue(h, create_node_test('C', 137));
    enqueue(h, create_node_test('D', 4238));
    enqueue(h, create_node_test('E', 480));
    enqueue(h, create_node_test('F', 257));
}

void test_heap_creation()
{
    h = create_heap();
    CU_ASSERT(h->size == 0);
    for (int i = 1; i <= 256; i++)
    {
     
        CU_ASSERT_EQUAL('*', *(unsigned char *)h->nodes[i]->item);
        CU_ASSERT_EQUAL(h->nodes[i]->frequency, 1);
        CU_ASSERT_EQUAL(h->nodes[i]->left, NULL);
        CU_ASSERT_EQUAL(h->nodes[i]->right, NULL);
    }
}

void test_enqueue()
{
    enqueue_heap();
    CU_ASSERT_EQUAL(h->nodes[1]->frequency , 137);
    CU_ASSERT_EQUAL(*(unsigned char*)h->nodes[1]->item, 'C');
    CU_ASSERT_EQUAL(h->nodes[2]->frequency, 480);
    CU_ASSERT_EQUAL(*(unsigned char *)h->nodes[2]->item, 'E');
    CU_ASSERT_EQUAL(h->nodes[3]->frequency, 257);
    CU_ASSERT_EQUAL(*(unsigned char *)h->nodes[3]->item, 'F');
    CU_ASSERT_EQUAL(h->nodes[4]->frequency, 10000);
    CU_ASSERT_EQUAL(*(unsigned char *)h->nodes[4]->item, 'A');
    CU_ASSERT_EQUAL(h->nodes[5]->frequency, 4238);
    CU_ASSERT_EQUAL(*(unsigned char *)h->nodes[5]->item, 'D');
    CU_ASSERT_EQUAL(h->nodes[6]->frequency, 613);
    CU_ASSERT_EQUAL(*(unsigned char *)h->nodes[6]->item, 'B');
}

void test_dequeue()
{
    node *dequeued;
    
    dequeued = dequeue(h);
    print_heap(h);
    CU_ASSERT_EQUAL(dequeued->frequency, 137);
    CU_ASSERT_EQUAL(*(unsigned char *)dequeued->item, 'C');
    dequeued = dequeue(h);
    CU_ASSERT_EQUAL(dequeued->frequency, 257);
    CU_ASSERT_EQUAL(*(unsigned char *)dequeued->item, 'F');
    dequeued = dequeue(h);
    CU_ASSERT_EQUAL(dequeued->frequency, 480);
    CU_ASSERT_EQUAL(*(unsigned char *)dequeued->item, 'E');
    dequeued = dequeue(h);
    CU_ASSERT_EQUAL(dequeued->frequency, 613);
    CU_ASSERT_EQUAL(*(unsigned char *)dequeued->item, 'B');
    dequeued = dequeue(h);
    CU_ASSERT_EQUAL(dequeued->frequency, 4238);
    CU_ASSERT_EQUAL(*(unsigned char *)dequeued->item, 'D');
    dequeued = dequeue(h);
    CU_ASSERT_EQUAL(dequeued->frequency, 10000);
    CU_ASSERT_EQUAL(*(unsigned char *)dequeued->item, 'A');
    dequeued = dequeue(h);
    CU_ASSERT_EQUAL(dequeued, NULL);
}

void check_tree(node *tree)
{
    if (tree != NULL)
    {
        if (*(unsigned char *)tree->item == '\\')
        {
            int size = strlen(str);
            str[size] = *(unsigned char *)tree->item;
            str[size + 1] = *((unsigned char *)tree->item + 1);
            str[size + 2] = '\0';
            check_tree(tree->left);
            check_tree(tree->right);
        }
        else
        {
            int size = strlen(str);
            str[size] = *(unsigned char *)tree->item;
            str[size+1] = '\0';
            check_tree(tree->left);
            check_tree(tree->right);
        }
    }
}

void test_tree_building()
{
    enqueue_heap();
    str[0] = '\0';
    node *left, *right, *parent;
    while (h->size != 1)
    {
        left = dequeue(h);
        right = dequeue(h);
        parent = create_node();
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;
        enqueue(h, parent);
    }
    returned = dequeue(h);
    check_tree(returned);
    CU_ASSERT_EQUAL(0, strcmp(str, "***B**CFEDA"));
}

void test_hash_table()
{
    unsigned long *tree_size = allocate_counter();
    bool bits[MAX_DEPTH];
    hash *map = create_hash_table();
    build_map(returned, map, -1, bits, START_JUMP, tree_size);
    int i;
    for(i=0;i<=64;i++)
    {
        CU_ASSERT(map->table[i] == NULL);
    }
    for(i=65;i<=70;i++)
    {
        CU_ASSERT(*(unsigned char*)map->table[i]->key == i);
    }
    for (i = 71; i <256; i++)
    {
        CU_ASSERT(map->table[i] == NULL);
    }
}

    /* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if (NULL == CU_add_test(pSuite, "testing heap creation", test_heap_creation))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "testing enqueue", test_enqueue))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "testing dequeue", test_dequeue))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "testing tree building", test_tree_building))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "testing hash table building", test_hash_table))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
