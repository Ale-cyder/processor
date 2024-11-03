#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "proc.h"
#include "ENUM_COM.h"

int main (int argc, char* argv[])
{
    if (argc == 2)
    {
        proc proces = {};
        if (get_cod (&proces, argv[1]))
            return 1;
        ERR PAN_answer = NO_ERR;
        if ((PAN_answer = ran (proces)) == NO_END_PROG)
        {
            printf ("no end comand, accomplishment cod finished\n");
        else if (PAN_answer)
            printf ("ERROR\n");
            return 1;
        }
        else 
        {
            printf ("programm succussful complited\n");
            return 0;
        }
    }
    else printf ("NOT file\n");
}

ERR get_cod (proc* proces, char* argv_0)
{
    if (argv_0)
    {
        FILE* fp = fopen (argv_0, "r");
        printf ("fp = %p\n", fp);
        puts (argv_0);
        if (!fp)
        {
            return ERR_OPEN;
        }
        if (chec_version (fp))
        {
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

        return NO_ERR;
    }
    else return ERR_ADR;
}

ERR ran (proc proces)
{
   
    if (initiation    (10, &proces.stk))
    {
        return ERR_INIT_STACK;
    }

    #define CMD_CMD(NAME, COD, ARG, CODE) case CMD_ ## NAME : CODE  break;
    while (proces.ip < proces.number_cmd)
    {
    
        switch (proces.arr_cod[proces.ip++])
        {
            #include "commands.h"
            default : return ERR_COD;
        }
        dump_proc (proces, "run");
    }
    return NO_END_PROG;
}

int get_data (proc* proces, int* res)
{
    int arg_type = proces->arr_cod[proces->ip++];
    int result = 0;
    if (arg_type & 4)
    {
        result += proces->arr_cod[proces->ip++];
    }
    if (arg_type & 1)
    {
        *res *= proces->arr_cod[proces->ip];
        result += proces->arr_reg[proces->arr_cod[proces->ip++]];

    }
    if (arg_type & 2)
    {
        *res = (-1) * result;
        result = proces->arr_ram[result]; 
    }
    if (arg_type & 8)
    {
        return proces->arr_cod[proces->ip++];
    }
    return result;
}
int chec_version (FILE* fp)
{
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