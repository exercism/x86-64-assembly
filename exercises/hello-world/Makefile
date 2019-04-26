AS = nasm

CFLAGS = -g -Wall -Wextra -pedantic -Werror
LDFLAGS =
ASFLAGS = -g -F dwarf -Werror

ifeq ($(shell uname -s),Darwin)
	ALL_CFLAGS = -fno-pie -Wno-unused-command-line-argument
	ALL_LDFLAGS = -Wl,-no_pie
	ALL_ASFLAGS = -f macho64 --prefix _
else
	ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
		ALL_CFLAGS = -fno-pie
		ALL_LDFLAGS = -no-pie
	endif
	ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
		ALL_CFLAGS = -fno-pie
		ALL_LDFLAGS = -nopie
	endif
	ifeq ($(CC),clang)
		ALL_CFLAGS = -fno-pie -Wno-unused-command-line-argument
		ALL_LDFLAGS = -nopie
	endif
	ALL_ASFLAGS = -f elf64
endif

ALL_CFLAGS += -std=c99 -m64 $(CFLAGS)
ALL_LDFLAGS += $(LDFLAGS)
ALL_ASFLAGS += $(ASFLAGS)

EXERCISE = $(notdir $(CURDIR))
FILE = $(subst -,_,$(EXERCISE))

OBJS = $(FILE).o $(FILE)_test.o unity/unity.o

CC_CMD = $(CC) $(ALL_CFLAGS) -c -o $@ $<

all: test-$(EXERCISE)
	@./test-$(EXERCISE)

test-$(EXERCISE): $(OBJS)
	@$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) -o $@ $(OBJS)

$(FILE).o: $(FILE).asm
	@$(AS) $(ALL_ASFLAGS) -o $@ $<

$(FILE)_test.o: $(FILE)_test.c
	@$(CC_CMD)

unity/unity.o: unity/unity.c unity/unity.h unity/unity_internals.h
	@$(CC_CMD)

clean:
	@rm -f *.o unity/*.o test-$(EXERCISE)

.PHONY: all clean
