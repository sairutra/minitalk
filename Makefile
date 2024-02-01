CC = cc

FLAGS = -Wall -Werror -Wextra 

SERVER = server.c

ClIENT = client.c

LIBFT = ./libft

LIBFT.A = ./libft/libft.a


all: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(LIBFT.A) -o server
	$(CC) $(FLAGS) $(ClIENT) $(LIBFT.A) -o client

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


