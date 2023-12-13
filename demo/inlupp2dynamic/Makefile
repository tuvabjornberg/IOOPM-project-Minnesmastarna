C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g 
C_SANITIZE	   = -fsanitize=address
C_LINK_OPTIONS = -lm 
CUNIT_LINK     = -lcunit
C_PROF		   = -pg
C_GCOV	   	   = -fprofile-arcs -ftest-coverage
VPATH		   = user_interface : data_structures : utils : tests : logic

%.o:  %.c 
	$(C_COMPILER) $(C_OPTIONS) $^ -c 

ui.out: ui.o hash_table.o linked_list.o utils.o merch_storage.o shop_cart.o hash_fun.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ 


ui_san.out: ui.c hash_table.c linked_list.c utils.c merch_storage.c shop_cart.c hash_fun.c
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $(C_SANITIZE) $^ -o $@ 

ui_sanitize: ui_san.out
	./ui_san.out < tests/ui_tests.txt

merch_storage_tests.out: merch_storage_tests.o merch_storage.o shop_cart.o hash_table.o linked_list.o hash_fun.o	
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK)

shop_cart_tests.out: shop_cart_tests.o shop_cart.o hash_table.o linked_list.o merch_storage.o hash_fun.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $(C_OPTIONS) $^ -o $@ $(CUNIT_LINK) 

tests: merch_storage_tests.out shop_cart_tests.out 
	./merch_storage_tests.out 
	./shop_cart_tests.out

ui_tests: ui.out
	./ui.out < tests/ui_tests.txt

merch_test_coverage.out: merch_storage_tests.o merch_storage.c shop_cart.o hash_table.o linked_list.o hash_fun.o	
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)
shop_test_coverage.out: shop_cart_tests.o shop_cart.c hash_table.o linked_list.o merch_storage.o hash_fun.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)
ui_test_coverage.out: ui.c shop_cart.o hash_table.o linked_list.o merch_storage.o hash_fun.o utils.o
	$(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(CUNIT_LINK) $(C_GCOV)

#cov: merch_test_coverage.out shop_test_coverage.out ui_test_coverage.out
#	./ui_test_coverage.out < tests/ui_tests.txt
#	gcov -b -c ui.c
#	./merch_test_coverage.out	
#	gcov -b -c merch_storage.c
#	./shop_test_coverage.out
#	gcov -b -c shop_cart.c

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


clean:
	rm -f *.o *.out *.profiling *.gcno *gcda *.gcov ui merch_storage_tests shop_cart_tests ui_sanitize


mem_tests: merch_storage_tests.out shop_cart_tests.out 
	valgrind --leak-check=full ./shop_cart_tests.out
	valgrind --leak-check=full ./merch_storage_tests.out	

mem_ui: ui.out
	valgrind --leak-check=full ./ui.out  

mem_ui_arg: ui.out
	valgrind --leak-check=full ./ui.out < tests/ui_tests.txt


.PHONY: ui_sanitize tests ui_tests cov prof clean mem_tests mem_ui mem_ui_arg
