Lab: 1
Graded by: Oscar Granados-Martinez oscar@wustl.edu
Grade: 98/100

-1 Comments:You should not have the same return value for too many, vs too few arguments 

-1 Whenever you have an invalid card file, you keep printing out that it's invalid, which is a
little unecessary, most notably in the case where comments are
together with a card definition (6C 5h 6H 5d 4D// two pairs) but good
job handling every case, including files with no comment lines.

Great job fixing the issues from lab 0

Very good job overall: great commenting, and great code modularity.  

Name: Xinyi,Gong
Lab: 1


========================================================================
    Lab1 : lab1 Project Overview
========================================================================
- This program will open a file by parsing command line arguments, and print out
the sorted playing cards listed in the file. Also, the program will find out the 
rank of a five-cards hand and sort all the hands by a specific way.


####error####
error Expression: invalid operator< 
- error with inconsistent operator definition
Error	1	error C3861: 'sortCards': identifier not found
- should put the function name before the main function where sortCards is called.

####Documentations for error values####
enum return_value {
success = 0, 
argument_error = -1, 
invalid_file_name = -2, 
invalid_card = -3};

enum class Suit{
SUIT_ERROR = 5;
}

enum class Rank{
RANK_ERROR = 15;
}

####Test Cases#####
C:\Users\Administrator\My Documents\Visual Studio 2013\Projects\lab1\Debug\

>lab1.exe  
lab1:You entered an invalid argument
you should enter only one file name follow the name of the executable program

>lab1.exe list.txt 
cannot find the file

>lab1.exe test0.txt
7u is an invalid card
7x is an invalid card
invalid hands
invalid hands
invalid hands
invalid hands
This hand has a no rank
This hand has a no rank
This hand has a one pair
This hand has a one pair
This hand has a two pairs
This hand has a three of a kind
This hand has a full house
This hand has a four of a kind
This hand has a straight flush

Valid cards are
2c
2d
2h
2h
2s
3d
3h
3s
3s
4d
4h
4h
4h
4s
4s
4s
5s
6s
6s
7c
7c
7d
7h
7s
7s
8d
8d
8h
9d
9s
jc
jh
jh
js
qd
qs
kh
ac
ac
ad
ah
ah
ah
as
as

///test.txt
4s 4d 7c 9s qs //one pair
7d    9d 7h 8d 3s //one pair 
9s 2c ac  7u 3s 7x //invalid 
7s 8d 7c 4h 4s//two pairs
js qd kh ah 3d//no rank   
7s 4s 3s 5s 6s 2s//invalid
7s 4s 3s 5s 6s //stright flush
2s 3s 7s 5s 6s 4s 8s//invalid hands
2h 8h 4h 3h 6s //no rank
2h 2s 2c 2d ad //four of a kind
ah jh ac as jc //full house
ah jh 4h as ac //three of a kind 



>lab1.exe test0.txt
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
invalid hands
tk is an invalid card
invalid hands
11s is an invalid card
invalid hands
invalid hands
This hand has a no rank
This hand has a no rank
This hand has a one pair
This hand has a one pair
This hand has a two pairs
This hand has a two pairs
This hand has a three of a kind
This hand has a three of a kind
This hand has a straight
This hand has a straight
This hand has a flush
This hand has a flush
This hand has a full house
This hand has a full house
This hand has a four of a kind
This hand has a four of a kind
This hand has a straight flush


Valid cards are
2d
2h
2h
2s
2s
3c
3c
3d
3d
3h
3h
3s
4c
4c
4d
4d
4d
4h
4s
4s
5h
5s
6c
6h
6s
7d
7h
7h
7s
7s
8c
8c
8d
8h
8h
8h
8s
8s
8s
8s
9c
9d
9d
9h
9s
9s
10c
10c
10d
10d
10d
10h
10h
10s
10s
10s
10s
jc
jd
jd
jh
jh
js
js
qd
qd
qh
qs
kc
kd
kd
kd
kh
ks
ks
ks
ac
ac
ad
ad
ad
ah
ah
as
as

///test0.txt
10d 10s 10c ks kd //full house (higher rank)
3d 3s 3c as ad //full house

6H // not a hand (too few)
Kc 3s 3D 2D 7c 5c  // not a hand (too many)

6c 10s 9H  8s  7H // straight
7s 8c 9d 10s jd //straight (higher rank)

AH Ks Js AD Ac // three of a kind (higher rank)
ks kd kc 2s 5h // three of akind

4s 4H  4D As 4c  // four of a kind
8c 8s 7d 8d 8h // four of a kind (higher rank)

KH   10H 3H 2H 8H // flush
AH 3H 2H JH QH //flush (higher rank)

9c QD 10c 10D 9s // two pairs
2s 2d ac ad 3d //two pairs (higher rank)


4d 4s 8h 10h jh //one pair
qd 7s 4c 4d 10d//one pair (higher rank)


tk 7h jc 6h 9d 8s // no rank 
KD JD 6s 5s 3c // no rank (higher rank)    

9s qs js 8s 10s // straight flush
9s qs js 8s 11s //straight flush (higher rank)

///All the test cases are sorted correctly. 


