CC = cc

FLAGS = -Wall -Werror -Wextra 

SERVER = server_folder/server.c

ClIENT = client_folder/client.c

CLM = client_folder/clm.c

CMM = client_folder/cmm.c

CMS = client_folder/cms.c

SMM = server_folder/smm.c

LIBFT = ./libft

LIBFT.A = ./libft/libft.a


all: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(SMM) $(LIBFT.A) -o server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CMS) $(LIBFT.A) -o client

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


