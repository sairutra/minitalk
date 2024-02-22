CC = cc

FLAGS = -Wall -Werror -Wextra 

SERVER = server_folder/server.c

ClIENT = client_folder/client.c

CLM = client_folder/clm.c

CMM = client_folder/cmm.c

CSM = client_folder/csm.c

SMM = server_folder/smm.c

SLM = server_folder/slm.c

SSM = server_folder/ssm.c

LIBFT = ./libft

LIBFT.A = ./libft/libft.a

MS_SRV_INTERVAL = 600

MS_LEN_INTERVAL = 20000

MS_BIT_INTERVAL = 2500

MS_MSG_INTERVAL = 20000

all: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(SLM) $(SMM) $(SSM) $(LIBFT.A)  -D SRV_INTERVAL=$(MS_SRV_INTERVAL) -o server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CSM) $(LIBFT.A)  -D LEN_INTERVAL=$(MS_LEN_INTERVAL) -D BIT_INTERVAL=$(MS_BIT_INTERVAL) -D MSG_INTERVAL=$(MS_MSG_INTERVAL) -o client

$(LIBFT.A):
	@$(MAKE) -C $(LIBFT) all

clean:
	@$(MAKE) -C $(LIBFT) clean
	rm -f server
	rm -f client

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	rm -f server
	rm -f client

re: fclean all


