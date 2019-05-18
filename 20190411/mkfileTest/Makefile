SOURCE:=$(wildcard *.c)
OBJS:= $(patsubst %.c,%.o,$(SOURCE))
ELF:=main
CC:=gcc
$(ELF):$(OBJS)
	gcc $^ -o $@ 
.PHONY:clean
	clean:
	rm -rf $(OBJS)  $(ELF)














