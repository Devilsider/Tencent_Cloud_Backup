SRCS:=$(wildcard *.c)
OBJS:= $(SRCS:%.c=%.o)
ELF:=thread_pool_server
CC:=gcc
CFLAGS:=-g -Wall -D DEBUG -lcrypto -lz -lcrypt
$(ELF):$(OBJS)
	gcc  $^ -o $@ -g -pthread -I /usr/include/mysql/ -lmysqlclient -lcrypt
clean:
	rm -rf $(ELF) $(OBJS)
