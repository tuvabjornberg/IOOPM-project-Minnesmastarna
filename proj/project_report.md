# Project Report

## Minnesmästarna

### Participant list
|Name               |Email                                  |Active Dates|
|----               |-----                                  |------------|
|Liam Anderberg     |liam.anderberg.7761@student.uu.se      |28/11-2023   --             |    
|Tuva Björnberg     |tuva.bjornberg.5452@student.uu.se      |28/11-2023   --             |
|Hektor Einarsson   |     |28/11-2023   --                  |
|Martin Ek          |martin.ek.7764@student.uu.se           |28/11-2023   --             |
|Tove Frænell       |tove.fraenell.3054@student.uu.se       |28/11-2023   --             |
|Theo Karlsson      |theocarlsson@gmail.com                 |28/11-2023   --             |    

## Quantification
Project start date:  28/11-2023
Project end date:    10/1-2024

Number of sprints, their start and end dates:    
1. 1/12 -  12/12
2. 12/12 - 19/12
3. 19/12 - 2/1
4. 2/1 - 10/1


Total number of new lines of C code written excluding tests and preexisting code: 334
Total number of lines of test code: 413
Total number of lines of “script code” (e.g., make files, Python scripts for generating test data, etc.): 142
Total number of hours worked by the team: 365 h
Total number of git commits: 202
Total number of pull requests: 40
Total number of GitHub issues: 14

## Process
### Inception
#### How we implemented the process
We decided to use the Scrum process. We decided this because it was something that we were familiar with, and had worked with before. The main gist of Scrum is to create sprints to follow, which was something that we planned very early on in the project. We did alter the way Scrum wants us to work, as we didn't have many daily scrums. This was due to us mostly working with the project at different times and different places, but we did let the group know if something major had been done that would affect everyone else.

Our meetings at the end of the sprints were a mix of a sprint review, retrospective, as well as some touches to sprint planning. We would at these meetings go over what had been done in the sprint, and make sure that everyone knew what had happened at that sprint. This was also a time where we decided what the next sprint should focus on, and what each person should tackle in the next sprint.

We made sure to have a few meetings during the sprints, these were happening frequently, and had structural similarities to a daily scrum. They were longer than a daily scrum should be, but the content was similar to what a daily scrum had.

#### Learning the process
Because this was something that we were slightly used to, we didn't have to spend any time learning the process. This made it so that we could focus more on working with the project instead of learning a process. This was also useful as we could implement how we had previously worked in the course as a means to this project, instead of completely separating the work we'd made for the rest of the course.

Something we could have changed with our chosen process was that we could have implemented the daily scrum better. This could have been especially useful in the beginning, as it would have lead to everyone knowing what had been done for each day, and could be more integrated into the project. This was something we lacked in the end, where some didn't really know what they could do, and some had a better understanding of the final product compared to others.


### Implementation
In the current implementation of the reference counter, each allocation results in additional bytes being allocated in front of the bytes requested by the users as metadata. The meta is stored as a struct with a counter, a size variable, and a pointer to a destructor function. In an attempt to make the most of the least amount of bytes, the counter and the size variable are unsigned shorts. The reasoning behind the choice of an unsigned data type is that neither the counter nor the size should ever have a negative value. An unsigned short in C consists of 2 bytes and has a range of  [0, 65,535]. In the current implementation, if an object’s counter reaches the upper limit of the interval, the object is deallocated. The size of a pointer is dependent on whether the program is running on a 32 or 64-bit machine. For the sake of this analysis, we will assume that the program is running on a 64-bit machine which is the more common out of the two, which would mean that the pointer is 8 bytes in size. 
Because the metadata is stored as a struct, there is an additional overhead, which is due to structure padding. Structure padding is when additional bytes are added to memory to make the data word-aligned. For a 64-bit architecture, a word is 64 bits or 8 bytes. In the reference counter, this results in an additional four bytes being added to word-align the metadata, and as a result, the metadata is two words or 16 bytes. 
 
In addition to the metadata for each object, pointers to all allocated objects are added to a linked list to be used in the object scanner function. A link in the linked list consists of a value, which is a pointer, as well as a pointer to the next link. Although these links are structs, no padding is added since each pointer is one word and the struct is naturally word-aligned. Therefore, the allocation of a link struct adds a total of 16 bytes to each allocation. 
 
Although it is not initially allocated, for each allocation made with the reference counter, an entry in a queue will be allocated to keep track of what allocations to deallocate. Because this is a consequence of the reference counter, it should be accounted for in the analysis. Just as the link struct, an entry in the queue is a struct consisting of a value, which is a pointer as well as a pointer to the next pointer, and because this struct holds two word-size pointers it will, like the link, have a size of 16 bytes.
 
