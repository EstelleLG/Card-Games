Lab number: Lab 2
Graded by: Ruth Miller ruth.miller@seas.wustl.edu
Score: 105/ 100 (100 + 5 Extra Credit)
Comments:

Nice Job!!!

========================================================================================================Name: Xinyi,Gong
Lab: 2

========================================================================
    Lab2 : lab2 Project Overview
========================================================================
- This program will create a deck of card by parsing a file that contains the playing cards.
- Users can shuffle the card by parsing a "-shuffle" argument.
- The program will deal the card from the deck to five hands, and determine their ranks.
- The program will sort these hands according to a lexical ordering, and also by their ranks.
 

####error####
error Expression: invalid operator< 
- error with inconsistent operator definition

error: cannot open source file "stdafx.h"
- I accidentally deleted stdafx.h.

####Documentations for error values####
enum command_line_return { 
no_argument = 1, 
one_argument_shuffle, 
two_invalid_arguments, 
more_than_two_arguments};

enum return_value {invalid_file_name = -22, 
invalid_card = -3, 
not_enough_cards};

####Test Cases#####

**no argument
C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
Enter the filename after the name of this program.
Add an optional '-shuffle' argument to perform shuffle.
lab2: No command line arguments are given.

**one argument 
C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
-shuffle
Enter the filename after the name of this program.
Add an optional '-shuffle' argument to perform shuffle.
lab2: Please enter the filename.


C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
test0.txt
Enter the filename after the name of this program.
Add an optional '-shuffle' argument to perform shuffle.
lab2: Can not open the file.
//test0.txt doesn't not exist 



C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
test.txt
tk is an invalid card
asdglaskdj is an invalid card
pd is an invalid card
2p is an invalid card
Hand 0
2d 4d 10h qc qs
Hand 1
4c 5c 9s qh ad
Hand 2
6d 7s 8s qd kh
Hand 3
6c 9d js qd kh
Hand 4
4d 6h jh kc ah
Hand 5
4s 9h 10h jc as
Hand 6
7h 8h 10h 10s ad
Hand 7
2c 4s 5h 6h 8s
Hand 8
2s 4d 8d 10d js

the rest of the deck has
8d
9s
10c
10s
js
9s

after sorting the hands based on the < operator
2c 4s 5h 6h 8s
no rank
2d 4d 10h qc qs
one pair
2s 4d 8d 10d js
no rank
4c 5c 9s qh ad
no rank
4d 6h jh kc ah
no rank
4s 9h 10h jc as
no rank
6c 9d js qd kh
no rank
6d 7s 8s qd kh
no rank
7h 8h 10h 10s ad
one pair

after sorting the hands based on the rank
2c 4s 5h 6h 8s
no rank
2s 4d 8d 10d js
no rank
6c 9d js qd kh
no rank
6d 7s 8s qd kh
no rank
4c 5c 9s qh ad
no rank
4d 6h jh kc ah
no rank
4s 9h 10h jc as
no rank
7h 8h 10h 10s ad
one pair
2d 4d 10h qc qs
one pair

//Cards are sorted correctly.

** two arguments
C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
test.txt test.txt
Enter the filename after the name of this program.
Add an optional '-shuffle' argument to perform shuffle.
lab2: You have entered two filenames.


C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
-shuffle -shuffle
Enter the filename after the name of this program.
Add an optional '-shuffle' argument to perform shuffle.
lab2: You have entered two -shuffle arguments.


C:\Users\Administrator\My Documents\visual studio 2013\Projects\lab2\Debug>lab2
-shuffle test.txt
tk is an invalid card
asdglaskdj is an invalid card
pd is an invalid card
2p is an invalid card
Hand 0
6h jc js kh ad
Hand 1
5c 7s 9s 10h 10s
Hand 2
8h 9h 10c qh kh
Hand 3
4s 7h 10h 10h as
Hand 4
4c 4d qc qd ah
Hand 5
9d 10s jh js kc
Hand 6
2d 4d 4d 8s qs
Hand 7
5h 6h 8d 8d 9s
Hand 8
4s 6c 9s 10d js

the rest of the deck has
ad
6d
qd
2s
8s
2c

after sorting the hands based on the < operator
2d 4d 4d 8s qs
one pair
4c 4d qc qd ah
two pairs
4s 6c 9s 10d js
no rank
4s 7h 10h 10h as
one pair
5c 7s 9s 10h 10s
one pair
5h 6h 8d 8d 9s
one pair
6h jc js kh ad
one pair
8h 9h 10c qh kh
no rank
9d 10s jh js kc
one pair

after sorting the hands based on the rank
4s 6c 9s 10d js
no rank
8h 9h 10c qh kh
no rank
2d 4d 4d 8s qs
one pair
5h 6h 8d 8d 9s
one pair
5c 7s 9s 10h 10s
one pair
4s 7h 10h 10h as
one pair
9d 10s jh js kc
one pair
6h jc js kh ad
one pair
4c 4d qc qd ah
two pairs

//Cards have been shuffled, and sorted correctly.


*******Extra Credit*******
A.8 The program will catch the exception thrown by the load method and then propagated up to the main function in deck.cpp. 
A.9 The exception is thrown only when the file cannot be opened.
A.12 Does not apply. I didn't use pointer whose value is 0.
A.13+14  The program doesn't use pointers. 
		The program uses vector index to access each card in a five-cards hand. Since the dealing method makes sure that every hand has five cards, 
		we are sure that the vector index does point to something. 
A.15 The program always uses the vector to store values. 
A.16 debugging: Usually I try to use cout to test how far did the program go. And also by comment some codes out I can determine which sentence cause the problems. 
	Usually the debugger of visual studio helps a lot, since the program will usually break near the bug. 
B.10 Yes, they are in the same order. 
	And the class initialization is before other member initializations. 
B.11 Does not apply. Since in this lab, we are told to construct a deck in a specific way.
B.12 Exception are thrown can caught by the main function.
B.18 We need a copy constructor so the program keeps it public. 
B.31 All the header files include #ifndef FOO_H   #define FOO_H and #endif /* FOO_H */
