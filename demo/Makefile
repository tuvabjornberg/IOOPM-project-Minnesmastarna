C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
C_LINK_OPTIONS = -lm
CUNIT_LINK     = -lcunit
C_SANITIZE	   = -fsanitize=address
VPATH           = ../src : Z92 

Z92 = Z92

%.o:  %.c
	$(C_COMPILER) $(C_OPTIONS) $^ -c

example.out: example.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@

memexample: example.out
	valgrind --leak-check=full ./example.out

testdemo:
	$(MAKE) -C $(Z92) ds_tests
	$(MAKE) -C $(Z92) logic_tests
	$(MAKE) -C $(Z92) ui_tests

memdemo:
	$(MAKE) -C $(Z92) ds_memtests
	$(MAKE) -C $(Z92) logic_memtests
	$(MAKE) -C $(Z92) ui_arg_memtests
	$(MAKE) -C $(Z92) ui_memtests

sandemo:
	$(MAKE) -C $(Z92) ds_sanitize
	$(MAKE) -C $(Z92) logic_sanitize
	$(MAKE) -C $(Z92) ui_sanitize

clean:
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: memexample demo testdemo memdemo sandemo clean