The total overhead of each allocation totals 48 bytes, which is a considerable overhead. There are several possible ways to lower the overhead. Depending on which program the reference counter is used with, being able to handle over 65 000 pointers to the same object might seem excessive, and a smaller data type could be chosen over the unsigned short for the counter and size components in the metadata to reduce the number of bytes in memory. However, for a smaller data type to make a difference, structure padding would have to be disabled within the struct or the metadata would have to be allocated piece by piece and not as a part of a struct. The latter was attempted during the project but was replaced by the current implementation due to data alignment and invalid read issues. 

Most of our implementation choices can be read about in the design report.

## Use of Tools

### Tools to the code
We haven't used a lot of different tools in the project. As far as external tools goes, it has mainly been Make. This is due to us learning to use it early in the coruse, which further led to us knowing how it worked and easly being able to compile and run the program we work on. Since we had multiple Makefiles, we had to change quite a few files in order to run different parts of the code. This was noticeable when integration started, as it became more important to run specific parts of the program. This led to us learning how to extend the Makfile further than earlier during the course. 

A lot of internal tools in C has been used as well. Most of these were tools that we have learned about during the course, such as CUnit, gdb, and coverage checking, but also some that not all of us had previously used, such as sanitization. Since all of us were used to using CUnit from earlier in the course, it wasn't a problem to work with and adapt to the project. This meant that we could use those tools to a large extent, and rely on our knowledge that we knew how they worked.

Another tool we used was GitHub. This made it easy for us to work on different parts of the code, and share it with each other. We used multiple different branches to make sure when something was pushed, it was working code, and if a pull request took time, you could still push up code to another branch if it didn't work and you had to create an issue log.


### Any tools outside the code
We used Trello as a means of making sure we had a structured plan. This kept us updated on what needed to be done, as well as who was woring on a specific part of the project. This made it easy to know who had made what part of the code, which was useful if you had a question regarding certain parts of the code. This was also a great way to see how much each person did, as the cards were claimed according to what part of the project one did.

We also created a Google Drive folder to keep our work organized. This included a folder where we had our meeting protocols, as well as some basic files that could be necessary for the project. It wa a place where we had the instructions close by, and could go back to see what was supposed to be done for each sprint. As we also had the folder with meeting protocols, we could see what we wanted to discuss for each of them, and go back to see what had previously been said. This also meant that if you missed a meeting for some reason, you could go back to see what had been discussed and what the next steps for the project that had been discussed.

The main communication tool that we used was Discord. We established early that we needed some form of communication online, as this would make it easier to work together when some of us couldn't make it to a physical meeting. It was also an easy way for people to ask the rest of the team what they could do, or if they needed help. We also updated each other there if someone were to merge an important part of the code that could change how the rest of the code worked or if someone had solved a bug that bothered many.

We also did a few meetings over Zoom. This happened during the holidays, where it was difficult for some of us to make it to a physical meeting. As most of us was familiar with Zoom before, this was a tool we knew were good for meetings, and it held a much better environment for distance meetings compared to Discord voice channels.


### Did we lack/dislike any tools
One thing that we would change if we redid the project was that we'd use GitHub in a better way from the start. Since most of us were new to this, we didn't fully use GitHub to it's fullest potential at the start. Had we known this, we could have spent less time learning how to efficiently use it, and instead focused our time to make sure we had finished everything earlier.

Another tool that could have been slightly better for us was Valgrind. There were times where some code wouldn't run through tests normally but it worked through Valgrind, and vice versa. This was especially annoying when working on the finishing stages, when we were trying to make sure that all the code properly worked. But although this was a struggle, it was still a very useful resource for us as we could see both if and where the program was leaking memory. 


## Communication, Cooperation and Coordination

### How did we communicate
Most of the communication between team members was online. We decided early to create a Discord server here we could ask questions and have our main communication. This was mainly as an easy way to reach all team members, and make sure that everyone was on the same page when it came to the code. At the beginning, we also tried to frequently have meetings in person, to make sure that everyone was up to date on where we were in the code. These became more sparse and over zoom as the holidays came around, and we were spread out all over the world. These were also a bit further apart, as it was harder to coordinate, and we wanted to be able to work whenever we had time on our own.

The communication between the coach and the team was through emails between the project leader and the coach. There has been minimal contact, but a resource which we could lean back on if we needed it. During contact between the coach and project leader, the response time was quick, and we got the help we needed fairly early on during the process. We didn't really need the coach regarding the code or for any conflicts, but it felt good to have someone to turn to if we needed it. In total, we had two group meetings with the coach, where we discussed partially how it was going, but also the problems we had stumbled upon at time of our meeting, and we wouldn't necessarily change anything about our communication with the coach if we could.


