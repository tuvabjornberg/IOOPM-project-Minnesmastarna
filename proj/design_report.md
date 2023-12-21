# Design Report
Describe the design of the system at a high level. The purpose of this document is to serve as a starting point for someone that wants to understand the implementation. You must also describe all deviations from the full specification. For every feature X that you do not deliver, explain why you do not deliver it, how the feature could be integrated in the future in your system, and sketch the high-level design.

Ni skall ha en beskrivning av programdesignen som
    översiktligt beskriver de centrala funktionerna i programmet
    översiktligt beskriver programmets arbetsgång ("algoritm")
    beskriver alla centrala datastrukturer som programmet använder
    beskriver hur programmets funktion delats upp i olika moduler

Använd gärna bilder som del av beskrivningarna!

Together with the actual code, this file will be used by the examiner to convince him/herself that you pass Y68.



# ROUGH DRAFT, ADD POINTS BELOW THAT SHOULD BE IN REPORT

## How have e implemented the program

* Add text here.


## Size of reference counter;
We made the choice of having the size of the reference counter as an unsigned short to keep the memory overhead relatively small compared to otherwise standard 32-bit and 64-bit unsigned integers, while still allowing a high enough number of allocations to prevent nearly all risk of overflow. Since we haven't implemented garbage collection, we felt that overflow would cause too many errors to be able to use an 8-bit integer or anything smaller instead, despite the loss of memory efficiency. We have, however, determined that there is no risk for a user to exceed 65536 references to one object, aside from deliberate sabotage. For that unlikely scenario, though, we have implemented a countermeasure. When the program tries to retain the reference count beyond its limits, it instead destroys the object of reference. This solution will cause errors if that object is used in any way after this, as it will now be a null-pointer, but it, at the very least, doesn't lead to undefined behavior from overflow.

- How does your system handles (or not) reference counter overflow?
    * Common approaches include either preventing overflow by choosing a larger data type for the reference counter or implementing mechanisms to detect and handle overflow gracefully, such as by triggering garbage collection or other memory management strategies.


## Design decisions
* Add any design decisions made here


## Not delivered features.
* Any feautres we haven't implemented, how could they be implemented/integrated in the future.