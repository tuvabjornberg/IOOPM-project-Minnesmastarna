# Code Review Report
Explain how you have used pull requests (PRs) and continuous reviewing of code that goes into "master".

Ute i arbetslivet gör man detta av flera anledningar:
    Kvalitetssäkring
    Utvecklare blir modigare när man delar ansvar för korrekthet
    När man vet att någon måste läsa koden skriver man ofta bättre kod
    Man sprider kunskap om vad som händer i projektet till fler


Redovisa i projektrapporten hur denna typ av kodgranskning har fungerat och relatera till den typ som gjordes under tidigare faser, som var mindre disciplinerad och inte rörde er egen kod.


Några saker att fundera på:
    What were the consequences of using code reviews before commiting?
            (Started, down below)
    Was it only extra work or did it serve any purpose?
            (Started, down below)
    Did you use a checklist or other formalised procedure for the code reviews? How did that work out?
            (Started, down below)
    How did the colourful diffs on GitHub work as support for seeing what had changed?
            (Started, down below)
    How often was a Pull Request pushed back for changes (or similar) before it was merged into master?
            (Not started yet)
    How many Pull Request did you make?
            (Not started. Check right before handing in, update with correct number)
    Were they open for a long time on average?
            (Not started. Check this, some took longer time than others.)
    Did every coder work in the same manner using Pull Request?
            (Not started. Personal reflection, do as discussion)
    If you were to restart the project tomorrow, what would you keep and what would you do differently?
            (Not started. Do together as discussion)

Together with the actual pull request log on GitHub, this file should convince the examiner that you pass Y66.



# Code reviews and pull requests
During the course of the project we used pull requests and continuous reviewing of the code that goes into our main branch. The goal being to verify code as well as make sure we only push working code (as far as we know) into the master branch. The reason being that we wanted to make sure everybody has a good base code when starting on something new. If we were to push into main before anything has been reviewed or tested properly someone could be building something based on bad or broken code, which in itself can lead to more issues down the line.


## What has our process been like?
Before we started with the actual coding we set up a strategy for code review and made sure everyone learned how to start with pull requests at least. Another important baseline we set was to communicate if you have created a pull request and await review.


The main process has been an author pushing their code into a branch (not the main branch) and creating a pull request. When announcing this to the rest of the group someone will review and test their code. The goal being it's reviewed as soon as possible. A reviewer can usually be found if the author just asks a person in the group directly, asks volunteers at meetings or through our group communication channel.


Some of the most efficient reviews were done with the author in discussion with the person(s) reviewing and changes made accordingly as fast as possible. This dynamic has contributed to some of our best and most efficent reviewes.
An efficent review is especially valuable if the code reviewed is important for the project to move forward.


In some cases we tried to have two reviewers on the same code, in order to have several inputs on the code.


## How did we review our code?
During the beginning stages of the project, most reviews were done as a quick double check that the code looked fine. We didn't have a set standard for how to review.


Everyone was taught how to create their own branches, commit like normal and create pull requests when done with their part. We had some learning experiences in the beginning with the first pull requests but eventually got the hang of it. A part of the process was trying to make sure everyone will try to review everyone's code at some point. While this was harder to put into practice we tried to ask different people in the group to review one's code, to avoid the same pair writing and reviewing code over and over.


TODO:
After **** The procedure of reviewing without a protocol was adjusted to have more structured reviews and to better keep track of our work. We started using the code review protocol from the course (used for the P-achievements) as a baseline guide. We did not use the protocol as a rule to follow, more as a guide to get started and to give examples on what to look a bit extra on. We could use it as a crutch to fall back on if we didn't know what to look for when reviewing.


TODO:
* How often was a Pull Request pushed back for changes (or similar) before it was merged into master?
* How many Pull requests did you make?
* Were they open for a long time on average?


## Consequences of code reviews in GitHub
The beneficial consequences of using pull requests were the guarantee that the code was agreed between at least two people before given to the rest of the group, the author and the reviewer. During these code reviews both small errors and more concerning problems arose which were solved to a certain degree before being pushed into main.


We had more clear milestones when code was pushed into main because for important implementations we urged each other to update their current working branch to continue working on something we know works.


Though, this consequence did have its own drawbacks for certain implementations. In most cases it would be because we have started working on an implementation assuming another worked as imagined. Some branches could easily fall behind the main branch. This led to some people working on older versions, which meant that some implementations had to be changed when the newer code was pushed up.


This became an issue in cases where a review took time. For example, when we had to reimplement the release function most of the implementation for the Z92 program was done. But because this type of review was extensive, it took time before the affected members could have access to the updated code. Through the extensive review definitely was necessary.


Using pull requests did serve a good purpose. It made sure at least two people were on the same page about changes to the code. Easy mistakes were caught and formatting of the code could quickly be fixed. It was more work compared to how we have been working previously in the course, with the assignments, where in most cases reviews weren't made to this extent. In a group project with six people we have found it easier to use this system to avoid confusion and broken code, when used correctly. What is similar with the code reviews from the assignment is the use of a code review protocol. Though we have not used it to the same extent for this project, it has served a good purpose.


## GitHub tools - TODO:
Whether GitHub's built- in functions helped with reviewing the code is an individual opinion. <-- TODO:


The color difference on GitHub helped to distinguish old and new code. If a change were made to existing code the reviewer could see what changes were made, instead of manually trying to see what was removed or not by comparing the old with the new file. The color difference also helped to narrow down to only new code. It helped the reviewer only see relevant code. Furthermore, if the new code needed to be put into a context the reviewer simply could extend the file to see code already existing in the main branch.


## Redos and future use
###  Did every coder work in the same manner using Pull Request?
### If you were to restart the project tomorrow, what would you keep and what would you do differently?




# Link to GitHub pull requests
https://github.com/IOOPM-UU/Minnesmastarna/pulls
