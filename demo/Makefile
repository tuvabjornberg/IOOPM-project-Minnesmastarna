C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
VPATH           = ../src : Z92

Z92 = Z92

%.o:  %.c 
	$(C_COMPILER) $(C_OPTIONS) $^ -c

clean: 
	rm -f *.o *.out
	$(MAKE) -C $(Z92) clean

.PHONY: 
