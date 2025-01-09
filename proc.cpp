#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "proc.h"
#include "ENUM_COM.h"

int main (const int argc, const char* argv[]) 
{
    if (argc == 2)
    {
        proc proces = {};
        if (get_cod (&proces, argv[1])) 
        {
            printf ("error read cod\n");
        }
        else 
        {
            ERR return_meaning = ran (&proces);
            print_error (return_meaning);
            
            des_troy_proc (&proces);
        }
    }
    else 
    {
        printf ("NOT file\n");
        return EXIT_FAILURE;
    }
    return 0;
}
int print_error (ERR return_mean)
{
    switch (return_mean)
    {
    case NO_ERR:
        printf ("the program has been successfully completed\n");
        break;
    case ERR_COD:
        printf ("error cod\n");
        break;
    case NO_END_PROG:
        printf ("no ending program command, accomplish cod finished\n");
        break;
    default:
        printf ("unknown error\n");
        break;
    }
    return 0;
}






ERR get_cod (proc* proces, const char* argv_0)
{
    if (argv_0)
    {
        FILE* fp = fopen (argv_0, "r");
    
        puts (argv_0);

        if (!fp)
        {
            return ERR_OPEN;
        }
        if (chec_version (fp))
        {
            fprintf (fp, "err version\n");
            return ERR_VERS;
        }

        fread (&(proces->number_cmd), sizeof(int), 1, fp);
      
        proces->arr_cod = (int*) calloc (proces->number_cmd + 1, sizeof (int)); 
     
        if (!proces->arr_cod)
        {
            return ERR_MALLOC;
        }
        int number_read_order = fread (proces->arr_cod, sizeof (int), proces->number_cmd, fp);
      
        if (number_read_order < proces->number_cmd)
        {
            return ERR_COD_READ;
        }

        const int start_size_stack = 10;
        if (initiation (start_size_stack, &(proces->stk)))
        {
            return ERR_INIT_STACK;
        }

        fclose (fp); 

        return NO_ERR;
    }
    else return ERR_ADR;
}

ERR des_troy_proc (proc* proces)
{
    if (proces->arr_cod) 
        free (proces->arr_cod);
    else
        printf ("something not good happened-\n");
        
    des_troy (&(proces->stk));
    *proces = {};
    return NO_ERR;
}

ERR ran (proc* proces)
{
    #define CMD_CMD(NAME, COD, ARG, CODE) case CMD_ ## NAME : CODE  break;
    while ((*proces).ip <(*proces).number_cmd)
    {
    
        switch ((*proces).arr_cod[(*proces).ip++])
        {
            #include "commands.h"
            default : return ERR_COD;
        }
        dump_proc (*proces, "run");
    }
    
    return NO_END_PROG;
}









int get_data (proc* proces, int* res)
{
    int arg_type = proces->arr_cod[proces->ip++];
    int result = 0;
    if (arg_type & 4) // bit numer
    {
        result += (proces->arr_cod[proces->ip++] * 10000);
    }
    
    if (arg_type & 1) // regist bit
    {
        *res = proces->arr_cod[proces->ip];
        result += proces->arr_reg[proces->arr_cod[proces->ip++]];
    }
    
    if (arg_type & 2) // ram bit
    {
        *res = ((-1) * result / 10000);
        result = proces->arr_ram[(result / 10000)]; 
    }
    
    if (arg_type & 8) // mark bit
    {
        return proces->arr_cod[proces->ip++];
    }
    return result;
}



int chec_version (FILE* fp)
{
    long int edentifier = 0;
    fread (&edentifier, sizeof(VErcion), 1, fp);
    if (edentifier != VErcion)
    {
        return 1;
    }
    return 0;
}
int dump_proc (proc proces, char* comment)
{
    static FILE* log_file = fopen ("log.txt", "w");
    fprintf (log_file, "\nnumber comand = %i\nadres array with cod = %p\n", proces.number_cmd, proces.arr_cod);
    
    for (int i = 0; i < proces.number_cmd; i++)
    {
        fprintf (log_file, "%3i ", proces.arr_cod[i]);
    }
    fprintf (log_file, "\n");

    for (int i = 0; i < proces.ip; i++)
    {
        fprintf (log_file, "    ");
    }
    fprintf (log_file, "^^^ ip = %i\n%s\n", proces.ip, comment);

    for (int i = 0; i < NUM_RAM; i++)
    {
        fprintf (log_file, "%3i | ", proces.arr_ram[i]);
    }
    fprintf (log_file, "\n");
    
    for (int i = 0; i < NUM_REG; i++)
    {
        fprintf (log_file, "%3i | ", proces.arr_reg[i]);
    }
    fprintf (log_file, "\n");
    fprintf (log_file ,"STACK\n");
    fprintf (log_file, "size = %lu\ncapaccity = %lu\ndata = %p\n",
            proces.stk.size_, proces.stk.capacity, proces.stk.data);   

    for (size_t i = 0; i < proces.stk.capacity; i++)
    {
        fprintf (log_file, "element number %lu = %i\n", i+1, *(proces.stk.data + i));
    }
    fprintf (log_file, "end damp \n");
    

    return 0;
}