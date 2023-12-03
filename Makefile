C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
C_SANITIZE      = -fsanitize=address
C_LINK_OPTIONS  = -lm
CUNIT_LINK      = -lcunit
C_PROF          = -pg
C_GCOV          = -fprofile-arcs -ftest-coverage
VPATH           = src : test : demo

all: refmem.o

refmem.o: refmem.c
	$(C_COMPILER) $(C_OPTIONS) $< -c -o $@

# demo
#demo/demo.o: demo.c
#	$(C_COMPILER) $(C_OPTIONS) $< -c -o $@
#
#demo: demo.o
#	./demo/demo.o



test/refmem_test.out: refmem_test.o refmem.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)
	
test: refmem_test.out
	./test/refmem_test.out



memtest: refmem_test.out
	valgrind --leak-check=full ./test/refmem_test.out

# f-sanitize, mem tool like valgrind
test/refmem_test_san.out: refmem_test.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK)

test_sanitize: refmem_test_san.out
	./test/refmem_test_san.out



test/refmem_coverage.out: test/refmem_test.o refmem.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)

# may work diff depending on your computer
cov1: refmem_coverage.out
	./test/refmem_coverage.out
	gcov -b -c src/refmem.c

cov2: refmem_coverage.out 
	./test/refmem_coverage.out
	gcov -b -c test/refmem_coverage.out-refmem.c



test/tests_prof.out: refmem_test.c refmem.c
	$(C_COMPILER) $(C_OPTIONS) $^ -o $@ $(C_PROF) $(CUNIT_LINK)

# gmon.out is always written in programs current working dir, 
# to avoid: use local makefile??
prof: tests_prof.out
	./test/tests_prof.out
	gprof test/tests_prof.out gmon.out > test/tests_prof.profiling



clean:
	rm -f *.o *.out *.profiling *.gcno *gcda *.gcov
	rm -f src/*.o src/*.out
	rm -f test/*.o test/*.out test/*.profiling test/*.gcno test/*gcda test/*.gcov
	rm -f demo/*.out

.PHONY: all test memtest test_sanitize cov1 cov2 prof clean
