#define CMD_CMD(NAME, COD, ARG,...) CMD_ ## NAME = (int)COD, 
enum COMAND 
{
    #include "commands.h"
};
#undef CMD_CMD