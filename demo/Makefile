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
  
test_demo:
	$(MAKE) -C $(Z92) ds_tests
	$(MAKE) -C $(Z92) logic_tests

mem_demo:
	$(MAKE) -C $(Z92) ds_memtests
	$(MAKE) -C $(Z92) logic_memtests

san_demo:
	$(MAKE) -C $(Z92) ds_sanitize
	$(MAKE) -C $(Z92) logic_sanitize

test_demo_ui: 
	$(MAKE) -C $(Z92) ui_tests

mem_demo_ui: 
	$(MAKE) -C $(Z92) ui_memtests

mem_demo_ui_arg: 
	$(MAKE) -C $(Z92) ui_arg_memtests

san_demo_ui: 
	$(MAKE) -C $(Z92) ui_sanitize

clean:
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: memexample sanexample test_demo mem_demo san_demo test_demo_ui mem_demo_ui mem_demo_ui_arg san_demo_ui clean