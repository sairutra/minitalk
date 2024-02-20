#include "../minitalk.h"

void print_string(struct s_msg_t *msg, pid_t pid)
{
    if(VERBOSE == 1)
        ft_putstr_fd("send complete sig2\n", STDOUT_FILENO);
    usleep(SRV_INTERVAL);
    kill(pid, SIGUSR2);
    msg->load[msg->index] = '\0';
    write(STDOUT_FILENO, msg->load, (msg->length - 1));
    write(STDOUT_FILENO, "\n", 1);
    free(msg->load);
    initialize_server_struct(msg);
    ft_putstr_fd("Server ready to receive string again\n", STDOUT_FILENO);
}

void string_initializer(struct s_msg_t *msg, char *binary, pid_t pid)
{
    binary[8] = '\0';
    msg->binaryindex = 0;
    if(binaryToDecimal(binary) == 0)
        print_string(msg, pid);
    else
    {
        msg->load[msg->index] = binaryToDecimal(binary);
        if(VERBOSE == 1)
        {
            ft_putstr_fd("msg load ", STDOUT_FILENO);
            ft_putchar_fd(msg->load[msg->index], STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        msg->index += 1;
    }
}
