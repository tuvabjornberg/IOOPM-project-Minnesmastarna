# Test Report
Explain how you are testing your project on three levels:
    Unit testing
    Integration testing
    Regression testing
Also explain how you have automated these things. 

Include a graphical overview of the code coverage (100% coverabe). 

You do not need to have tests of the demo code. It is presumed to have been properly tested in assignment 2. (But if you do find new bugs in the demo code, you should mention that.)

List your 6 most nasty bugs by linking to their issue pages on GitHub.

This file, together with the GitHub issue log, should convince the examiner that you pass Y69.



# ROUGH DRAFT, ADD POINTS BELOW THAT SHOULD BE IN REPORT

## How do we test the program 
We have tested our program mainly through unit testing. This has been done through newly written tests. We have also had to change the tests from Z92 during the integration part of the project, so that they fit the mold of how the new code is written. The code from before can also be tested with a txt-file, to make sure that when using the user input, the program still won't have any memory leaks.

### Unit testing 
Unit tests were created using CUnit. These were created mainly during the first stage of the program, when we had to start implementation of the refmem functions. These were also split up into multiple files, so each test file handled different parts of the origin file.

This separation meant that we separated the standardised refmem tests into one file, whereas the destructor tests got their own file. This meant that if one of these files were to suddenly stop passing their tests, we could easily find which part of the program that was suddenly not working.

Because we had to create a queue structure, we had to test this one as well. This meant that this also got a few tests, to make sure that it wouldn't have any memory leaks, and work accordingly to how we want it to work. These tests were also created in a separate file, as they held no relevance to the refmem tests or the destructor tests.

A lot of the files which were used for the integration was tested beforehand. This meant that instead of writing new tests, they were instead updated to work with our refmem file. Because most of it was tested beforehand, we didn't spend much time working with these tests and focused on making them run instead, which that itself took some time.


### Integration testing
There weren't many integration tests created for the project. Due to the integration code already being tested beforehand, the tests were mainly changed to pass when implementing the old code with the refmem file. As these tests made sure that all the code worked properly beforehand, this wasn't really something we had to rewrite when did the project.

We had some trouble with the input.txt file when testing after the integration with refmemhad happened. As these problems arose, we instead tested parts of this manually. This made it so that we couldn't really test the UI-functions with the same cases automatically, but had to instead remember what we wrote when testing. Because of this, we couldn't really know if the integration was working completely all the time, but had to trust that our manual tests were good enough.

TODO: Continue


### Regression testing
Since we created unit tests when creating the functions, these became our regression tests. This made it so that if we ever changed the code, we could use the unit tests to make sure that the code still worked as intended. As these were made as unit tests, they were extended over time, but once we had created a test that we knew worked in the beginning, they weren't modified to make sure the program always aspired to work the same. 

The tests that previously were a part of the Z92 weren't initially regression tests when they were first adapted, but became once we started implementation. Once we had figured out how the tests had to be changed in order to suit the project, these tests were mostly left untouched. An exception to this is some of the logic tests, that during the integration part had to be adapted to work without certain elements. These had the correct lines commented out, so that once the expected code worked, the tests would go back to the way they were.

TODO: Continue



## How have we automated the testing 
We have automated the tests with the use of CUnit and Makefiles. This type of automation has made it easier during the programming process, where we could almost always test any code which has been changed. The main Makefile was made so that the tests could be run from the outer file, and thus only had one Makefile which was used to run the program accordingly. This meant that once we started the integration phase of the code, the Makefile was updated so that it could run those tests from the same Makefile.


## Graphical overview of code coverage
TODO: Add text here. This will be done after all code is written.


# Link to GitHub Issue Log (GENERAL)
https://github.com/IOOPM-UU/Minnesmastarna/issues

## Our most nasty bugs
### Bug 1
TODO: Add link

### Bug 2
TODO: Add link

### Bug 3
TODO: Add link

### Bug 4
TODO: Add link

### Bug 5
TODO: Add link

### Bug 6
TODO: Add link
