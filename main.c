#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "hash_table.h"
#include "inputs.h"

//Driver code
int main()
{
    // test_func();
    int dim_x = 3, dim_y = 3;
    unsigned char* image_color256 = image_rgb_to_color256(dim_x, dim_y, image_rgb);

    printf("Color palette: ");
    print_arr(image_color256, 0, PALETTE_MAX*RGB_TUPLE_SIZE);
    printf("Color indices: ");
    print_arr(image_color256, PALETTE_MAX*RGB_TUPLE_SIZE, PALETTE_MAX*RGB_TUPLE_SIZE + dim_x*dim_y);
}

//Convert image from RGB representation to COLOR256 format
unsigned char* image_rgb_to_color256(unsigned int dim_x, unsigned int dim_y, unsigned char* image_buf)
{
    int in_size = RGB_TUPLE_SIZE*dim_x*dim_y;                   //input total size
    int color_count = 0, offset = PALETTE_MAX*RGB_TUPLE_SIZE;   //offset for color indices
    int palette_index = 0;                                      //color indices in palette
    int curr_compact;                                           //stores the compact value of the current RGB pixel
    int find;                                                   //index of compact in hash table, else -1

    //check for NULL buffer
    if (image_buf == NULL)
    {
        error_handler(INP_ERR, INP_MSG);
        return NULL;
    }

    //check dimensions
    if (dim_x == 0 || dim_y == 0) //|| dim_x*dim_y%3 != 0)
    {
        error_handler(DIM_ERR, DIM_MSG);
        return NULL;
    }

    //allocate memory for new image
    unsigned char* color256_img = image_color256(dim_x, dim_y);

    if (color256_img == NULL)
    {
        error_handler(BUFF_ERR, BUFF_MSG);
        return NULL;
    }

    for (int i = 0; i < in_size; i+= 3)
    {
        //read compact representation of RGB triplet
        curr_compact = compact(image_buf, i);
        find = lookup(curr_compact);

        if (find == -1) //if not already in hash table
        {
            //insert into hash table
            insert(curr_compact, color_count); 
            unpack(curr_compact);   //extract RGB values

            //insert new color into palette 
            color256_img[palette_index] = red;
            color256_img[palette_index+1] = green;
            color256_img[palette_index+2] = blue;

            //store index
            color256_img[(i/3)+offset] = color_count;
            color_count++;
            palette_index += 3;
        }
        else    //if already in hash table
        {
            unpack(curr_compact);
            //store previously occurred index
            color256_img[(i/3)+offset] = find;
        }

        //check color count isn't greater than max palette size
        if (color_count > PALETTE_MAX)
        {
            error_handler(PALETTE_ERR, PALETTE_MSG);
            return NULL;
        }
    }

    return color256_img;
}   //image_rgb_to_color256()

//Initialize COLOR256 format image
unsigned char* image_color256(unsigned int dim_x, unsigned int dim_y)
{
    //calculate total size of COLOR256 table
    int final_size = PALETTE_MAX*RGB_TUPLE_SIZE + dim_x*dim_y;

    //check dimensions
    if (dim_x == 0 || dim_y == 0)
    {
        error_handler(DIM_ERR, DIM_MSG);
        return NULL;
    }

    //allocate memory for COLOR256 table
    unsigned char* img = malloc(final_size*sizeof(unsigned char));

    if (img == NULL)
    {
        error_handler(MALLOC_ERR, MALLOC_MSG);
        exit(1);
    }

    //initialize all values to zero
    memset(img, 0, final_size*sizeof(unsigned char));

    return img;
}   //image_color256()
