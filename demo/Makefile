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

test_demo: 
#$(MAKE) -C $(Z92) ds_tests
	$(MAKE) -C $(Z92) logic_tests

mem_demo: 
#$(MAKE) -C $(Z92) ds_memtests
	$(MAKE) -C $(Z92) logic_memtests

san_demo: 
#$(MAKE) -C $(Z92) ds_sanitize
	$(MAKE) -C $(Z92) merchsan

clean: 
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: 
