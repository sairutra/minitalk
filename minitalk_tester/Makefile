MINI = ../
CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Werror -Wextra
TEST = main.c
CLIENT_TEST = client_tests/ctest.c
SERVER_TEST = server_tests/stest.c
CLIENT_SERVER_TEST = client_server_tests/cstest.c
WELCOME = minitalk_tester_welcome.c

.SILENT:

all:	MINI WELCOME TESTS

MINI:
	@$(MAKE) --no-print-directory -C $(MINI) all
	cp $(MINI)/$(CLIENT) ./
	cp $(MINI)/$(SERVER) ./
	@$(MAKE) --no-print-directory -C $(MINI) clean

TESTS:
	@$(CC) $(CFLAGS) $(TEST) $(CLIENT_TEST) $(SERVER_TEST) $(CLIENT_SERVER_TEST) && ./a.out
	rm a.out

WELCOME:
	@$(CC) $(CFLAGS) $(WELCOME) && ./a.out

clean:
	rm logs/*
	rm client
	rm server