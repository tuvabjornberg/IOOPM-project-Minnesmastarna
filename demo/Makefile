C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
C_LINK_OPTIONS = -lm 
C_SANITIZE	   = -fsanitize=address
VPATH           = ../src : Z92

Z92 = Z92

%.o:  %.c 
	$(C_COMPILER) $(C_OPTIONS) $^ -c

example.out: example.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ 

memexample: example.out
	valgrind --leak-check=full ./example.out

examplesan.out: example.c refmem.c queue.c list.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK) 

sanexample: examplesan.out
	./examplesan.out

clean: 
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: 
