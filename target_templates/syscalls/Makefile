TARGETS = sys_exit

LINKER_FLAGS = -s

all: clean $(TARGETS)

$(TARGETS):
	as $@.s -o $@.o
	ld -s $@.o -o $@.out

clean:
	rm -f $(TARGETS).o $(TARGETS).out
