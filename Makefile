C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
VPATH           = src : test : demo

TEST = test
DEMO = demo

all: refmem.o

%.o:  %.c
	$(C_COMPILER) $(C_OPTIONS) $^ -c

demo:
	$(MAKE) -C $(DEMO) demons

test: 
	$(MAKE) -C $(TEST) test
	$(MAKE) -C $(DEMO) test_demo

memtest:
	$(MAKE) -C $(TEST) memtest
	$(MAKE) -C $(DEMO) memexample
	$(MAKE) -C $(DEMO) mem_demo

cov:
	$(MAKE) -C $(TEST) cov

prof:
	$(MAKE) -C $(TEST) prof

example:
	$(MAKE) -C $(DEMO) memexample
  
clean:
	rm -f *.o .out
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: all test memtest cov prof example clean 