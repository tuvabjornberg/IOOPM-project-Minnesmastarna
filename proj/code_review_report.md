# Code Review Report
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


After a couple of weeks the procedure of reviewing without a protocol was adjusted to have more structured reviews and to better keep track of our work. We started using the code review protocol from the course (used for the P-achievements) as a baseline guide. We did not use the protocol as a rule to follow, more as a guide to get started and to give examples on what to look a bit extra on. We could use it as a crutch to fall back on if we didn't know what to look for when reviewing.


This process helped the entire team to work in somewhat the same manner regarding pull requests. Since we set up guidelines for everyone to follow there were rarely any confusion regarding the entire process and make it more effective in order to spend more time on writing new code.


We didn't push many pull requests back. If this was the case, the author at hand was informed of this and knew what they had to change for the pull request to go through with the help of GitHub's different toools. Out of all our pull requests, this happened to about 4-5, and these problems were solved fairly quickly. Most often the problem were code standard issues. The pull requests that were closed wothout merging most often a result of another persons branch working or were crested just as a means to exchange ideas. We had made a total of 40 pull requests for this project. They were not open for long and an average length of an open request was less than a day. There were some that took time, but we also communicated to the rest of the team when there was something to be reviewed.


## Consequences of code reviews in GitHub
The beneficial consequences of using pull requests were the guarantee that the code was agreed between at least two people before given to the rest of the group, the author and the reviewer. During these code reviews both small errors and more concerning problems arose which were solved to a certain degree before being pushed into main.


We had more clear milestones when code was pushed into main because for important implementations we urged each other to update their current working branch to continue working on something we know works.


Though, this consequence did have its own drawbacks for certain implementations. In most cases it would be because we have started working on an implementation assuming another worked as imagined. Some branches could easily fall behind the main branch. This led to some people working on older versions, which meant that some implementations had to be changed when the newer code was pushed up.


This became an issue in cases where a review took time. For example, when we had to reimplement the release function most of the implementation for the Z92 program was done. But because this type of review was extensive, it took time before the affected members could have access to the updated code. Through the extensive review definitely was necessary.


Using pull requests did serve a good purpose. It made sure at least two people were on the same page about changes to the code. Easy mistakes were caught and formatting of the code could quickly be fixed. It was more work compared to how we have been working previously in the course, with the assignments, where in most cases reviews weren't made to this extent. In a group project with six people we have found it easier to use this system to avoid confusion and broken code, when used correctly. What is similar with the code reviews from the assignment is the use of a code review protocol. Though we have not used it to the same extent for this project, it has served a good purpose.


## GitHub tools

The color difference on GitHub helped to distinguish old and new code. If a change were made to existing code the reviewer could see what changes were made, instead of manually trying to see what was removed or not by comparing the old with the new file. The color difference also helped to narrow down to only new code. It helped the reviewer only see relevant code. Furthermore, if the new code needed to be put into a context the reviewer simply could extend the file to see code already existing in the main branch.


Reviewing pull requests, solving merge conflicts and suggesting improvements were made easier because the interface is simple and straightforward.


## Redos and future use
If the project were to restart there are parts we would have done differently in means of using pull requests and reviewing the code.


The first improvement would be that the author would write a more detailed description of what has been done and comment on any special design choices or parts. This would help the reviewer understand the code faster and better instead of using energy to understand what has been changed. Changes that seem obvious to the author might not be to someone else, even though we all work on the same project and use the same code standards. With this change we could spend less time trying to understand what and why something has been changed and more time on why it works and what improvements could be made.


Another improvement we would do is to have more organized branches. For this project most of the team were new to making branches and using pull requests which led to a steep learning curve and everyone managing what was easier for them to understand. Our repository has quite a lot of branches and the commits and merges we feel are a bit messy. Though we have achieved the goal we feel like it could have been done in a more clean way. Now that the team has more experience with branches and pull requests we would do a better job at managing the repository.


There are plenty of parts we will keep and one of the most important ones would be our guidelines. We feel that because we all discussed how we together should manage the reviews everyone has had something to fall back on when in doubt. The process of communication when pull requests needs to be reviewed and the review protocol helps give structure.


Another part we would keep if we were to restart the project is the dynamic of changing reviewers. This helped the entire team to stay in the loop of what is going on and not just have two people circle around the code. It helped us get a new perspective for each implementation because each individual views the code in a different way. It also helped not to get stuck on a single implementation.


# Link to GitHub pull requests
https://github.com/IOOPM-UU/Minnesmastarna/pulls
