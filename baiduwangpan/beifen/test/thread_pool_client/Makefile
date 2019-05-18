SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=process_pool_client
CC:=gcc
CFLAGS:=-g -Wall -D DEBUG -lcrypto -lz -lcrypt
$(ELF):$(OBJS)
	gcc $^ -o $@ -lcrypt
.PHONY:clean
clean:
	rm -rf $(ELF) $(OBJS)

