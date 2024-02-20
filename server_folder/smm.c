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

