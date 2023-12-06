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

refmem_test_sanitize: 
	$(MAKE) -C $(TEST) memtest

cov: 
	$(MAKE) -C $(TEST) cov

prof: 
	$(MAKE) -C $(TEST) prof

demo: 
	$(MAKE) -C $@

clean: 
	rm -f *.o
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
	$(MAKE) -C $(DEMO) clean

.PHONY: $(SRC)
