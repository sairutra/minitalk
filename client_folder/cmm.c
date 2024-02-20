#include "../minitalk.h"

void    sendBits_SigUsr2(pid_t  pid)
{
    kill(pid, SIGUSR2);
    if(VERBOSE == 1)
        ft_putstr_fd("sigusr2: 1\n", STDOUT_FILENO);
}

void    sendBits_SigUsr1(pid_t  pid)
{
    kill(pid, SIGUSR1);
    if(VERBOSE == 1)
        ft_putstr_fd("sigusr1: 0\n", STDOUT_FILENO);
}

void    SendLoad(char   load, pid_t   pid)
{
    if (VERBOSE == 1)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        ft_putchar_fd(load, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    sendBits(load, pid);
    usleep(MSG_INTERVAL);
}

void initialize_struct(struct c_msg_t *msg)
{
    if(VERBOSE == 1)
        ft_putstr_fd("struct members initaliazed to 0\n", STDOUT_FILENO);
    msg->pid = 0;
    msg->msg_status = 0;
    msg->len_status = 0;
}
