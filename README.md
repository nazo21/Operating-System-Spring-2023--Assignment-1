# Operating-System-Spring-2023--Assignment-1
My code for the Assignments
Readme.pdf(Contains the Printed Results)

Comments:
The producer seems to working in order, however the consumer isn't consumming anything. It may be due to the fact is it waiting constantly or simply the output isn't being printed out correctly. 
I put the main and producer and consumer all in one cpp and it does what it supposed to do two produce and two consume. Maybe when it is put into two executables is where the issue arises

I figure out the problem, I may not be implementing the function correctly and not utitlizing shared memory properly, since there needs to be communication such as producer must go first produce then consumer consumes but maybe either the consumer is stuck on waiting since only the producer seems to be working as it did produces 2 items. I should modify it and include more threads

I have to implement shared memory properly with producer and consumer along with using threads. It may be better to do that in the main function instead of just separating functions into two but take away from the producer function to just creating items and do all the conditions in main function. Same thing with consumer. I know the header file is correct the void functions if put to one do their job(only two are produced and 2 consumed) maybe I should modify the way I am doing it and rely more on the main funct for conditions

Overview:
We have a Producer-Consumer Problem where the table can only hold two items at a time before the consumer takes an item then the producer can produce another item into the table for a total of 6 times. We will use shared data in the header file to define where the semaphores and p_threads mutex function
Since the prompt specified two executables or two process we will separate the functions into two and use pthreads to run them at the same time. 




Conclusion/Problems:

Problem 1: Consumer function isn't working
Problem 2: I am not implementing Shared Memory properly
Problem 3: I want more produce but as more is produced then consumer has to keep up


My Takeaway: 

If everything is in one file then the program is straight forward but when it is in two executables there are problems of different instances and that is the role of shared memory to make these two process run concurrently and effectively using the shared data. 