### Cooperation between team members
A lot of cooperation between the team members were through helping each other when someone got stuck. This happened mostly if someone asked for help from the rest of the group, but also when people waited for code to continue, and decided to check what was happening that took time. When working on the same modules of the program, we relied on people sharing their findings with the rest of the group and commits as soon as changes had been made. This become more prevalent during the integration part of the project, as certain modules were dependant on others and a lot of people would work on solving the same issues. 

The cooperation between team members also became proficient when there was a large task which was crucial for the program to work as intended. This could be seen when we worked on the destructors, as two people worked on them together, while the rest tried to go forward as much as they could so we didn't get stuck on any one part of the code.

While some people worked together and some opted to work by themselves, it remained important to us that everyone updated the group if there was something that they did which could be important to the rest. If there were some decisions that had to be made while in a cooperative phase, these were partly made by the contributors, but if it affected everyone, the choice was discussed and made together.


### Demotivated/angry team members
There were no structural way for us to deal with demotivated or stressed members. We all knew that there we were going to have an exam a few days prior, and that some might want to put less time to work on the project at this time. Since a lot could come up that led to not being able to do what you had planned initially, we made sure that if some parts started falling behind, someone else could take a better look at that part, and the person who originally was supposed to work on it did something else when they had time.


### How did it go during the holidays
During the break, we knew that some people maybe had more plans than others, but we decided to divide the work as evenly as we could. This was so that everyone had their own part to work with. At this time, we also made sure to update the discord if we needed help, or if someone could check out a pull request that had been made. This made it so that event though some wanted to spend time with family or focus on our other course, there was still something that could be done. We also made sure to have one meeting where we checked how the work was going, and what we had left. This was also where we decided mainly who should work mainly on each report, as they could be done if someone were to travel for a longer time, or had some spare time to write as their part of the integration was done.


### Lessons learned
A big lesson that we had to learn was how to work in a bigger group. Since we previously had worked in either pairs or smaller group, it was a challenge for us to work with more people, and because of this, communication became especially important. This was also a bigger challenge in the beginning, where we had to see how far each person had come with the rest of the course. It was hard to synchronize with the rest of the group at this time, because some were finishing up the rest of the course while others still had a lot left to work on.

The problems with synchronization also lead to the work being unevenly divided at the beginning. Those who still had other parts of the course left were splitting their efforts between the project and the Z-goals, while those who were basically fininshed could put all their effort into the project much easier. During this time as well, we amde sure to have frequent meetings, to make sure that everyone was up-to-date with the project, even though they didn't want to put their full effort into it just yet.

Time management also became a problem, and something that we had to work with. Since we mainly met the rest of the group during scheduled meetings, most of the coding happened at time we had scheduled ourselves. This meant that some could be working earlier in the day, while others worked more at night. This meant that if you needed help, sometimes there were no other people who had time to do so. This became harder during the break, as people also wanted to spend time with family, and had to plan their work for when they had time. Something that we could have done was plan for more time where we solely worked on the project at the same place beforehand, when we knew that mostly everyone could come and work together.

## Work Breakdown Structure

### Sprints
We decided at the start to split the work up into four sprints, where the first one started at the beginning of the project, and the last one ending when we hand in the project. Since we didn't know which day was our last at the beginning of the project, we placed the final sprint to end the 8th. Our plan also meant that we had two sprints before christmas, which were bigger, and then two smaller sprints during the break.

The first two sprints were mainly to focus on the refmem file. Our first one was to hopefully have a working refmem file, with the functions that we were going to use later working. This meant that these sprints were code-heavy, and a lot of work here was for anyone to grab and work on. Our timeline did get skewed here, as we decided to end the first sprint a few days later than the initial sprint had planned.

Our second sprint mainly focused on making the destructors work, but this was also where we started our implementation. The goal of the sprint was to have the integration done for example use. We came across a few problems during this sprint, where we had to start reworking our implementation of the code we had written in the previous sprint. This sprint was worked through on time, as most of this work could be done in parallel, with some of us starting on the third sprint before we finished the second one.

The third sprint was where almost all of the integration was supposed to happen. this was also the sprint we decided to have over the holidays. We made that decision, as the implementation could be done by multiple people, with each one of us choosing a file and working on it. As some of the code was dependant on other parts of the implementation to work, those parts were prioritised. This was planned to be one of our longer sprints, as there was quite a few files in the integration, but also as we didn't want to start up a new sprint during the break. It also merged well into the last sprint.

