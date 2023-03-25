#ifndef __HELPER_H_
#define __HELPER_H_

#define PALETTE_MAX 256
#define RGB_TUPLE_SIZE 3

int red, green, blue;

//function prototypes
unsigned char* image_rgb_to_color256(unsigned int dim_x, unsigned int dim_y, unsigned char* image_buf);
unsigned char* image_color256(unsigned int dim_x, unsigned int dim_y);
void test_func();
void print_arr(unsigned char* buf, int start_idx, int end_idx);
void print_list();
void error_handler(int error, char* str);
void unpack(int compact);

#endif
