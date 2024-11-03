#ifndef ghjk
#define ghjk
#include "../stack/stack__/stack/stack.h"
#define NUM_RAM 64
#define NUM_REG 8
struct proc
{
    int ip;
    int number_cmd;   
    int* arr_cod;
    int arr_reg[NUM_REG];
    int arr_ram[NUM_RAM];
    Stack stk;
};
enum ERR
{
    NO_ERR = 0,
    ERR_NAME = 1,
    ERR_ADR = 2,
    ERR_OPEN = 3,
    ERR_VERS = 4,
    ERR_MALLOC = 5,
    ERR_COD_READ = 6,
    ERR_COD = 7,
    NO_END_PROG = 8,
    ERR_INIT_STACK = 9
};

int get_data (proc* proces, int* res);
int dump_proc (proc process, char* comment);
ERR ran (proc proces);
ERR get_cod (proc* proces, char* argv_1);
int chec_version (FILE* fp);
#endif
