SRCS:=$(wildcard *.cc)
OBJS:= $(SRCS:%.cc=%.o)
ELF:=textQuery
CC:=g++
CFLAGS:=-g -Wall -D DEBUG -std=c++11
$(ELF):$(OBJS)
	g++  $^ -o $@ -g -std=c++11
clean:
	rm -rf $(ELF) $(OBJS)
