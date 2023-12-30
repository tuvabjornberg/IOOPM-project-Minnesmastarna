C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g 
VPATH           = src : test : demo

SRC = src
TEST = test
DEMO = demo

all: refmem.o 

%.o:  %.c 
	$(C_COMPILER) $(C_OPTIONS) $^ -c

src: 
	$(MAKE) -C $@

test: src
	$(MAKE) -C $(TEST) test

memtest: 
	$(MAKE) -C $(TEST) memtest

test_sanitize: 
	$(MAKE) -C $(TEST) test_sanitize

cov: 
	$(MAKE) -C $(TEST) cov

prof: 
	$(MAKE) -C $(TEST) prof

testdemo: 
	$(MAKE) -C $(DEMO) test_demo_hash
	$(MAKE) -C $(DEMO) test_demo_shopcart

memdemo: 
	$(MAKE) -C $(DEMO) mem_demo_hash
	$(MAKE) -C $(DEMO) mem_demo_shopcart

sandemo: 
#$(MAKE) -C $(DEMO) san_demo_hash
	$(MAKE) -C $(DEMO) san_demo_shopcart

example: 
	$(MAKE) -C $(DEMO) memexample

sanexample: 
	$(MAKE) -C $(DEMO) sanexample

sc_tests:
	$(MAKE) -C $(DEMO) sc_tests

sc_memtests:
	$(MAKE) -C $(DEMO) sc_memtests

clean: 
	rm -f *.o
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: all src test memtest test_sanitize cov prof demo clean
