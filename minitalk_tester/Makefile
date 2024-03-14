MINI = ../
CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Werror -Wextra
TEST = main.c
CLIENT_TEST = client_tests/ctest.c
WELCOME = minitalk_tester_welcome.c

.SILENT:

all:	MINI WELCOME TESTS 

MINI:
	@$(MAKE) --no-print-directory -C $(MINI) all
	cp $(MINI)/$(CLIENT) ./
	cp $(MINI)/$(SERVER) ./
	@$(MAKE) --no-print-directory -C $(MINI) clean

TESTS:
	@$(CC) $(CFLAGS) $(TEST) $(CLIENT_TEST) && ./a.out
	rm a.out

WELCOME:
	@$(CC) $(CFLAGS) $(WELCOME) && ./a.out

clean:
	rm clientlogs.txt
	rm clientoutput.txt
	rm client
	rm server