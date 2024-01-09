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

## How we implemented the program
The reference counter keeps track of additional information to an allocated object by using structured metadata, which is saved in front of each allocated pointer. The metadata consists of a counter, a size variable, and a pointer to a destructor function. 
The counter is used to keep track of how many live pointers there are to the allocated object. This is managed through an interface where the user will use a retain function whenever creating a new pointer to an object and a release function whenever a pointer to an object is freed or removed. If the counter becomes zero after a release, the object can no longer be referenced from the program and the memory can be returned. In order to avoid cascading frees, the deallocation of objects is handled through a queue and a cascade limit that can be changed by the user. Instead of an object being deallocated when its counter reaches zero, it will be enqueued to the free-queue. At certain points in the reference counter, it will deallocate as many objects from the queue that the cascade limit allows. To make it possible for the user to decide when to deallocate objects, a cleanup was implemented, that, no matter the cascade limit, will empty the queue. As the reference counter adds some additional data structures, a shutdown function has to be run at the end of the program to clean these up. Shutdown will also handle any remaining objects in the free-queue.
The size variable in the metadata keeps track of how big the allocated object is, which is then used to prevent invalid reads when scanning an object for pointers that need to be released when the object is deallocated. The function pointer in the metadata points to a destructor function which is called before an object is deallocated. If the destructor function pointer is null, a default destructor will be run that scans the object for pointers to other objects allocated with the reference counter. If a pointer to an object is found, the pointer will be released, since the reference will be dead once the object is deallocated.



## Size of reference counter;
We made the choice of having the size of the reference counter as an unsigned short to keep the memory overhead relatively small compared to otherwise standard 32-bit and 64-bit unsigned integers, while still allowing a high enough number of allocations to prevent nearly all risk of overflow. Since we haven't implemented garbage collection, we felt that overflow would cause too many errors to be able to use an 8-bit integer or anything smaller instead, despite the loss of memory efficiency. We have, however, determined that there is no risk for a user to exceed 65536 references to one object, aside from deliberate sabotage. For that unlikely scenario, though, we have implemented a countermeasure. When the program tries to retain the reference count beyond its limits, it instead destroys the object of reference. This solution will cause errors if that object is used in any way after this, as it will now be a null-pointer, but it, at the very least, doesn't lead to undefined behavior from overflow.

- How does your system handles (or not) reference counter overflow?
    * Common approaches include either preventing overflow by choosing a larger data type for the reference counter or implementing mechanisms to detect and handle overflow gracefully, such as by triggering garbage collection or other memory management strategies.


## Not delivered features.
* Any feautres we haven't implemented, how could they be implemented/integrated in the future.