C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g
C_SANITIZE	   = -fsanitize=address
C_LINK_OPTIONS = -lm
CUNIT_LINK     = -lcunit
C_PROF		   = -pg
C_GCOV	   	   = -fprofile-arcs -ftest-coverage
VPATH		   = user_interface : data_structures : utils : tests : logic  : ../../src

%.o:  %.c
	$(C_COMPILER) $(C_OPTIONS) $^ -c

ui.out: ui.o hash_table.o linked_list.o utils.o merch_storage.o shop_cart.o hash_fun.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@


merch_storage_tests.out: merch_storage_tests.o merch_storage.o shop_cart.o hash_table.o linked_list.o hash_fun.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)

shop_cart_tests.out: shop_cart_tests.o shop_cart.o hash_table.o linked_list.o merch_storage.o hash_fun.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)

logic_tests: merch_storage_tests.out shop_cart_tests.out
	./merch_storage_tests.out
#	./shop_cart_tests.out

logic_memtests: merch_storage_tests.out shop_cart_tests.out
#	valgrind --leak-check=full ./shop_cart_tests.out
	valgrind --leak-check=full ./merch_storage_tests.out

ui_tests: ui.out
	./ui.out < tests/ui_tests.txt

ui_memtests: ui.out
	valgrind --leak-check=full ./ui.out

ui_arg_memtests: ui.out
	valgrind --leak-check=full ./ui.out < tests/ui_tests.txt

hash_test.out: hash_table_tests.o hash_table.o linked_list.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK)

list_test.out: linked_list.o linked_list_tests.o refmem.o queue.o list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK)

ds_tests: hash_test.out list_test.out
	./hash_test.out
	./list_test.out

ds_memtests: hash_test.out list_test.out
	valgrind --leak-check=full ./hash_test.out
	valgrind --leak-check=full ./list_test.out

hash_san.out: hash_table_tests.c hash_table.c linked_list.c refmem.c queue.c list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK)

list_san.out: linked_list_tests.c linked_list.c refmem.c queue.c list.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK)

ds_sanitize: hash_san.out list_san.out
	./hash_san.out
	./list_san.out

merch_test_coverage.out: merch_storage_tests.o merch_storage.c shop_cart.o hash_table.o linked_list.o hash_fun.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)
shop_test_coverage.out: shop_cart_tests.o shop_cart.c hash_table.o linked_list.o merch_storage.o hash_fun.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)
ui_test_coverage.out: ui.c shop_cart.o hash_table.o linked_list.o merch_storage.o hash_fun.o utils.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)

cov: merch_test_coverage.out shop_test_coverage.out ui_test_coverage.out
	./ui_test_coverage.out < tests/ui_tests.txt
	gcov -b -c ui_test_coverage.out-ui.c
	./merch_test_coverage.out
	gcov -b -c merch_test_coverage.out-merch_storage.c
	./shop_test_coverage.out
	gcov -b -c shop_test_coverage.out-shop_cart.c

ui_prof.out: ui.c hash_table.c linked_list.c utils.c merch_storage.c shop_cart.c hash_fun.c
	$(C_COMPILER) $(C_OPTIONS) $^ -o $@ $(C_PROF)

merch_storage_prof.out: merch_storage_tests.c merch_storage.c shop_cart.c hash_table.c linked_list.c hash_fun.c
	$(C_COMPILER) $(C_OPTIONS) $^ -o $@ $(C_PROF) $(CUNIT_LINK)

shop_cart_prof.out: shop_cart_tests.c shop_cart.c hash_table.c linked_list.c merch_storage.c hash_fun.c
	$(C_COMPILER) $(C_OPTIONS) $^ -o $@ $(C_PROF) $(CUNIT_LINK)

prof: ui_prof.out merch_storage_prof.out shop_cart_prof.out shop_cart_prof.out
	./ui_prof.out < tests/ui_tests.txt
	gprof ui_prof.out gmon.out > ui_tests.profiling
	./merch_storage_prof.out
	gprof merch_storage_prof.out gmon.out > merch_storage_prof.profiling
	./shop_cart_prof.out
	gprof shop_cart_prof.out gmon.out > shop_cart_prof.profiling

ui_san.out: ui.c hash_table.c linked_list.c utils.c merch_storage.c shop_cart.c hash_fun.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@

ui_sanitize: ui_san.out
	./ui_san.out < tests/ui_tests.txt

merchsan.out: merch_storage_tests.c merch_storage.c hash_table.c linked_list.c utils.c shop_cart.c hash_fun.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ $(CUNIT_LINK)

merchsan: merchsan.out
	./merchsan.out

clean:
	rm -f *.o *.out *.profiling *.gcno *gcda *.gcov ui merch_storage_tests shop_cart_tests ui_sanitize

.PHONY: ui_sanitize tests ui_tests cov prof clean mem_tests mem_ui mem_ui_arg merchsan ds_memtests ds_tests
