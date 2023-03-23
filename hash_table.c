#include <stddef.h>
#include <stdlib.h>
#include "hash_table.h"
#include "helper.h"

//initialize all entries in hash table to NULL
void init_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
}

void insert(int key, int idx)
{
    //ensure hash value doesn't already exist in the table
    if (lookup(key) > -1)
    {
        error_handler(3, "Value already exists in table");
        return;
    }

    //hash compact value to find arrray index
    int hash_val = hash(key);
    node* cursor = hashtable[hash_val];

    //allocate space for new node
    node *new_node = malloc(sizeof(node));

    if (new_node == NULL)
    {
        error_handler(1, "allocating memory");
        exit(1);
    }

    //initialize new node
    new_node->val = key;
    new_node->index = idx;

    //insert in corresponding array index
    if (cursor == NULL)
    {
        hashtable[hash_val] = new_node;
        new_node->next = NULL;
    }

    else
    {
        new_node->next = hashtable[hash_val];
        hashtable[hash_val] = new_node;
    }
}

int lookup(int key)
{
    //hash compact value to find arrray index
    int hash_val = hash(key);
    node* cursor = hashtable[hash_val];

    //traverse linked list till either value is found or list end is reached
    while(cursor != NULL)
    {
        if (cursor->val == key)
        {
            return cursor->index;
        }

        else
        {
            cursor = cursor->next;
        }
    }

    return -1;
}

//  Represent 3 RGB fields in a single 9 digit int as: RRR_GGG_BBB for ease of hashing and lookup
int compact(unsigned char* image, int index)
{
    int com = 0;
    for (int i = 0; i < RGB_TUPLE_SIZE-1; i++, index++)
    {
        com += (int) image[index];
        com *= 1000;
    }

    com += (int) image[index];

    return com;
}

//modular hashing
int hash(int compact)
{
    return compact%TABLE_SIZE;
}
