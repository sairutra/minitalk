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


all: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(SLM) $(SMM) $(SSM) $(LIBFT.A)  -D SRV_INTERVAL=600 -o server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CSM) $(LIBFT.A)  -D LEN_INTERVAL=20000 -D BIT_INTERVAL=2500 -D MSG_INTERVAL=20000 -o client

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


