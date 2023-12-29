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

## How do we test the program (Started on)
We have tested our program mainly through unit testing. This has been done through newly written tests. We have also had to change the tests from Z92 during the integration part of the project, so that they fit the mold of how the new code is written. The code from before can also be tested with a txt-file, to make sure that when using the user input, the program still won't have any memory leaks.

### Unit testing (Started on)
Unit tests were created using CUnit. These were created mainly during the first stage of the program, when we had to start implementation of the refmem functions. These were also split up into multiple files, so each test file handled different parts of the origin file.

This separation meant that we separated the standardised refmem tests into one file, whereas the destructor tests got their own file. This meant that if one of these files were to suddenly stop passing their tests, we could easily find which part of the program that was suddenly not working.

Because we had to create a queue structure, we had to test this one as well. This meant that this also got a few tests, to make sure that it wouldn't have any memory leaks, and work accordingly to how we want it to work. These tests were also created in a separate file, as they held no relevance to the refmem tests or the destructor tests.


### Integration testing
TODO: Add text here

### Regression testing
TODO: Add text here


## How have we automated the testing (Started on)
We have automated the tests with the use of CUnit and Makefiles. This type of automation has made it easier during the programming process, where we could almost always test any code which has been changed. The main Makefile was made so that the tests could be run from the outer file, and thus only had one Makefile which was used to run the program accordingly. This meant that once we started the integration phase of the code, the Makefile was updated so that it could run tose tests from the same Makefile.


## Graphical overview of code coverage
TODO: Add text here. This will be done after all code is written.


# LINK TO GITHUB ISSUE LOG (GENERAL)
https://github.com/IOOPM-UU/Minnesmastarna/issues



# LINKS TO NASTY BUGS THAT HAD TO BE FIXED
TODO: Add links here to the nastiest bugs that have been discovered, maybe with some text about what they were, and how we solved them.