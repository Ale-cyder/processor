#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "asm.h" 

int main (int argc, char* argv[])
{
    if (argc == 2)
    {
        char* argv_1 = argv[1];
        if (assembl(argv_1))
            return 1;
        else 
       {
            printf ("All's well that ends well\n");
       }
    }
    else 
        printf ("err file name\n");
}

int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}
int assembl (char* argv_1)
{
    FILE *fp = fopen (argv_1, "r");

    if (fp == 0)
    {
        fprintf (stderr, "oshibka");
        return 1;
    }
    
    black mark[10] = {};
    char order[ORDER_LENGTH] = {}; 
    int code[1000] = {};
    int ip = 1, number_of_mark;

    if ((number_of_mark = get_mark (mark, fp)) < 0)
    {
        fprintf (stderr, "err mark\n");
        return 1;
    }
    rewind (fp);

    #define CMD_CMD(NAME, COD, ARG, ...) if (!strcicmp (order, # NAME)) \
                                         { code[ip++] = COD; if (ARG) \
                                         {if (get_arg (code, &ip, fp, mark, number_of_mark)) {printf ("error\n"); \
                                         return 1;}}} else 
   
    int c = fscanf (fp, "%s", order);
    while (c != EOF)
    {
        #include "commands.h"
        {
            int  o = 0;
            for (o = 0; o < ORDER_LENGTH; o++)
            {
                if ((order[o] == ':') && (order[o+1] == '\0'))
                    break;

            }
            if (ORDER_LENGTH == o)
                fprintf (stderr, "Error: %s not the right command\n", order);
        }
        c = fscanf (fp, "%s\n", order);     
    }
    #undef CMD_CMD

    fclose (fp);

    FILE* file_cod = fopen ("cod.txt", "w");
    if (!file_cod)
        return 2;
    
    code[0] = ip - 1;
    int y = fwrite (code, sizeof(code[0]), ip, file_cod);
    //fprintf (file_cod, "%i ", ip);

    //for (int y = 0; y < ip; y++)
    //    fprintf (file_cod, "%i ", code[y]);
    fclose (file_cod);
    return 0;
}
int get_arg (int* code, int* ip, FILE* fp, black* mark, int number_of_mark) 
{
    int start_ip = (*ip)++;
    char c = 0;
    char name_mark[ORDER_LENGTH] = {};
    int name_mark_length = 0;
    int register_num = 0, number = 0, contr = 0;

    c = getc (fp);
    int sign_multiplier = 1;
    while ((c != EOF) && (c != '\n'))
    {
        if ((c <= 'z') && (c >= 'a'))
        {
            while ((c <= 'z') && (c >= 'a'))
            {
                name_mark[name_mark_length++] = c;
                c = getc (fp);
                if (name_mark_length >= ORDER_LENGTH - 1)
                      return 1;
            }

            if ((name_mark_length == 2) && (name_mark[1] == 'x') && (name_mark[0] <= 'h'))
            {
                code[start_ip] = code[start_ip] | 1;
                register_num = name_mark[0] - 'a'; // probably will use register
            }
            else 
            {
                name_mark[name_mark_length] = '\0';

                for (int i = 0; i < number_of_mark; i++)
                {
                    
                    if (!strcmp ((mark + i)->name, name_mark))
                    {
                        code[start_ip] = code[start_ip] | 8;
                        code[(*ip)++] = (mark + i)->adr;
                    
                        if (!(code[start_ip]) & (255-8))
                        {
                            return 1;
                        }
                        return 0;
                    }
                } 
            }
            continue;
        }
        else if (c == '[')
        {
            contr = 1;
            printf ("contr = 1;\n");
        }
        else if (c == ']')
        {
            if (contr) code[start_ip] = code[start_ip] | 2; // will be used RAM
            else return 1;
        }
        else if ((c <= '9') && (c >= '0'))
        {
            
            code[start_ip] = code[start_ip] | 4; // will be used number
            number = c - '0';
            while (((c = getc (fp)) < '9' ) && (c >= '0'))
            {
                number = number * 10 + (c - '0');
            }
            printf ("sign = %i\n", sign_multiplier);
            code[*ip] += number * sign_multiplier;
         
            continue;
        }
        else if (c == ' ') {}
        else if (c == '-') {sign_multiplier = -1;}
        else if (c == '+') {sign_multiplier = 1;}
        else 
        {
            fprintf (stderr, "else er\n");
            return 1;
        }
        c = getc(fp);
    }
    if (code[start_ip] & 4)
    {
        (*ip)++;
    }
    else if (code[(start_ip)] & 1)
    {
        code[(*ip)++] = register_num;
    }
    return 0;
}

int get_mark (black* mark, FILE* fp)
{
    size_t coun = 0;
    size_t number_of_mark = 0;
    char c = 0;
    
    char order[ORDER_LENGTH] = {};

    c = 0;

    while (c != EOF)
    {   
        int num = 0, y = 0, reg = 0, a = 0, chet = 0;
        while (((c = getc (fp)) != '\n') && (c != EOF))
        {
            if (a < ORDER_LENGTH)
                mark[number_of_mark].name[a++] = c;

            if (c == ':')
            {
                c = 0; 
                
                mark[number_of_mark].name[--a] = '\0';
                (mark[number_of_mark++]).adr = coun;
                break;
            }
            else if (c == 'x')
            {
                if (y)
                {
                    reg = 1;
                    chet = 1;
                }
            }
            else if (c == ' ')
            {
                y = 1;
            }
            else if ((c <= '9') && (c >= '0'))
            {
                if (y)
                {
                    num = 1;
                    chet = 1;
                }
            }
        }

        coun = coun + 1 + num + reg + chet;
    }

    return number_of_mark;
}