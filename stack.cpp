#include "stack.h"

err_enum initiation (int capacity_, Stack* stk) 
{
    if (!stk)
    {
        return err_adr_arr;
    } 

    if (capacity_ < Min_Stack_Size)
    {
        capacity_ = Min_Stack_Size;
    }

    int varieble_size = capacity_ *  SizStack_elem KANAR(+ (2 * size_kanary)); 
    
    stk->data = (stack_elem_type*) calloc (varieble_size, 1);
   
    KANAR ((stk->data) = (stack_elem_type*) ((char*) (stk->data) + size_kanary);) 
    
    
    stk->size_ = 0;
    stk->capacity = capacity_; 
     
    KANAR 
    (
        stk->right_d = CANARY_NAME;
        stk->left_d = CANARY_NAME;
       *(unsigned long long int*) ((char*)(stk->data) - size_kanary) = CANARY_NAME; 
       *(unsigned long long int*) ((stk->data) + stk->capacity) = CANARY_NAME;
   )
    for (int i = stk->size_; i < stk->capacity; i++)
    {
        stk->data[i] = NOVICHOK; 
    }
    
    
    return stack_err (stk,__FILE__,__LINE__); 
}


err_enum stack_pop (Stack* stack_pp, stack_elem_type* elem) 
{
    err_enum stack_err_answer = stack_err (stack_pp, __FILE__, __LINE__);
    if (stack_err_answer) 
    {
        printf ("err i p\n"); 
        return stack_err_answer;
    }

    if ((stack_pp->capacity > reduct_multiplier * (stack_pp->size_)) && (stack_pp->capacity > Min_Stack_Size * reduct_multiplier)) 
    {
        realloc_stack (stack_pp, alignment);
    }
    if (stack_pp->size_ == 0)
    {
        return zero_size;
    }
    *elem = *(stack_pp->data + --(stack_pp->size_)); 

    *(stack_pp->data + (stack_pp->size_)) = NOVICHOK;

    return stack_err (stack_pp, __FILE__, __LINE__);
}

err_enum stack_push (Stack* stack_pp, stack_elem_type elem)
{
    err_enum stack_err_answer = stack_err (stack_pp, __FILE__, __LINE__);

    if (stack_err_answer) 
    {
        printf ("err i push\n"); 
        return stack_err_answer;
    }
        

    if (stack_pp->capacity <= stack_pp->size_) 
    {
        realloc_stack (stack_pp, expansion);
    }
    
    *(stack_pp->data + stack_pp->size_) = elem;
    (stack_pp->size_)++;
    return stack_err (stack_pp, __FILE__, __LINE__);
}

err_enum stack_err (Stack* stack_pp, const char* Fill_, int line)
{
    err_enum controller = no_err;
    if (!stack_pp)
    {
        fputs ("invalid address for stack\n", stderr);
        controller = err_adr_stk;
    }
    else if (!stack_pp->data)
    {
        fputs ("invalid address array in stack\n", stderr);
        controller = err_adr_arr;
    }
    else if (stack_pp->capacity < Min_Stack_Size) 
    {
        fputs ("error stack size\n", stderr);
        controller = err_size_arr;
    }
    KANAR( 
    else if (!((stack_pp->left_d == CANARY_NAME) && (stack_pp->right_d == CANARY_NAME)))
    {
        fputs ("error: error kanareika in struct\n", stderr);  
        controller = err_kanar_stk; 
    }
    else if (!(*(unsigned long long int*)(stack_pp->data + stack_pp->capacity) == CANARY_NAME) && 
              (*(unsigned long long int*)((char*)stack_pp->data - size_kanary) == CANARY_NAME)) 
    {
        fputs ("error: error kanareika in array\n", stderr);  
        controller = err_kanar_stk; 
    })
    if (controller)
    {
        fputs("File: ", stderr);
        fputs (Fill_, stderr);
        fprintf (stderr, "\nLine %i\n", line);
    }
    return controller;
}

err_enum damp (Stack st)
{
    err_enum stack_err_answer = stack_err (&st, __FILE__, __LINE__);
    if (stack_err_answer) 
    {
        printf ("err damp\n"); 
        return stack_err_answer;
    }
    fprintf (stdout ,"STACK\n");
    fprintf (stdout, "size = %lu\ncapaccity = %lu\ndata = %p\n",
            st.size_, st.capacity, st.data);   
    KANAR( 
        fprintf (stdout, "left kanar = %llx\nright kanar = %llx\n", st.left_d, st.right_d);        
        fprintf (stdout, "Kanar in array:\n left = %llx\n right = %llx\n", 
            *(unsigned long long int*)(st.data + st.capacity), 
            *(unsigned long long int*)((char*)st.data - size_kanary) ); 
        )
    for (size_t i = 0; i < st.capacity; i++)
    {
        fprintf (stdout, "element number %lu = %i\n", i+1, *(st.data + i));
    }
    return no_err;
}

err_enum realloc_stack (Stack* stack_pp, realock_operation oper_)
{
    void* temp_old_arr_adr = (void*)((char*)(stack_pp->data) KANAR(- size_kanary));
    void* temp_new_arr_adr = 0;

    if (oper_ == expansion)
    {
        size_t size_stac = (magnification_multiplier * (stack_pp->capacity) * SizStack_elem KANAR(+ 2 * size_kanary)); 
        
        temp_new_arr_adr = realloc (temp_old_arr_adr, size_stac);
        
        if  (temp_new_arr_adr) 
        {
            stack_pp->data = (stack_elem_type*)((char*)temp_new_arr_adr KANAR(+ size_kanary)); 

            stack_pp->capacity = (stack_pp->capacity) * magnification_multiplier;

            for (size_t i = stack_pp->size_; i < stack_pp->capacity; i++)
            {
                stack_pp->data[i] = NOVICHOK;
            }
        }
        else
        { 
            fputs ("No the memory for increase stack\n", stderr); // TODO: ошибку обработать
            return no_memory_to_increase;
        }
    }
    else 
    {
        size_t size_stac =  ((size_t)((stack_pp->capacity) / reduct_multiplier) * SizStack_elem  KANAR(+ 2 * size_kanary));
        
        temp_new_arr_adr = (realloc (temp_old_arr_adr, size_stac));

        (stack_pp->data) = (stack_elem_type*)((char*) temp_new_arr_adr KANAR(+ size_kanary));

        stack_pp->capacity = (size_t)((stack_pp->capacity)/reduct_multiplier);
    }
    KANAR
        (
            *(unsigned long long int*)((stack_pp->data) + stack_pp->capacity) = CANARY_NAME;
        )
    return no_err;
}

int des_troy (Stack* stk)
{ 
    void* memory_adres = (void*) ((char*)stk->data KANAR( - size_kanary)); 
    
    if (memory_adres)
        free (memory_adres);
    else 
        printf ("something not good happen\n");
    *stk = {};
    return 0;
}