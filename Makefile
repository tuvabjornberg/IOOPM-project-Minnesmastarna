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

demo: src
	$(MAKE) -C $(DEMO) demons

demotxt:
	$(MAKE) -C $(DEMO) demo_txt

test: src
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
	rm -f *.o
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: all src test memtest cov prof example clean 