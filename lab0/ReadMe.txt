Lab number: 0
Graded by: Joseph Kwon
Score: 93 / 100
Comments:
-3: don't hardcode numbers, use an enum or const int
-3: seven heart instead of 7h (the latter is a valid card definition string)
-1: don't hardcode program name in usage message
-0: remember to catch any possible errors

Search for //JK to see my comments in your files

--------------------------------------------

Name: Xinyi,Gong
Lab: 0


========================================================================
    CONSOLE APPLICATION : lab00 Project Overview
========================================================================
- This program will open a file by parsing command line arguments, and print out what was read, 
which in this lab, are playing cards.

/////////error/////////// 
error LNK1120:1 unresolved externals
error LNK2011: precompiled object not linked in; image may not run

////////Documentations for error values/////////
invalid_file_name = 1;
invalidArgument(more than one argument or no argument) = -2;

////////Test Cases//////////
C:\Users\Administrator\My Documents\Visual Studio 2013\Projects\lab00\Debug\

>lab00.exe  
ConsoleApplication:You entered an invalid argument
you should enter only one file name follow the name of the executable program

>lab00.exe list.txt cse332.txt
ConsoleApplication:You entered an invalid argument
you should enter only one file name follow the name of the executable program

>lab00.exe list.txt
asdf is an invalid card
sd7 is an invalid card
xc is an invalid card
s9 is an invalid card
1s is an invalid card

Valid cards are 
eight Heart
seven Diamond
ace Spade
four Heart
eight Spade

here is a copy of list.txt - 
asdf 8h sd7 xc s9 d7 7d 1s as

7hh 4h 009&s 






8s
- The output is correct.

>lab00.exe cse332.txt
cannot find the file 

>echo %errorlevel%
1 - which means an invalid file name

>lab00.exe list.txt
10r is an invalid card
12s is an invalid card
12p is an invalid card

Valid cards are
ten Spade
jack Spade
ace Spade
jack Heart
queen Diamond

here is a copy of list.txt - 
10s 10r js As jH QD

12s 12p 
- The output is correct.



