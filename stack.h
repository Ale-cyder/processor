

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#define kankareika

#ifdef kankareika
#define OMMON ,
#define KANAR(naame) naame 
#define CANARY_NAME 0xabcdabcdabcdabcd
#else 
#define OMMON
#define KANAR(naame) 
#endif

#ifndef qwertyuiop
#define qwertyuiop
typedef int stack_elem_type;
#define NOVICHOK (stack_elem_type)0X60D15DEAD

enum realock_operation
{
    expansion = 1,
    alignment = 3
};
enum err_enum
{
    no_err = 0,
    err_adr_stk = 1,
    err_adr_arr = 2,
    err_size_arr = 3,
    zero_capacity = 4,
    zero_size = 5, 
    no_memory_to_increase = 6 OMMON
    KANAR (err_kanar_stk = 7) OMMON
    KANAR(err_kanar_arr = 8)
    
};

struct Stack
{
    KANAR(unsigned long long int left_d;)
    stack_elem_type* data;
    size_t size_;
    size_t capacity;
    KANAR(unsigned long long int right_d;)
};
const int Min_Stack_Size = 4;
KANAR(const int size_kanary = sizeof(unsigned long long int);)
const size_t SizStack_elem = sizeof (stack_elem_type);  
const float  reduct_multiplier = 1.5;
const size_t magnification_multiplier = 2;
int      des_troy      (Stack* stk);
err_enum initiation    (int xxx_, Stack* stk);
err_enum realloc_stack (Stack* stack_pp, realock_operation operation_);
err_enum stack_err     (Stack* stack_pp, const char* Fill_, int line);
err_enum stack_push    (Stack* stack_pp, stack_elem_type elem);
err_enum stack_pop     (Stack* stack_pp, stack_elem_type* elem); // TODO: подравнять
err_enum damp          (Stack st);
#endif