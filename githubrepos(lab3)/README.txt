
files "assignment3.h", "main.c" and "makefile" were given.


This was given out as an assignment in the class "Principles of Programming", it was handed out as a sort of
"baptism by fire" when it comes to data structures since we had only really explored arrays previously. I had
no experience beforehand creating linked lists in any language and the information was only taught within
the two weeks during the assignment period.

It was a challenging assignment as it encouraged us to get out of our comfort zone and start to rely on
recursive function calls to complete the structures.

____________________________________________________________________________________________________________

Hello! this folder contains a makefile, a header file and a main file all essential to run
the linked list program.

To compile and create an executable, browse to this folder on your terminal and type:
	
	:$ make

this will create the executable from the .c file that depends on the main file and header to
define the structures used.

If you need to clean the directory of the object files and the executable, simply type:
	
	:$ make clean

To run the program within the working directory:
	
	:$ ./list

___________________________________________________________________________________________________________

DESCRIPTION:

The .c files in this directory define a singly linked list structure, the nodes of one being the parent of
another singly linked list structure.

There is an HB list, of which its nodes are defined with a integer "key" and two pointers; one pointer
linking the next node in the HB list (named next) and another pointer linking to the first node in another
singly linked list (named bottom).

the child linked list of an HB node is known as an SL node with a similar integer "key" and this time one
pointer to the next node in this SL list.

the structure ends up looking like this for a n=5, m=5 list(when printed):
(We are allowed to create arrays to help insert keys into the different nodes in the structure. I used two,
one for the double pointer HB nodes and one for the SL list children which added the previous HB node key
for better randomization.)

2  ->  4 6 12
5  ->  17 19 25 29
13 ->  14 19 20 29 35
16 -> 
25 -> 35 39 55

The program then flattens the list using recursive function calls. (The challenge is to do this WITHOUT
creating any arrays to simply dump and insert into the new SL list).

This is done by pivoting on the first HB node (in this case 2) or a node with a key that is guaranteed to be
smaller than any other key in the list (like -1). The program then determines where the HB node would fit
into the new SL using if/if else statements. It then calls a function to check and make sure the SL list
linked to that HB node is not empty (with a statement to move to the next SL node when returned), takes the
child node and determines where it fits in to the new SL list using the same if/if else structure. The 
functions continuously return the pointer to the new SL list to the front (our pivot).

In total, it requires 4 functions to completely flatten the list into an SL list. This can also be done
using while and for loops. There is also a method of flattening the list using a merge function.
	if you were to put all vertical lists of the HB nodes into a sorted SL list, you can merge the
	keys from the HB list into the final SL list.

This would then look like this:

2 4 5 6 12 13 14 16 17 19 19 20 25 25 29 29 35 35 39 55

The program then prints bot the larger HB list and the SL list using recursion. The lists are then freed
before the program is terminated.
	to print the HB list, I made use of a function that prints the HB node and then calls the print
	SL list function to print the children nodes in the linked SL list. The same method is used to
	free these functions! This means I did not have to make even more functions to complete essentially
	the same task.


____________________________________________________________________________________________________________

IMPLEMENTATION:

This program does do the task it set out to complete. It successfully creates an HB list and flattens it; the
print and free functions all work properly.

Valgrind shows that my program does not leak any memory during allocation and freeing of nodes.
	However, it does complain if one of the singly linked lists linked to an HB node is empty.
	I have not been able to completely fix this.
	Otherwise, with any other cases the program does not incite any complaint.

I have completed this assignment in 168 lines of code, This could be considered a little lengthy and if 
I were to work on something similar to this in the future, it would be in my best interest to shorten the
code from finding other methods to complete certain actions.
	for example, I can randomize keys based on previous keys to ensure they are sorted, instead of using 
	a sort function for two arrays.
	My flatten list could very much be shortened if I had only been merging two lists together instead of
	one-by-one searching and inserting each node into the list.


OUTPUT OF Valgrind:

==17== Memcheck, a memory error detector
==17== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==17== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==17== Command: ./list
==17==
==17== error calling PR_SET_PTRACER, vgdb might block
HB list
13 -> 34
29 -> 41 70 94 106 113
65 -> 87
71 -> 116 137
74 -> 111 130

SL list
13 29 34 41 65 70 71 74 87 94 106 111 113 116 130 137

==17==
==17== HEAP SUMMARY:
==17==     in use at exit: 0 bytes in 0 blocks
==17==   total heap usage: 34 allocs, 34 frees, 4,664 bytes allocated
==17==
==17== All heap blocks were freed -- no leaks are possible
==17==
==17== For counts of detected and suppressed errors, rerun with: -v
==17== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

OUTPUT OF cloc:


       1 text file.
       1 unique file.
       0 files ignored.

github.com/AlDanial/cloc v 1.74  T=0.07 s (15.2 files/s, 3835.4 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C                                1             45             39            168
-------------------------------------------------------------------------------
