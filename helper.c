#include <stdio.h>
#include "helper.h"
#include "hash_table.h"

int ERRNO = 0;

//Set global error number and print error message
void error_handler(int error, char* str)
{
    ERRNO = error;
    printf("Error: %s | %d\n", str, ERRNO);
}   //error_handler()

//Function to test other functions
void test_func()
{
    //TEST COLOR256 IMAGE INIT
    unsigned char image_rgb[] = {255, 0, 0, 0, 255, 0, 0, 0, 255,
                                0, 0, 255, 0, 255, 0, 255, 0, 0,
                                0, 255, 0, 255, 0, 0, 0, 0, 255};

    unsigned char* new = image_rgb_to_color256(3, 3, image_rgb);

    printf("%d ", PALETTE_MAX*RGB_TUPLE_SIZE + 9);

    //TEST HASH TABLE FUNCTIONS
    init_table();

    for (int i = 0; i < TABLE_SIZE; i++)
        insert(i, i);

    for (int i = TABLE_SIZE; i < 2*TABLE_SIZE; i++)
        insert(i, i);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        print_list(hashtable[i]);
    }

    printf("%d \n", lookup(500));
}   //test_func()

//Utility function to print array
void print_arr(unsigned char* buf, int start_idx, int end_idx)
{
    for (int i = start_idx; i < end_idx; i++)
    {
        printf("%d ", buf[i]);
    }

    printf("\n");
}   //print_arr()

//Utility function to print linked list
void print_list(node* start)
{
    node* cursor = start;

    while(cursor != NULL)
    {
        printf("%d ", cursor->val);
        cursor = cursor->next;
    }

    printf("\n");
}   //print_list()

//Extract RGB values from 9 digit int representation (RRR_GGG_BBB)
void unpack(int compact)
{
    blue = compact%1000;                    //extract 3 least significant digits
    green = (compact%1000000 - blue)/1000;  //extract middle 3 digits
    red = compact/1000000;                  //extract 3 most significant digits
}   //unpack()
