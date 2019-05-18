SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.c,$(SRCS))
ELF:=process_pool_server
CC:=gcc
CFLAGS:=-g -Wall -D DEBUG
$(ELF):$(OBJF)
	gcc $^ -o $@
.PHONY:clean
clean:
	rm -rf $(ELF) $(OBJS)

