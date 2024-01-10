# Test Report

We have tested our program mainly through unit testing. This has been done through newly written tests. We have also had to change the tests from Z92 during the integration part of the project, so that they fit the mold of how the new code is written. The code from before can also be tested with a txt-file, to make sure that when using the user input, the program still won't have any memory leaks.

### Unit testing 
Unit tests were created using CUnit. These were created mainly during the first stage of the program, when we had to start implementation of the refmem functions. These were also split up into multiple files, so each test file handled different parts of the origin file.

This separation meant that we separated the standardised refmem tests into one file, whereas the destructor tests got their own file. This meant that if one of these files were to suddenly stop passing their tests, we could easily find which part of the program that was suddenly not working.

Because we had to create a queue structure, we had to test this one as well. This meant that this also got a few tests, to make sure that it wouldn't have any memory leaks, and work accordingly to how we want it to work. These tests were also created in a separate file, as they held no relevance to the refmem tests or the destructor tests.

A lot of the files which were used for the integration was tested beforehand. This meant that instead of writing new tests, they were instead updated to work with our refmem file. Because most of it was tested beforehand, we didn't spend much time working with these tests and focused on making them run instead, which that itself took some time.


### Integration testing
There weren't many integration tests created for the project. Due to the integration code already being tested beforehand, the tests were mainly changed to pass when implementing the old code with the refmem file. As these tests made sure that all the code worked properly beforehand, this wasn't really something we had to rewrite when did the project.

We had some trouble with the input.txt file when testing after the integration with refmemhad happened. As these problems arose, we instead tested parts of this manually. This made it so that we couldn't really test the UI-functions with the same cases automatically, but had to instead remember what we wrote when testing. Because of this, we couldn't really know if the integration was working completely all the time, but had to trust that our manual tests were good enough. later, we learned that the txt file problems were only happening to one computer, which could mean that the problem happened on a system level, instead of having the program malfunctioning.


### Regression testing
Since we created unit tests when creating the functions, these became our regression tests. This made it so that if we ever changed the code, we could use the unit tests to make sure that the code still worked as intended. As these were made as unit tests, they were extended over time, but once we had created a test that we knew worked in the beginning, they weren't modified to make sure the program always aspired to work the same. 

The tests that previously were a part of the Z92 weren't initially regression tests when they were first adapted, but became once we started implementation. Once we had figured out how the tests had to be changed in order to suit the project, these tests were mostly left untouched. An exception to this is some of the logic tests, that during the integration part had to be adapted to work without certain elements. These had the correct lines commented out, so that once the expected code worked, the tests would go back to the way they were.


## How have we automated the testing 
We have automated the tests with the use of CUnit and Makefiles. This type of automation has made it easier during the programming process, where we could almost always test any code which has been changed. The main Makefile was made so that the tests could be run from the outer file, and thus only had one Makefile which was used to run the program accordingly. This meant that once we started the integration phase of the code, the Makefile was updated so that it could run those tests from the same Makefile.'

We also automated it so that if you were to write "make test" in the termainal, all tests were run. This became the way regression tests were run, as it was an easy command to make sure that everything was working as it should. Automation with Valgrind was run through "make memtest", which ran all tests, as well as the example file that was given in the instructions. This was especially useful to see that if the code that could pass the tests didn't have any memory problems, and was good enough to push up into the main branch.

While integration, we made sure that the demo files could be run throgh their own command in the Makefile. This was done through "make testdemo" and "make memdemo", which ran the tests normally, and through Valgrind respectively. This was good to have when we weren't doing any changes to the refmem code, and instead were just testing that our integration was working.


## Problems that arose during testing
One problem that arose while testing happened while testing the boundaries of the hash table. We created a test that added 1000 entries into a hash table, and later removed those entries. During this test, we realised that although there are no memory leakage, we have more frees than allocations. We realised that for 80 inserts, the frees and allocations are the same, but once we have 81 or more entries, the number isn't balanced. We decided to keep this, as the tests still work and 



## Overview of code coverage
The refmem_tests and destructor_tests combined have 100%. Since we've wanted to strive for a good coverage for these files, this is a very good result to see. This meant that all the new code which we have written is tested fully, and works as we want it to. 

Since we've only adapted the previous code, and have only adapted the Z92-files, the coverage won't have changed. This means that the coverage will be as the old coverage, which was 100%. 

# Link to GitHub Issue Log (GENERAL)
https://github.com/IOOPM-UU/Minnesmastarna/issues

## Our most nasty bugs
### Bug 1
https://github.com/IOOPM-UU/Minnesmastarna/issues/6

### Bug 2
https://github.com/IOOPM-UU/Minnesmastarna/issues/9

### Bug 3
https://github.com/IOOPM-UU/Minnesmastarna/issues/11

### Bug 4
https://github.com/IOOPM-UU/Minnesmastarna/issues/23

### Bug 5
https://github.com/IOOPM-UU/Minnesmastarna/issues/27

### Bug 6
https://github.com/IOOPM-UU/Minnesmastarna/issues/29
