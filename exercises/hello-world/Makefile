CC ?= gcc
AS = nasm

CFLAGS = -std=c99 -g -Wall -Wextra -pedantic -Werror
ALL_CFLAGS = -m64 $(CFLAGS)

ASFLAGS = -g -F dwarf -Werror

ifeq ($(OS),Windows_NT)
	ALL_ASFLAGS = -f elf64
else ifeq ($(shell uname -s),Darwin)
	ALL_ASFLAGS = -f macho64 --prefix _
else
	ALL_ASFLAGS = -f elf64
endif

ALL_ASFLAGS += $(ASFLAGS)

EXERCISE = $(notdir $(CURDIR))
FILE = $(subst -,_,$(EXERCISE))

OBJS = $(FILE).o $(FILE)_test.o unity/unity.o

CC_CMD = $(CC) $(ALL_CFLAGS) -c -o $@ $<

all: test-$(EXERCISE)
	@./test-$(EXERCISE)

test-$(EXERCISE): $(OBJS)
	@$(CC) $(ALL_CFLAGS) -o $@ $(OBJS)

$(FILE).o: $(FILE).asm
	@$(AS) $(ALL_ASFLAGS) -o $@ $<

$(FILE)_test.o: $(FILE)_test.c
	@$(CC_CMD)

unity/unity.o: unity/unity.c unity/unity.h unity/unity_internals.h
	@$(CC_CMD)

clean:
	@rm -f *.o unity/*.o test-$(EXERCISE)

.PHONY: all clean
