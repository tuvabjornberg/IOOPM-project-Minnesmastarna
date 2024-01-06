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
	$(MAKE) -C $(DEMO) test_demo_ds

memtest:
	$(MAKE) -C $(TEST) memtest
	$(MAKE) -C $(DEMO) memexample
	$(MAKE) -C $(DEMO) mem_demo_ds

test_sanitize:
	$(MAKE) -C $(TEST) test_sanitize

cov:
	$(MAKE) -C $(TEST) cov

prof:
	$(MAKE) -C $(TEST) prof

testdemo:
	$(MAKE) -C $(DEMO) test_demo_ds

memdemo:
	$(MAKE) -C $(DEMO) mem_demo_ds

sandemo:
	$(MAKE) -C $(DEMO) san_demo_ds

example:
	$(MAKE) -C $(DEMO) memexample

sanexample:
	$(MAKE) -C $(DEMO) sanexample

clean:
	rm -f *.o
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: all src test memtest test_sanitize cov prof demo clean
