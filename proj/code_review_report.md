# Code Review Report
Explain how you have used pull requests (PRs) and continuous reviewing of code that goes into "master". 

Ute i arbetslivet gör man detta av flera anledningar:
    Kvalitetssäkring
    Utvecklare blir modigare när man delar ansvar för korrekthet
    När man vet att någon måste läsa koden skriver man ofta bättre kod
    Man sprider kunskap om vad som händer i projektet till fler

Redovisa i projektrapporten hur denna typ av kodgranskining har fungerat och relatera till den typ som gjordes under tidigare faser, som var mindre disciplinerad och inte rörde er egen kod.

Några saker att fundera på:
    What were the consequences of using code reviews before commiting?
            (Started, down below)
    Was it only extra work or did it serve any purpose?
            (Not started yet)
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



# ROUGH DRAFT, ADD POINTS BELOW THAT SHOULD BE IN REPORT

## What has our process been like.
* We have been reviewing each others codes as pull requests have been announced. This has been done by people asking if someone can review, as well as checks when sitting together and working on the code. This has made it so that any new code has been reviewed before being pushed into the main branch. 


## What consequences were there with reviewing the code
* One of the consequences with reviewing the code before commiting is ...

* One consequence with pull requests and code reviews is that some branches could easily fall behind the main branch. This lead to some people working on older versions, which meant that some implementations had to be changed when the newer code was pushed up. This became an issue when we had to reimplement the release function, which happened at the same time as integration to the main program had started. This meant that most integrations had to be adapted to the old code for a while, and later changed when the adaptation had been fixed.


## How did we review our code
* At the beginning, code reviews weren't that big and we didn't have a set standard how to review. This was later changed, and we had the protocol from the course as a guide to how we reviewed the code. Getting the protocol led to us having a guide that could be used for reviewing, and even if the protocol wasn't fully used, we could still use it as a crutch to fall back on if we didn't know what to look for when reviewing.


## Did GitHub's built in functions help with reviewing the code
* The color diffs on GitHub could help with knowing what had been changed, which helped as we could see what code needed to be reviewed. This helped with knowing what code were to be added to the main branch, which led to knowing what code is relevant to look at for the review. 


## How did we use pull requests, how long were they opened, how many code reviews did we do
* Add text here


## How is this compared to previous reviews in the course
* Compared to the previous code reviews we've done in the course, we've had the same protocol as our backbone for reviewing. 





* TODO: Hur granskas kod, används någon mall när man granskar koden.


# LINK TO GITHUB PULL REQUESTS
https://github.com/IOOPM-UU/Minnesmastarna/pulls