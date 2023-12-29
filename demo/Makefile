C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
C_LINK_OPTIONS = -lm
CUNIT_LINK     = -lcunit
C_SANITIZE	   = -fsanitize=address
VPATH           = ../src : Z92 : Z92/tests : Z92/data_structures : Z92/logic : Z92/utils

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

test_demo_hash: 
	$(MAKE) -C $(Z92) ds_tests

mem_demo_hash: 
	$(MAKE) -C $(Z92) ds_memtests

san_demo_hash: 
	$(MAKE) -C $(Z92) hash_sanitize

clean: 
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: 
