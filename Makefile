C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
C_LINK_OPTIONS = -lm
VPATH           = src : test : demo

SRC = src
TEST = test
DEMO = demo
UI = demo/Z92/user_interface
DATA_STRUCTURES = demo/Z92/data_structures
LOGIC = demo/Z92/logic
UTILS = demo/Z92/utils

all: refmem.o

%.o:  %.c
	$(C_COMPILER) $(C_OPTIONS) $^ -c

demo: demo.out

demo.out: $(UI)/ui.c $(DATA_STRUCTURES)/hash_table.c $(DATA_STRUCTURES)/linked_list.c $(UTILS)/utils.c $(LOGIC)/merch_storage.c $(LOGIC)/shop_cart.c $(UTILS)/hash_fun.c $(SRC)/refmem.c $(SRC)/queue.c $(SRC)/list.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@

test:
	$(MAKE) -C $(TEST) test
	$(MAKE) -C $(DEMO) testdemo

memtest:
	$(MAKE) -C $(TEST) memtest
	$(MAKE) -C $(DEMO) memexample
	$(MAKE) -C $(DEMO) memdemo

cov:
	$(MAKE) -C $(TEST) cov

example:
	$(MAKE) -C $(DEMO) memexample

clean:
	rm -f *.o *.out
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: all demo test memtest cov example clean