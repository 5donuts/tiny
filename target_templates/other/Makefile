TARGETS = ret_one

LINKER_FLAGS = -s

all: clean $(TARGETS)

$(TARGETS):
	as $@.s -o $@.o
	ld -s $@.o -o $@.out

clean:
	rm -f *.o *.out
