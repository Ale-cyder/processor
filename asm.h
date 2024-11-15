#define ORDER_LENGTH 10
#define NUM_MARK 10
#define ARR_COD 1000
struct black 
{
    size_t adr;
    char name[ORDER_LENGTH];
};
const long int VErsion = 0x60d15dead;
int write_cod (int* code, int ip, char* argv_1);
int strcicmp (char const *a, char const *b);
int assembl  (char* argv_1);
int get_arg  (int* code, int* ip, FILE* fp, black* mark, int number_of_mark);
int get_mark (black* mark, FILE* fp);