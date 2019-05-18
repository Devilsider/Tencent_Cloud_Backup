SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=process_pool_client
CC:=gcc
CFLAGS:=-g -Wall -D DEBUG -lcrypto -lz -lcrypt
$(ELF):$(OBJS)
	gcc $^ -o $@ -lcrypt -pthread
.PHONY:clean
clean:
	rm -rf $(ELF) $(OBJS)

