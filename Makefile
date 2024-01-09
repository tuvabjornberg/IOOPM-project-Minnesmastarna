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
	$(MAKE) -C $(DEMO) test_demo

memtest:
	$(MAKE) -C $(TEST) memtest
	$(MAKE) -C $(DEMO) memexample
	$(MAKE) -C $(DEMO) mem_demo

cov:
	$(MAKE) -C $(TEST) cov

prof:
	$(MAKE) -C $(TEST) prof

testdemo: 
	$(MAKE) -C $(DEMO) test_demo
#$(MAKE) -C $(DEMO) test_demo_ui

memdemo: 
	$(MAKE) -C $(DEMO) mem_demo
#$(MAKE) -C $(DEMO) mem_demo_ui_arg
#$(MAKE) -C $(DEMO) mem_demo_ui	

sandemo:
	$(MAKE) -C $(DEMO) san_demo
#$(MAKE) -C $(DEMO) san_demo_ui

example:
	$(MAKE) -C $(DEMO) memexample
  
clean:
	rm -f *.o
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: all src test memtest cov prof testdemo memdemo sandemo example clean 