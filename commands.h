// CMD___ (NAME, CODE, ARG, ---)
CMD_CMD (POP,  1, 1,
{
    int adres = 1;

    get_data (proces, &adres);

    if (adres > -1)
        stack_pop (&proces->stk, &(proces->arr_reg[adres]));
    else 
    {
        adres = -adres;
      
        stack_pop (&proces->stk, &(proces->arr_ram[adres]));
    }
})
CMD_CMD (PUSH, 2, 1,
{
    int c = 0;

    stack_push (&proces->stk, get_data (proces, &c));
})
CMD_CMD (ADD,  3, 0,
{
    int first_num  = 0;
    int second_num = 0;

    stack_pop (&proces->stk, &first_num);
    stack_pop (&proces->stk, &second_num);

    stack_push (&proces->stk, first_num + second_num);
})
CMD_CMD (SUB,  4, 0,
{
    int first_num  = 0;
    int second_num = 0;

    stack_pop (&proces->stk, &first_num);
    stack_pop (&proces->stk, &second_num);

    stack_push (&proces->stk, first_num - second_num);
}) 
CMD_CMD (DIV,  5, 0,
{
    int first_num  = 0;
    int second_num = 0;

    stack_pop (&proces->stk, &first_num);
    stack_pop (&proces->stk, &second_num);

    stack_push (&proces->stk, (int)(((float)first_num / (float)second_num) * 10000));
}) 
CMD_CMD (MUL,  6, 0,
{
    int first_num  = 0;
    int second_num = 0;

    stack_pop (&proces->stk, &first_num);
    stack_pop (&proces->stk, &second_num);

    second_num = second_num / 100;
    first_num = first_num / 100;

    first_num = first_num * second_num;

    stack_push (&proces->stk, first_num);
}) 
CMD_CMD (JB,   7, 1,
{
    int first_num  = 0;
    int second_num = 0;

    stack_pop (&proces->stk, &first_num);
    stack_pop (&proces->stk, &second_num);

    if (first_num == second_num)
    {
        int y = 0;
        proces->ip = get_data (proces, &y);
    }
    else 
    {
        proces->ip += 2;
    }
}) 
CMD_CMD (JA,   8, 1,
{
    int first_num  = 0;
    int second_num = 0;

    stack_pop (&proces->stk, &first_num);
    stack_pop (&proces->stk, &second_num);

    if (first_num > second_num)
    {
        int y = 0;
        proces->ip = get_data (proces, &y);
    }                     
    else 
    {
        proces->ip += 2;
    }                
})                       
CMD_CMD (JMP,  9, 1,
{
    int f = 0;

    proces->ip = get_data (proces, &f);
})
CMD_CMD (HLT, 10, 0,
{
    //des_troy (&(proces->stk));
    return NO_ERR;
})
CMD_CMD (OUT, 11, 0,
{
    int first_num  = 0;

    stack_pop (&proces->stk, &first_num);

    fprintf (stdout, "out: %.4f\n", (float)first_num / 10000);
})
CMD_CMD (SQRT,  12, 0,
{
    int first_num  = 0;

    stack_pop (&proces->stk, &first_num);

    stack_push (&proces->stk, (int)(100 * sqrt(first_num)));
})
CMD_CMD (INPUT,  13, 0,
{
    float first_num  = 0;

    scanf ("%f", &first_num);

    stack_push (&proces->stk, (int)(first_num * 10000));
})