Our last sprint consisted of writing all of the documentation reports, as well as finalizing the project. We started this before the third one had ended, as we could divide the reports between everyone, so that each person had something to work on. This was also a sprint where the plan was loose. At this stage, almost everyone was working on the same files, to make sure that the code worked for everyone. At this time, people were also working on different reports, which meant that communication and cooperation between this sprint became extremely crucial to make sure evryone knew what was going on.


### How did we program
Most of the programming was made individually. This was due to timing, with people wanting to work at the project at different times. This was also the main way we worked during the integration part of the project, as the integration had us split up over different files. At times, when there were complicated tasks, or when many people waited on the same code, there became instances of pair programming or group programming. This was so that if someone had gotten stuck and couldn't figure out the solution, someone else could look at the code and hopefully help out with moving the project forward.

The work was divided by who had things to do. At the beginning, the code was mainly divided by who had the time to do it, and who was the first to claim that they would do it. Later on, the divide became more structural, and we tried to make sure that everyone had something to work at and knew what their next step would be. If someone didn't know what they should do, there was most likely someone who they could help out, or they could start with the next step of the project.


### Workload, load-balance
We checked quite early into the project when people wanted to put mort of their effort into the project. Because some wanted to have more time over the holidays for our other course, they took a heavier workload at the beginning of the projects, whereas those who took a lighter load at the beginning did more work later on. This meant that the people who did less at the start took on a bigger role in the implementation stage.

A lot of the finishing touches, such as making the code work and working on the reports were equally distributed between everyone. We had initially divided the reports so that people could work on them simultaneously just as the code was divided in the beginning of the project, but since they became one of the last things we did, part of the reports were redistributed, but in smaller parts so that everyone was working on it together at the end.

The load balance was also split depending on what task each person was working on. A few tasks were much heavier, where more effort was needed, while some were much lighter. This meant that those with heavy tasks often stayed there for a longer time, while those with easier tasks could make sure that the smaller parts were working, and get ahead so that it would be easier to work in the future. Those with the easier tasks also became the people who took on the bigger files of the implementation, while those who worked on a heavier task in the beginning took lighter tasks at this time.

There was some problems with estimating how much time each part would take. We made a small estimation at the beginning of the program when we created our sprints. This mainly consisted of how much time we thought each part of the process would take. The problem arose when we realised that some parts of our written code didn't work as intended, and needed to be reworked. At the same time, the work that we were supposed to work on became a slight problem as well. This led to us needing to put more effort into making sure we fixed the code, but at the same time not falling behind in our initial schedule. This didn't work as we wanted though, as we had planned to finish our implementation around the first days of the new year, but it was something that we had to constantly work on until a few days before presenting.

### Burndown Chart
We have created a burndown chart to show how our work went. This had two curves, one where out initial plan is shown, and a second one which shows our actualy work progress. It shows us that our progress started off strong, and we were under the planned curve for a while. This did change quite early, as we had some bigger parts to finish later that took longer time than expected. Our burndown chart can be found in a png-file in the same folder as the project report.


## Reflection
### Are we confident with our product
We feel fairly confident that we had implemented the right thing. Our feelings for this is because we have created a working program that could be implemented to a Z92, and it worked as we wanted it to. There were some things that, because of our implementation, kind of skipped over. One of these happened with how we handled strdup, where we created a function to duplicate the string, instead of purely reference counting, which would have been the dream.

## Rating 1-7
Our satisfaction with our process comes in to about a five. This was something that we didn't really think much about, but we feel as if we worked hard on the project, and did manage to finish the work. 

Our satisfaction with the delivered project is also about a five. We're happy with what we had created, and it's working as intended, but this number is not higher due to us not having time. The time for the project was very limited, and if we had more time, we would most likely be happier with our delivered product.

One thing we are more satisfied with is the quality of the code. A main part was that we tried to make sure that good code went into the main branch, and this happened through detailed code reviews with pull requests. Since we wanted to make sure that the code had good quality from the beginning, this was also something that we spent a lot of time doing, and making sure that it held up to the code that already had been pushed into main.

### Biggest wins and fails as a team
One of our big wins is that we have a working project. Even though it might seem like a very small thing, and something we had working from the start, we also had to spend a lot of time making sure that there were no memory leakage, and that the code we had could be ran without problems. A later win was that we got the txt file to work as intended, as it had trouble working for some people and would give off an infinite loop instead of running smoothly through the program.

We don't think that there were any big fails as a team. There were a few small problems, as there always is, but no big ones that could critically damage our work or team.
