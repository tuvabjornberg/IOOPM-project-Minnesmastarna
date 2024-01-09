# Code Quality Report
You should explain why you think you have written good code and why you think that the code is good!
Hur har ni sett till att koden är läsbar för alla i teamet?
Använd gärna ett verktyg (t.ex. astyle) för att automatiskt formattera kod på ett enhetligt sätt.

You can go about this in any way that you like that is helpful to the reviewer. Helpful saves time, meaning that blanket statements such as “just look at all the code” are not good enough (discussing each function individually also would not save time).

Under kursens gång har kodkvalitet beaktats åtskilliga gånger. Under projektet skall ni skriva kod av hög kvalitet! Vad betyder det? (Läsbarhet? Underhållsbarhet? Prestanda? Korrekthet? Testbarhet? Etc…) Hur har det tagit sig uttryck i ert system? Vad har det fått för konsekvenser?

This file, together with the GitHub issue log, should convince the examiner that you pass Y65.



# ROUGH DRAFT, ADD POINTS BELOW THAT SHOULD BE IN REPORT

## Why is code quality important
Coding is a very free practice, that can be approached through many different courses of action. Solving problems and actually writing working code can be done very differently, so to actually allow people to efficiently work together in a project like this one, certain conditions need to be set. These conditions are typically made to keep people in line with their work, to allow a wider understanding for the people around them, wether that be group members or reviewers. Following these to uphold quality and familiarity is a great practice that benefits everyone in the end.


## Why have we written good code, why is our code good
Our code consistently adheres to the GNU coding standard, which is important in a project that relies on several people working together. This approach ensures readability and maintainability, which is crucial when also using regular code reviewing to uphold quality. The project itself also provides an important factor in general code quality with the continuous streamlining of making a solid and efficient memory management system. 

The constant improvement that have been made to our original starting point, and the changes in direction we have made along the way is also something to mention that has contributed to a more efficient and reliable memory management system. Exploring different approaches to the implementation, like for example how we went back and forth with how we would store allocated objects in ```refmem.c```, gave us an insight into the pros and cons of either using a hash table storage or just keeping the meta data in a struct for instance. These obstacles force you to actually understand the code, and discussions about them also means that the whole group can get involved and actually take part.

Another crucial aspect of code quality reassurance is consistently and rigorously testing the code and making sure everything actually works. We have always kept this factor close to our hearts by only ever allowing thoroughly verified and functioning code to be merged to our main branch, which is of course a good practice since we want to keep that branch stable and reliable. 

So in conclusion we have always made sure to be careful with the code we write and the changes we make, to try and always avoid errors and bugs no matter how small.


## Is the code readable for everyone in the team
Readability once again points to our chosen coding standard approach, where creating a familiar code environment for everyone facilitates working together with code reviews. This is also important in the way that everyone taking part in code reviews provides a better all around understanding in the group of what certain code does. This however is only a small part of readability. 

Clear modularization of the project files is also a part of maintaining readable code in the way of simplifying navigation, and this along with using properly abstracted functions within the modules provide a good and simple flow of the code, that is of course easier to understand. Abstracting properly has a lot to do with avoiding repetition of code, which is essential for making a code suitable for reviewing, since it saves time for the reviewer.

All functions have documentation in their interface files for a more general understanding, but we don't really have comments in the code. However this is not really an issue, when we're constantly reviewing each others code using pull request, since you get to take a closer look at changes that have been made. Along with the branch owners comment when creating the pull request, you can often connect the dots about what is happening in the code, and this continuous process throughout the projects course provides great support for becoming better at it.


## Helpful to reviewer
* For specifics, look in the instruction above.
To facilitate reviewing, we have of course done the usual work of functional breakdowns and clear modularity, where we consistently have followed the coding standard. To give a high-level overview of how the project structure is built up, we basically have the ```src```-folder that contains the memory management and related files to support it, and the ```demo```-folder that has the integration of it.

Diving a little bit deeper into ```demo``` and further into ```Z92```, we have made a logical division of files with separate purpose and functionality. ```data_structures```is essentially what it says, with the hash table structure and linked listed structure completely integrated. ```logic``` instead includes the actual "assignment 2" files for the warehouse, that are of course also integrated.

Practical usage of the code through testing can be found in both ```Z92``` for integration-related files, and outside or ```src``` for the memory management. ```Z92``` also contains ```example.c``` which is a simple program designed to run with the memory management system, so for the sake of understanding, a quick glance at how it runs might clear things up a bit.

README-files can be found in the starting directory, as well as in ```/demo/Z92```, to get an overview of how to compile and run certain parts of the program.


## What does it mean to have good code
Having good code can mean a lot of things, but it usually boils down to being something multiple people with different end-goals can comprehend. There are of course multiple attributes that is connected to this, like maintainability, reliability, testability and efficiency to name a few. Writing optimized, well-structured code that functions reliably under various scenarios, and is easy to test and maintain is also a major factor in writing good code. A solid combination of these will reinforce a project like this one, and keep things looking clean.


## What code standard have we used, how is it good?
Our decision to adopt the GNU coding standard was a democratic choice made within the group, valuing its emphasis on consistency, readability, and collaboration. This code standard was a straight forward way to incorporate solid and good practices while coding, and has worked out that way throughout the course of the project.


# LINK TO GITHUB ISSUE LOG
https://github.com/IOOPM-UU/Minnesmastarna/issues