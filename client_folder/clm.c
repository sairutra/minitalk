#include "../minitalk.h"

void    len_status_start(pid_t pid, int len_status)
{
    kill(pid, SIGUSR2);
    if(VERBOSE == 1)
    {
        ft_putstr_fd("send sigusr2 lenstatus: ", STDOUT_FILENO);
        ft_putnbr_fd(len_status, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    usleep(LEN_INTERVAL);
}

void    len_status_sending(pid_t pid)
{
        if(VERBOSE == 1)
            ft_putstr_fd("send sigusr1 len\n", STDOUT_FILENO);
        kill(pid, SIGUSR1);
        usleep(LEN_INTERVAL);
}

void    len_status_end(pid_t pid, int len_status)
{
	kill(pid, SIGUSR2);
    if(VERBOSE == 1)
    {
		ft_putstr_fd("send sigusr2 lenstatus: ", STDOUT_FILENO);
		ft_putnbr_fd(len_status, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
    }
    usleep(LEN_INTERVAL);
}

int     len_status_confirmation(void)
{
    if(VERBOSE == 1)
        ft_putstr_fd("len confirmation 2 \n", STDOUT_FILENO);
    return(2);
}

int     len_status_received(void)
{
    if(VERBOSE == 1)
        ft_putstr_fd("message received len \n", STDOUT_FILENO);
    return(4);
}

int     len_status_complete(void)
{
    if(VERBOSE == 1)
        ft_putstr_fd("len complete 6 \n", STDOUT_FILENO);
    return(6);
}