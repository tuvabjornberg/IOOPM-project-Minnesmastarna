# Dependencies
1.  `hash_table` comes from Tuva’s Assignment 1
2.  `linked_list` and `iterator` comes from Tuva’s Assignment 1
3.  `utils` comes from Marcus' bootstrap labs
4.  `common` comes from Tuva's Assignment 1


# Make commands
#### Remember to run make clean before any make commands:
```
$ make clean
```

   #### Build and run the webstore:
   ```
   $ make ui.out
   $ ./ui.out
   ```
   #### Run tests:
   ```
   for hash_table and linked_list:
   $ make ds_tests

   for merch_storage and shop_cart:
   $ make logic_tests

   for ui:
   $ make ui_tests
   ```

   #### Memory tests:
   ```
   for hash_table.c and linked_list.c
   $ make ds_memtests

   for merch_storage and shop_cart:
   $ make logic_memtests

   for ui without input file:
   $ make ui_memtests

   for ui with input file:
   $ make ui_arg_memtests
   or
   $ make ui_sanitize
   ```

   #### Coverage tests:
   ```
   $ make cov
   ```
   _Coverage tests done with gcov_\
   `merch_store.c`:\
    Lines executed:100.00% of 228\
    Branches executed:100.00% of 54\
    Taken at least once:96.30% of 54\
    Calls executed:100.00% of 75\
    Lines executed:100.00% of 228

   `shop_cart.c`:\
    Lines executed:100.00% of 93\
    Branches executed:100.00% of 18\
    Taken at least once:83.33% of 18\
    Calls executed:100.00% of 37\
    Lines executed:100.00% of 93

   `ui.c`:\
    Lines executed:100.00% of 295\
    Branches executed:100.00% of 118\
    Taken at least once:94.92% of 118\
    Calls executed:100.00% of 130\
    Lines executed:100.00% of 295


   #### Performace tests:
   ```
   for ui_tests.txt
   $ make prof

   for other .txt files:
   $ make ui_prof.out
   $ ./ui_prof.out < filename.txt
   $ gprof ui_prof.out gmon.out > output
   ```

   #### Time:
   ```
   $ make ui.out
   $ command time --verbose ./ui.out < filename.txt
   ```


 # Notes and error handling

  - Errors and edge-cases are handled, in some cases, by returning a NULL. merch_storage.c and shop_cart.c are mostly dependent on the error handeling in ui.c. Errors such as empty hashtables and invalid user inputs are handled with return messages to the user to retry their menu choice or choose another input.
  - ui.c also ensures proper memory management when using the allocated memory from hash_table, linked_list and iterator, (through merch_table and shop_cart) including freeing the allocated for keys, values, lists, iterators and options after use.