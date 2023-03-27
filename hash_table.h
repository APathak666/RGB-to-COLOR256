#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#define TABLE_SIZE 397  //setting hash table size to arbitrary prime
#define TABLE_INIT 0    //initialize HASH TABLE ENT
typedef struct node
{
    int val;
    int index;
    struct node *next;
}
node;

//Hash table to store compact RGB values
node *hashtable[TABLE_SIZE];

//function prototypes
void init_table();
void insert(int key, int idx);
int lookup(int key);
int compact(unsigned char* image, int index);
int hash(int compact);

#endif
