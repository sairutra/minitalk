CC = cc

FLAGS = -Iinc -Ilib/libft/inc -Wall -Werror -Wextra -O3

SERVER = src/srv/server.c

ClIENT = src/clt/client.c

CLM = src/clt/clm.c

CLM_EXT = src/clt/clm_ext.c

CMM = src/clt/cmm.c

CSM = src/clt/csm.c

SMM = src/srv/smm.c

SLM = src/srv/slm.c

SSM = src/srv/ssm.c

LIBFT = ./lib/libft

LIBFT.A = ./lib/libft/lib/libft.a

all: $(LIBFT.A)
	mkdir -p build/bin
	$(CC) $(FLAGS) $(SERVER) $(SLM) $(SMM) $(SSM) $(LIBFT.A) -o build/bin/server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CSM) $(CLM_EXT) $(LIBFT.A) -o build/bin/client

verbose: $(LIBFT.A)
	$(CC) $(FLAGS) $(SERVER) $(SLM) $(SMM) $(SSM) $(LIBFT.A)  -D VERBOSE=1 -o build/bin/server
	$(CC) $(FLAGS) $(ClIENT) $(CLM) $(CMM) $(CSM) $(CLM_EXT) $(LIBFT.A)  -D VERBOSE=1 -o build/bin/client

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


