C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
VPATH           = ../src 

%.o:  %.c 
	$(C_COMPILER) $(C_OPTIONS) $^ -c

clean: 
	rm -f *.o *.out

.PHONY: 
