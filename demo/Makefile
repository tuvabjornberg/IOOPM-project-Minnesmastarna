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

shop_cart_tests.out: shop_cart_tests.o shop_cart.o hash_table.o linked_list.o merch_storage.o hash_fun.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

sc_tests: shop_cart_tests.out 
	./shop_cart_tests.out

sc_memtests: shop_cart_tests.out 
	valgrind --leak-check=full ./shop_cart_tests.out

clean: 
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: 
