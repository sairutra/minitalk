CC = cc

FLAGS = -Wall -Werror -Wextra -O3

SERVER = server_folder/server.c

ClIENT = client_folder/client.c

CLM = client_folder/clm.c

CLM_EXT = client_folder/clm_ext.c

CMM = client_folder/cmm.c

CSM = client_folder/csm.c

SMM = server_folder/smm.c

SLM = server_folder/slm.c

SSM = server_folder/ssm.c

LIBFT = ./libft

LIBFT.A = ./libft/lib/libft.a

all: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(SLM) $(SMM) $(SSM) $(LIBFT.A) -o server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CSM) $(CLM_EXT) $(LIBFT.A) -o client

verbose: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(SLM) $(SMM) $(SSM) $(LIBFT.A)  -D VERBOSE=1 -o server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CSM) $(CLM_EXT) $(LIBFT.A)  -D VERBOSE=1 -o client

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

bonus: all


