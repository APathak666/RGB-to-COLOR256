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

//error codes and messages
enum err_code {MALLOC_ERR = 1, PALETTE_ERR, INSERT_ERR, DIM_ERR, BUFF_ERR, INP_ERR};

#define MALLOC_MSG  "allocating memory"
#define PALETTE_MSG "color palette size exceeded"
#define INSERT_MSG  "value already exists in table"
#define DIM_MSG     "incorrect dimensions"
#define BUFF_MSG    "color256 buffer returned NULL"
#define INP_MSG     "NULL input"

#endif
