MattyG Boy

MattyG Boy is (will be) a very basic emulator for the original Nintendo GameBoy. I'm creating it mostly because I learned the basics of how emulators work somewhat recently and I want to prove to myself that I can do something like this that interests me a lot.

This readme, like this project, is in its infancy and I will add to it as I make headway in the project.

6/20/18

So it's been nearly a month and quite an adventure getting as far as I have. I have implemented all but couple opcodes that are waiting on other dependencies (or for me to feel that I better understand what they do), and have made a lot of progress implementing the virtual memory system. 

It was probably in the past few days as I struck out to implement the virtual memory in a way much more complex than I had originally envisioned (pretty much just a big array that any relevant instruction could directly access) that I have learned the most brand new things. I didn't realize just how much more involved the memory system was than the simple CPU emulator I built for school, clearly they had dumbed down that part in order to focus on the assembly instructions. Part of it is admittdly frustrating (why does this thing that seemed to be so simple have to get so complicated???) but at the same time it becomes fascinating to see how so much was done with so little, like in the case of memory banking.

The biggest lesson I have learned is the benefit of getting a more holistic view of a development project like this before starting to code. The memory refactoring I'm doing now is just the largest of several refactors I've done when something I had envisioned at the start turned out not to work when I started looking into newer information I needed to execute the next part of the project.

My biggest enemy at this point is a struggle to keep making forward progress and only stopping to refactor when absolutely necessary. I want to get it *working* before I worry about making it *great*, but I'm having a hard time finding exactly where that line is between ugly/overly complex but works and too ugly, too overly complex, shouldn't be done this way and I should change it before continuing.

11/8/18

Loooong time since last update and mounting schoolwork and work work have taken my attention away from this project. My issue right now is that the timer and graphics registers don't seem to update appropriately and I don't yet know why. I've been wrestling with that in fits and starts for a while now. At this point I'm reasonably sure that my opcodes are correctly implemented, so the problem has to be somewhere in my memory management system, the new graphics/timers source files, or with my understanding of when and how those registers should be updated. 
