C_COMPILER      = gcc
C_OPTIONS       = -Wall -pedantic -g
C_SANITIZE      = -fsanitize=address
C_LINK_OPTIONS  = -lm
CUNIT_LINK      = -lcunit
C_PROF          = -pg
C_GCOV          = -fprofile-arcs -ftest-coverage
VPATH           = ../src 

%.o:  %.c 
	$(C_COMPILER) $(C_OPTIONS) $^ -c

refmem_test.out: refmem_test.o refmem.o queue.o hash_table.o linked_list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)

queue_test.out: queue_test.o queue.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)

destructor_test.out: destructor_test.o refmem.o hash_table.o queue.o linked_list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)

test: refmem_test.out queue_test.out destructor_test.out
	./queue_test.out
	./refmem_test.out
	./destructor_test.out

memtest: refmem_test.out queue_test.out
	valgrind --leak-check=full ./queue_test.out
	valgrind --leak-check=full ./refmem_test.out

# f-sanitize, mem tool like valgrind
refmem_test_san.out: refmem_test.c refmem.c queue.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK)

queue_test_san.out: queue_test.c queue.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK)

test_sanitize: refmem_test_san.out queue_test_san.out
	./refmem_test_san.out
	./queue_test_san.out

refmem_test_coverage.out: refmem_test.o refmem.c queue.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)

queue_test_coverage.out: queue_test.o queue.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)

cov: refmem_test_coverage.out queue_test_coverage.out
	./queue_test_coverage.out
	gcov -b -c queue_test_coverage.out-queue.c
	./refmem_test_coverage.out
	gcov -b -c refmem_test_coverage.out-refmem.c

refmem_prof.out: refmem_test.c refmem.c queue.c
	$(C_COMPILER) $(C_OPTIONS) $^ -o $@ $(C_PROF) $(CUNIT_LINK) 

prof: refmem_prof.out 
	./refmem_prof.out 
	gprof refmem_prof.out gmon.out > refmem_prof.profiling

clean: 
	rm -f *.o *.out *.gcda *.gcno *.gcov *.profiling

.PHONY: test memtest test_sanitize cov prof
