#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "hash_table.h"

int main()
{
    unsigned char image_rgb[] = {255, 0, 0, 0, 255, 0, 0, 0, 255,
                                0, 0, 255, 0, 255, 0, 255, 0, 0,
                                0, 255, 0, 255, 0, 0, 0, 0, 255};

    // test_func();
    image_rgb_to_color256(3, 3, image_rgb);
}

unsigned char* image_rgb_to_color256(unsigned int dim_x, unsigned int dim_y, unsigned char* image_buf)
{
    //check for NULL buffer
    if (image_buf == NULL)
    {
        error_handler(6, "NULL image received");
        return NULL;
    }

    //check dimensions
    if (dim_x == 0 || dim_y == 0)
    {
        error_handler(4, "incorrect dimensions");
        return NULL;
    }

    //allocate memory for new image
    unsigned char* color256_img = image_color256(dim_x, dim_y);

    if (color256_img == NULL)
    {
        error_handler(5 , "color");
        return NULL;
    }

    int in_size = RGB_TUPLE_SIZE*dim_x*dim_y;
    int color_count = 0, color_index = 0, offset = PALETTE_MAX*RGB_TUPLE_SIZE;
    int curr_compact;

    for (int i = 0; i < in_size; i+= 3)
    {
        //read compact representation of RGB triplet
        curr_compact = compact(image_buf, i);
        int find = lookup(curr_compact);

        //if not already in hash table
        if (find == -1)
        {
            //insert into hash table
            insert(curr_compact, color_index); 
            unpack(curr_compact);   //extract RGB values

            //insert new color into palette 
            color256_img[i] = red;
            color256_img[i+1] = green;
            color256_img[i+2] = blue;

            //store index
            color256_img[color_index+offset] = color_count;
            color_count++;
        }

        //if already in hash table
        else
        {
            unpack(curr_compact);
            //store previously occurred index
            color256_img[color_index+offset] = find;
        }

        color_index++;

        //check color count is under 256
        if (color_count > 256)
        {
            error_handler(2, "Color palette size exceeded");
            return NULL;
        }
    }

    //verification purposes
    print_arr(color256_img, PALETTE_MAX*RGB_TUPLE_SIZE + dim_x*dim_y);

    return color256_img;
}

unsigned char* image_color256(unsigned int dim_x, unsigned int dim_y)
{
    //check dimensions
    if (dim_x == 0 || dim_y == 0)
    {
        error_handler(4, "incorrect dimensions");
        return NULL;
    }

    //calculate total size of COLOR256 table
    int final_size = PALETTE_MAX*RGB_TUPLE_SIZE + dim_x*dim_y;
    printf("Final size: %d\n", final_size);

    //allocate memory for COLOR256 table
    unsigned char* img = malloc(final_size*sizeof(unsigned char));

    if (img == NULL)
    {
        error_handler(1, "allocating memory");
        exit(1);
    }

    //initialize all values to zero
    for (int i = 0; i < final_size; i++)
    {
        img[i] = 0;
    }

    return img;
}