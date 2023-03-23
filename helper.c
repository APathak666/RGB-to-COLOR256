#include <stdio.h>
#include "helper.h"
#include "hash_table.h"

int ERRNO = 0;

//set global error number and print error message
void error_handler(int error, char* str)
{
    ERRNO = error;
    printf("Error: %s | %d\n", str, ERRNO);
}

//function to test other functions
void test_func()
{
    // unsigned char image_rgb[] = {255, 0, 0, 0, 255, 0, 0, 0, 255,
    //                             0, 0, 255, 0, 255, 0, 255, 0, 0,
    //                             0, 255, 0, 255, 0, 0, 0, 0, 255};

    // unsigned char* new = image_rgb_to_color256(3, 3, image_rgb);

    // print_arr(new, PALETTE_MAX*RGB_TUPLE_SIZE + 9);
    // printf("%d ", PALETTE_MAX*RGB_TUPLE_SIZE + 9);

    init_table();

    for (int i = 0; i < TABLE_SIZE; i++)
        insert(i, i);

    for (int i = TABLE_SIZE; i < 2*TABLE_SIZE; i++)
        insert(i, i);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        print_list(hashtable[i]);
    }
}

//utility function to print array
void print_arr(unsigned char* buf, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", buf[i]);
    }
}

//utility function to print linked list
void print_list(node* start)
{
    node* cursor = start;

    while(cursor != NULL)
    {
        printf("%d ", cursor->val);
        cursor = cursor->next;
    }

    printf("\n");
}

//extract RGB values from 9 digit int representation (RRR_GGG_BBB)
void unpack(int compact)
{
    blue = compact%1000;
    green = (compact%1000000 - blue)/1000;
    red = compact/1000000;

}