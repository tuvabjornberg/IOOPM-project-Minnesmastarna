# Design Report
Describe the design of the system at a high level. The purpose of this document is to serve as a starting point for someone that wants to understand the implementation. You must also describe all deviations from the full specification. For every feature X that you do not deliver, explain why you do not deliver it, how the feature could be integrated in the future in your system, and sketch the high-level design.

Ni skall ha en beskrivning av programdesignen som 
    översiktligt beskriver de centrala funktionerna i programmet
    översiktligt beskriver programmets arbetsgång ("algoritm")
    beskriver alla centrala datastrukturer som programmet använder
    beskriver hur programmets funktion delats upp i olika moduler

Använd gärna bilder som del av beskrivningarna!

Together with the actual code, this file will be used by the examiner to convince him/herself that you pass Y68.



## Size of reference counter - TODO: 
We made the choice of having the size of the reference counter as an 8 bit integer to keep the memory overhead small compared to other data types. This is beneficial for this system as memory efficiency is one of the main goals of this project, as using smaller data types for the reference counter reduces the overall memory usage. 

A valid concern is the fact that we can only represent 255 reference counts to each object.

- How does your system handles (or not) reference counter overflow? 
    * Common approaches include either preventing overflow by choosing a larger data type for the reference counter or implementing mechanisms to detect and handle overflow gracefully, such as by triggering garbage collection or other memory management strategies.

