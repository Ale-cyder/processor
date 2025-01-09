#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "asm.h"





int main (int argc, char* argv[])
{
    if (argc == 2)
    {                            
        enm return_mean = assembl (argv[1]);
        print_error (return_mean);
    }
    else
        printf ("err file name\n");
}
int print_error (enm return_mean)
{
    switch (return_mean)
    {
    case err_file:
        printf ("incorrect file name");
        break;
    case err_mark:
        printf ("incorrect label");
        break;
    case success:
        printf ("All's well that ends well\n");
        break;
    case err_dump:
        printf ("error in dump\n");
        break;
    default:
        printf ("incorrect error\n");
        break;
    }
    return 0;
}


int strcicmp (char const *a, char const *b)
{
    for (;; a++, b++) 
    {
        int d = tolower ((unsigned char) * a) - tolower ((unsigned char) * b);
        if (d != 0 || !*a) 
            return d;
    }
}

enm assembl (char* argv_1) 
{
    FILE *fp = fopen (argv_1, "r");

    if (fp == 0)
    {
        fprintf (stderr, "oshibka otkretia faila\n");
        return err_file;
    }

    black mark_initiation[num_mark] = {}, mark_adres_in_code_subtit[2 * num_mark] = {};               
    char order[ORDER_LENGTH] = {};
    int code[ARR_COD] = {};
    int ip = 1, number_of_mark_initiation = 0, number_of_mark_in_code = 0; 



    #define CMD_CMD(NAME, COD, ARG, ...) if (!strcicmp (order, # NAME)) \
                                        { \
                                            code[ip++] = COD; \
                                            if (ARG) \
                                            { \
                                                if (get_arg (code, &ip, fp, mark_adres_in_code_subtit, &number_of_mark_in_code)) \
                                                { \
                                                    printf ("error arg on comand %s\n", # NAME); \
                                                    return err_arg; \
                                                } \
                                            } \
                                        } else

    int get_int = fscanf (fp, "%s", order);

    while (get_int != EOF)
    {
        #include "commands.h"
        {
            int  count_length = 0;
            for (count_length = 0; count_length < ORDER_LENGTH; count_length++)
            {
                if ((order[count_length] == ':') && (order[count_length+1] == '\0'))//
                {
                    order[count_length] = '\0';
                    strcpy ((mark_initiation[number_of_mark_initiation]).name, order);
                    (mark_initiation[number_of_mark_initiation++]).adr = ip-1;
                    break;//
                }
            }
            if (ORDER_LENGTH == count_length)
                fprintf (stderr, "Error: %s not the right command\n", order);
        }
        get_int = fscanf (fp, "%s\n", order);
    }
    #undef CMD_CMD

    fclose (fp);
    
    if (subtit_mark (number_of_mark_in_code, number_of_mark_initiation, mark_adres_in_code_subtit, mark_initiation, code))
        return err_mark;

    return write_code_to_file (code, ip, argv_1);;
}

int subtit_mark (int number_of_mark_in_code, int number_of_mark_initiation, black* mark_adres_in_code_subtit, black* mark_initiation, int* code)
{
    for (int count_use_mark_in_code = 0; count_use_mark_in_code < number_of_mark_in_code ; count_use_mark_in_code++)
    {
        int count_initiation_mark = 0;

        for (; count_initiation_mark < number_of_mark_initiation; count_initiation_mark++)
        {
            if (strcmp ((mark_adres_in_code_subtit[count_use_mark_in_code]).name, (mark_initiation[count_initiation_mark]).name) == 0)
            {
                code[(mark_adres_in_code_subtit[count_use_mark_in_code]).adr] = (mark_initiation[count_initiation_mark]).adr;
                
                break;
            }
        }
        
        if (count_initiation_mark == number_of_mark_initiation)
        {
            return 1;
        }
    }
    return 0;
}




/*
int get_mark (black* mark, FILE* fp)
{
    int counter = 0; 
    int number_of_mark = 0;

    char char_get = 0;
    while (char_get != EOF) // TODO: абсолютно не читаемый алгоритм. Придумай норм названия переменных------------------------------
    {
        int is_num = 0, was_white_space = 0, is_register = 0, a = 0, is_type_bit = 0; // TODO: переименовать--------------------

        while (((char_get = getc (fp)) != '\n') && (char_get != EOF))
        {

            if (char_get == ':')
            {
                is_type_bit = -1; // because mark is ===    "name mark": -- it is not written into the code, only the address is remembered

                mark[number_of_mark].name[a] = '\0';
                (mark[number_of_mark++]).adr = counter;
            }
            else if (isalpha(char_get)) 
            {
                if (a < ORDER_LENGTH)
                    mark[number_of_mark].name[a++] = char_get;
                if (was_white_space)
                {
                    is_register = 1;
                    is_type_bit = 1;
                }
            }
            else if (char_get == ' ')
            {
                was_white_space = 1;
            }
            else if (isdigit (char_get))
            {
                if (was_white_space)
                {
                    is_num = 1;
                    is_type_bit = 1;
                }
            }
        }
        counter = counter + 1 + is_num + is_register + is_type_bit;
    }

    return number_of_mark;
}
*/
enm write_code_to_file (int* code, int ip, char* argv_1) 
{
    const int file_name_length = 70; 
    char file_write_name[file_name_length] = {};

    for (int i = 0; i < (file_name_length - 3); i++) 
    {
        file_write_name[i] = argv_1[i];

        if (argv_1[i] == '.')
        {
            i++;
            file_write_name[i++] = 'b';
            file_write_name[i++] = 'i';
            file_write_name[i++] = 'n';
            file_write_name[i++] = '\0';

            printf ("name file with cod is:\n");
            puts (file_write_name);

            FILE* file_cod = fopen (file_write_name, "w");
            
            if (!file_cod)
                return err_file;
            fwrite (&VErsion, sizeof(long int), 1, file_cod);
            code[0] = ip - 1;

            fwrite (code, sizeof (code[0]), (size_t)ip, file_cod);

            fclose (file_cod);
            return success;
        }
    }
    return err_dump;
}


enm get_numer            (const int start_ip, int* code, int* ip, FILE* fp);
enm check_and_write_register       (const int start_ip, int* code, int* ip, char* get_str);
enm check_and_write_mark       (const int start_ip, int* code, int* ip, char* get_str, int* number_of_mark, black* mark);

int get_arg (int* code, int* ip, FILE* fp, black* mark, int* number_of_mark)
{
    const int start_ip = (*ip)++;
    char get_str[ORDER_LENGTH] = {};

    if (fscanf (fp, "%[[]", get_str)) 
    {
        const int will_ram = 2;
        code[start_ip] = code[start_ip] | will_ram;

        if ((get_numer (start_ip, code, ip, fp) == success) && (fscanf (fp, "%[+]", get_str) == 0))
            return 0;

        if (fscanf (fp, "%[^]... ]]", get_str) != 0)
            if (check_and_write_register (start_ip, code, ip, get_str) == success)
            return 0;
        return 1;
    }

    if (get_numer (start_ip, code, ip, fp) == success) 
    {
        if (fscanf (fp, "+%[^\n ]", get_str) != 0)
            if (check_and_write_register (start_ip, code, ip, get_str) != success)
                return 1;
        return 0;
    }

    if (fscanf (fp, "%[^\n ]", get_str) == 0)
        return 1;

    if ((check_and_write_register (start_ip, code, ip, get_str) == success) || (check_and_write_mark (start_ip, code, ip, get_str, number_of_mark, mark) == success))
        return 0;
    
    return 1;
}

//
enm check_and_write_mark       (const int start_ip, int* code, int* ip, char* get_str, int* number_of_mark, black* mark)
{
    const int will_mark = 8;

    code[start_ip] = code[start_ip] | will_mark;
    strcpy ((mark[*number_of_mark]).name, get_str);
    (mark[(*number_of_mark)++]).adr = *ip;
    code[(*ip)++] = -1;

    return success;       
}
//
enm check_and_write_register (const int start_ip, int* code, int* ip, char* get_str)
{
    const int will_register = 1; 

    if ((get_str[3] == '\0') && (get_str[1] == 'x') && (get_str[0] >= 'a') && (get_str[0] <= 'h')) 
    {
        code[start_ip] = code[start_ip] | will_register;
        code[(*ip)++] = get_str[0] - 'a'; 
        return success;
    }
    return err_reg;
}
//
enm get_numer (const int start_ip, int* code, int* ip, FILE* fp)
{
    const int will_number = 4;
    int number = 0, sign_multiplier = 1;
    char get_char = 0;

    // if (fscanf (fp, "%[-]", &get_char))
    //     sign_multiplier = -1;

    if (fscanf (fp, "%d", &number) == 0)
        return no_event;

    code[start_ip] = code[start_ip] | will_number; 
    code[(*ip)++] = number * sign_multiplier;

    return success;
}