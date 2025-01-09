const int ORDER_LENGTH = 10;
const int num_mark = 10;
const int ARR_COD = 1000;
const long int VErsion = 0x60d15dead;

struct black 
{
    int adr;
    char name[ORDER_LENGTH];
};
enum enm 
{
    success = 0,
    err_cmd = 1,
    err_arg =  2,
    err_file = 3,
    err_mark = 4,
    err_reg = 6,
    no_event = 7,
    was_event = 8,
    err_marking = 9,
    err_dump = 10
};

int print_error (enm return_mean);
int is_it_label (FILE* fp, char* get_char, int start_ip, int* register_num, int* code, int number_of_mark, black* mark, int* ip);
enm write_code_to_file (int* code, int ip, char* argv_1);
int strcicmp (char const *a, char const *b);
enm assembl  (char* argv_1);
int subtit_mark (int number_of_mark_in_code, int number_of_mark_initiation, black* mark_adres_in_code_subtit, black* mark_initiation, int* code);
int get_arg  (int* code, int* ip, FILE* fp, black* mark, int *number_of_mark);
int get_mark (black* mark, FILE* fp);
//int _get_numer (int start_ip, int* code, char* get_char, FILE* fp);