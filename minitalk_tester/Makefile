MINI = ../
CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Werror -Wextra
TEST = main.c

.SILENT:

all:	MINI 

MINI:
	@$(MAKE) --no-print-directory -C $(MINI) all
	cp $(MINI)/$(CLIENT) ./
	cp $(MINI)/$(SERVER) ./
	@$(MAKE) --no-print-directory -C $(MINI) clean
	@$(CC) $(CFLAGS) $(TEST) && ./a.out
	rm a.out 

clean:
	rm clientlogs.txt
	rm clientoutput.txt
	rm client
	rm server