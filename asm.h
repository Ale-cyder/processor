
int strcicmp(char const *a, char const *b); 
#define ORDER_LENGTH 10
struct black 
{
    size_t adr;
    char name[ORDER_LENGTH];
};
int assembl (char* argv_1);
int get_arg (int* code, int* ip, FILE* fp, black* mark, int number_of_mark);
int get_mark (black* mark, FILE* fp);