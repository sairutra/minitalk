CC = cc

FLAGS = -Wall -Werror -Wextra 

SERVER = server.c

ClIENT = client_folder/client.c

CLM = client_folder/clm.c

CMM = client_folder/cmm.c

LIBFT = ./libft

LIBFT.A = ./libft/libft.a


all: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(LIBFT.A) -o server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(LIBFT.A) -o client

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


