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

We have the standard Producer-Consumer, then we needed implemented Semaphores in order with wait and signal and empty and full to satisfy mutual exclusion then we will use mutex to have one function lock the process then once the job has been done it will unlock the process and signal the job has been completed

The main functions intializes the values and then the threads are created for prod and cons then wait unti the threads are finish then the variables are destroyed with sem_destroy for memory usage.



Conclusion/Problems:

Problem 1: Consumer function isn't working
Problem 2: I am not implementing Shared Memory properly
Problem 3: I want more produce but as more is produced then consumer has to keep up

Solutions:

Use a while function or specify how many threads should be created in total

Maybe adding the shared memory to it would make it better, I didn't implemented it properly because what would occur is the consumer would constantly wait if the table is full but it never is because it is in a different instance than producer. 

Update:
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

int main() {
    const char* name = "/Prodcons"; // the name of the shared memory object
    const int SIZE = 4096; // the size of the shared memory object
    const char* message = "Hello, world!"; // the message to be written to the shared memory object

    // Create the shared memory object
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        std::cerr << "shm_open failed" << std::endl;
        return 1;
    }

    // Resize the shared memory object
    if (ftruncate(fd, SIZE) == -1) {
        std::cerr << "ftruncate failed" << std::endl;
        return 1;
    }

    // Map the shared memory object into the process's address space
    char* addr = (char*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        std::cerr << "mmap failed" << std::endl;
        return 1;
    }

    // Write the message to the shared memory object
    std::strcpy(addr, message);

    // Unmap the shared memory object
    if (munmap(addr, SIZE) == -1) {
        std::cerr << "munmap failed" << std::endl;
        return 1;
    }

    // Close the shared memory object
    if (close(fd) == -1) {
        std
      
      shm_unlink(shmpath);

}

I figure out what the implementation is, We use the following code above to make sure the other process is in communication then insert our consumer code in between the first part and before unlike. Then modfy the functions to adapt to the style. Most likely, we need to re-evalue our header file and main function

My Takeaway: 

If everything is in one file then the program is straight forward but when it is in two executables there are problems of different instances and that is the role of shared memory to make these two process run concurrently and effectively using the shared data. 
