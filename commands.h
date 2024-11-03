// CMD___ (NAME, CODE, ARG, ---)
CMD_CMD (POP,  1, 1,
{
    int adres = 1;
    get_data (&proces, &adres);
    if (adres > -1)
        stack_pop (&proces.stk, &(proces.arr_reg[adres]));
    else 
        stack_pop (&proces.stk, &(proces.arr_ram[-adres]));
})
CMD_CMD (PUSH, 2, 1,
{
    int c = 0;
    stack_push (&proces.stk, get_data (&proces, &c));
})
CMD_CMD (ADD,  3, 0,
{
    int first_num  = 0;
    int second_num = 0;
    stack_pop (&proces.stk, &first_num);
    stack_pop (&proces.stk, &second_num);
    stack_push (&proces.stk, first_num + second_num);
})
CMD_CMD (SUB,  4, 0,
{
    int first_num  = 0;
    int second_num = 0;
    stack_pop (&proces.stk, &first_num);
    stack_pop (&proces.stk, &second_num);
    stack_push (&proces.stk, first_num - second_num);
}) // _cod_ type_ if is -> regist_ num_
CMD_CMD (DIV,  5, 0,
{
    int first_num  = 0;
    int second_num = 0;
    stack_pop (&proces.stk, &first_num);
    stack_pop (&proces.stk, &second_num);
    stack_push (&proces.stk, (int)(first_num / second_num));
}) // push 2 || push [2] || push ax || push [ax+2] || push 3+ax
CMD_CMD (MUL,  6, 0,
{
    int first_num  = 0;
    int second_num = 0;
    stack_pop (&proces.stk, &first_num);
    stack_pop (&proces.stk, &second_num);
    stack_push (&proces.stk, first_num * second_num);
}) // pop ax || pop [2] || pop [ax+2] 
CMD_CMD (JB,   7, 1,
{
    int first_num  = 0;
    int second_num = 0;
    stack_pop (&proces.stk, &first_num);
    stack_pop (&proces.stk, &second_num);
    int y = 0;
    if (first_num > second_num)
    {
        proces.ip = get_data (&proces, &y);
    }
}) // jb [2] || jb 2 || jb ax || jb [4+ax] || jb 4+ax
CMD_CMD (JA,   8, 1,
{
    int first_num  = 0;
    int second_num = 0;
    stack_pop (&proces.stk, &first_num);
    stack_pop (&proces.stk, &second_num);
    int y = 0;
    if (first_num > second_num)
    {
        proces.ip = get_data (&proces, &y);
    }                     
    else 
    {
        proces.ip+=2;
    }                     // reg  oper  num  mark
})                       // 1-    2-    3-   4-   5-6-7-8
CMD_CMD (JMP,  9, 1,
{
    int f = 0;
    proces.ip = get_data (&proces, &f);
})
CMD_CMD (HLT, 10, 0,
{
    return NO_ERR;
})
CMD_CMD (OUT, 11, 0,
{
    int first_num  = 0;
    stack_pop (&proces.stk, &first_num);
    fprintf (stdout, "out: %i\n", first_num);
})
CMD_CMD (SQRT,  12, 0,
{
    int first_num  = 0;
    stack_pop (&proces.stk, &first_num);
    stack_push (&proces.stk, (int)sqrt(first_num));
})
CMD_CMD (INPUT,  13, 0,
{
    int first_num  = 0;
    scanf ("%i", &first_num);
    stack_push (&proces.stk, first_num);
})
