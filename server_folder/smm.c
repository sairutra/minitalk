#include "../minitalk.h"

void initialize_server_struct(struct s_msg_t *msg)
{
    if(VERBOSE == 1)
        ft_putstr_fd("server struct members initaliazed to 0\n", STDOUT_FILENO);
    msg->binaryindex = 0;
	msg->len_status = 0;
	msg->msg_status = 0;
	msg->index = 0;
	msg->length = 0;
    msg->load = ft_memset(msg->load, 0, ft_strlen(msg->load));
}


void    msg_status_confirm(struct s_msg_t *msg, pid_t pid)
{
    msg->msg_status = 1;
    if(VERBOSE == 1)
    {
        ft_putstr_fd("msg_status = 1 \n", STDOUT_FILENO);
        ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
    }
    kill(pid, SIGUSR2);		
}

void    server_sigusr1(struct s_msg_t *msg, char *binary, pid_t pid)
{
    kill(pid, SIGUSR1);
    if(VERBOSE == 1)
        ft_putstr_fd("msg_status 1: sigusr1 (0)  \n", STDOUT_FILENO);
    binary[msg->binaryindex] = 48;
    msg->binaryindex++;
    if(VERBOSE == 1)
    {
        ft_putnbr_fd(msg->binaryindex, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}

void    server_sigusr2(struct s_msg_t *msg, char *binary, pid_t pid)
{
    kill(pid, SIGUSR1);
    if(VERBOSE == 1)
        ft_putstr_fd("msg_status 1: sigusr2 (1) \n", STDOUT_FILENO);
    binary[msg->binaryindex] = 49;
    msg->binaryindex++;
    if(VERBOSE == 1)
    {
        ft_putnbr_fd(msg->binaryindex, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}
