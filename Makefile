CC := gcc

SRCS += test/main.c
SRCS += atcmd.c
SRCS += ext/string-utils/str.c
INCS += .
INCS += ext/string-utils

CFLAGS += -Wall
CFLAGS += -Wformat=0
ifdef DEBUG
CFLAGS += -g
endif

default: $(SRCS:%.c=obj/%.o)
	@mkdir -p bin
	$(CC) -o bin/test $? $(INCS:%=-I%) $(CFLAGS)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(INCS:%=-I%) $(CFLAGS)

clean:
	rm -f $(SRCS:%.c=obj/%.o)
	rm -f bin/test

