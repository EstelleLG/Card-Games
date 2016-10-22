Lab number: Lab 3
Graded by: Ruth Miller ruth.miller@seas.wustl.edu
Score: 99 / 100 (94 + 5 Extra Credit)
Comments:


-3 Card rank and suit are hardcoded in the switch statement.  

-3 Hardcoded constants was noted in last 2 previous labs (in multiple group member's lab 1 and 2), 
   but it is still not addressed. 

=============================================================================================================================

Name: Xinyi Gong, Kunyao Liu, Yuan Gao

Lab: 3



========================================================================

    Lab3 : lab3 Project Overview

========================================================================

- This program will create a FiveCardDraw game.

- Players can join and leave the game by entering FiveCardDraw and their names.

- Each player will have one .txt file containing his game record. (#win and #loss)

	- If an existing record of a player is found, the game will read in the record of that player.

	- If a player choose to quit, (or forced to quit because there are too few players) the game will update the record.

- The game will deal 5 cards from the deck to each player.

- Player can choose to discard cards.

- The result is determined by the rank of a player's hand.



<<<<<<<<<<<<<<<<<<<<<<<

Error:

error Expression: invalid operator< 

- error with inconsistent operator definition



error: vector iterator not incrementable

- after the erase function is called, the iterator is invalidated.

- instead we used   i = gamePlayer.erase(...); to update the iterator.



<<<<<<<<<<<<<<<<<<<<<<<

Documentations for error values in lab3

enum command_line_return { less_than_three_arguments = 5};

enum mainFunction_num {exception_error = 40};

enum Num{ not_enough_to_deal = 135, too_many_players = 11};

enum error{instance_not_available = 20, game_already_started, unknown_game, no_game_in_progress, already_playing, ignore_this_bad_input};



<<<<<<<<<<<<<<<<<<<<<<<

Test Cases: 

Case 1: /*This case is to test normal cases where users join and play the games, some users quit after one round, and other users join. Users can choose to throw different cards using the command line arguments.

		  After all users quit, the game is over. */

		

		Command line: H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw xinyi yuan kunyao

		Output: 

		game started



		Name: xinyi Hand: 3h 4c 5h qh kh

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



		Command line: no cards

		Output: 

		Name: yuan Hand: 4d 6d 8c 10h js

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



		Command Line: 1 2 3

		Output: 

		Name: kunyao Hand: 3d 6s 7h 10d 10s

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



		Command Line: all cards

		Output:

		Name: xinyi

		Hand: 3h 4c 5h qh kh

		Name: yuan

		Hand: 2c 8h 8s 10h js

		Name: kunyao

		Hand: 7d 8d 10c kd ac



		The result is

		xinyi 2 5

		3h 4c 5h qh kh

		kunyao 0 1

		7d 8d 10c kd ac

		yuan 7 4

		2c 8h 8s 10h js

		Does anyone want to quit the game? Please enter 'yes' or 'no'



		Command Line: yes

		Output:

		Enter your usernames(seperated by spaces)



		Command Line:kunyao yuan

		Output:

		Does anyone want to join the game? Please enter 'yes' or 'no'



		Command Line:yes

		Output:

		Enter the names of newusers (seperate by spaces)



		Command Line:april

		Output:

		Name: xinyi Hand: 3c 3s 4s 8c jc

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

		

		Command Line: 1 2 3

		Output:

		Name: april Hand: 2h 3d 6c 9d kc

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



		Command Line: 4 2 1

		Output: 

		Name: xinyi

		Hand: 5c 8c 10d jc as

		Name: april

		Hand: 2c 6c 10h jd kc



		The result is

		april 0 1

		2c 6c 10h jd kc

		xinyi 3 5

		5c 8c 10d jc as

		Does anyone want to quit the game? Please enter 'yes' or 'no'

	

		Command Line: yes

		Output: 

		Enter your usernames(seperated by spaces)



		Command Line: april xinyi

		Output: 

		Does anyone want to join the game? Please enter 'yes' or 'no'



		Command Line: no

		Output: 

		Game Over! There are not enough players.





Case 2: Command Line argument: H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDrw xinyi yuan kunyao

		Output:

		lab3: Exception caught40

		/* this output is correct because the game name is wrong */



Case 3: Command Line arguments: H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw xinyi

		Output: 

		lab3: The program should be run with at least 3 arguments: the name of a game, and the names of two or more players5

		/*This output is correct because the user only key in one username. */



Case 4: Command Line arguments: H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw xinyi xinyi

		Output: 

		lab3: Exception caught40

		/* this output is correct because two same player names are keyed in. */



Case 5: Command Line: H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw a b c d e f g h i j k l

		Output: 

		lab3: too many players135

		/*This output is correct because there are more than 11 players, and they won't get enough cards to play. */



Case 6: /*When discarding cards, if the user keys in invalid inputs, the command will be reprompt to ask users to key in again. */

		Name: e Hand: 3s 5h 10h qh kc

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

		

		Command Line Argument: abc 1 2 3

		Output: 

		Name: e Hand: 3s 5h 10h qh kc

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



Case 7: /*When exactly 10 players are added, if no players quit, the game will not ask if there are more players that want to join the game. */

		H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw a b c d e f g h i j

		Output: game started ... 

				(intermediate steps are omitted.)

				...

		Does anyone want to quit the game? Please enter 'yes' or 'no'

		Command Line argument: no 

		Output: (Take note that the game does not prompt users to add players)

		Name: a Hand: 6c 7s 9h jc qd

		Which card do you want to discard?

		Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



Case 8: /*When there is only one player left, the game will quit automatically, and the system will record his/her results*/

		H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw a b c d e f g h i j

		Output: game started ... 

				(intermediate steps are omitted.)

				...

				Does anyone want to quit the game? Please enter 'yes' or 'no'

		Command: yes

		Output: 

		Enter your usernames(seperated by spaces)

		Command: a b c d e f g h i

		Does anyone want to join the game? Please enter 'yes' or 'no'

		no

		Game Over! There are not enough players.

		/*This is correct because there is only one player in the game. */







<<<<<<<<<<<<<<<<<<<<<<<



EXTRA CREDITS:

		1. We modified the Player class and added one private member bool pAuto to indicate whether this player 

		   is a automated player or not.

		2. When a command line input name has an asterick(*) at the end of the name, the pAuto will be set to 

		   true, and the player's pName will be the input name without the asterick(*).

		3. If pAuto is true for a player, the program will find the rank of this automatic player's hand. Based on his hand,

		   the program will find out which card should be discarded according to the instruction. 

		   eg: If the hand is "two pairs", we will find out whether if follows xaabb, aaxbb, or aabbx, and discard the

		   unmatched card x.

		4. For each automated player, the program will calculate a probability that determines whether this player 

		   should quit the game or not based on the result of the last game.The program will also generate a random number

		   0-99. By comparing the random number and calculated probablity, the program will determine whether this automated

	           player will leave/remain.If this automated player quit(erase it from the gamePlayer), the program will update his record.

		    





<<<<<<<<<<<<<<<<<<<<<<<

Game Simulation: 



																										/*Start the game with 2 players and two automatic players: */

H:\My Documents\Visual Studio 2013\Projects\lab3\Debug>lab3 FiveCardDraw ape joyce rachel* xinyi*

game started



Name: ape Hand: 2h 3h 7d 8d jh

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

1 2 3 4



Name: joyce Hand: 3s 5s 8c 9h 10d

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

all cards



																					/*Take note that the following codes are generated automatically without any user inputs(The system chooses to discard cards for the automatic players): */

Name: rachel Hand: 2s 6s qc kh ac

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



Name: xinyi Hand: 5c 6h 8h jc ad

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

Name: ape

Hand: 5d 5h 6d jh ah

Name: joyce

Hand: 4c 8s 9c 10h 10s

Name: rachel

Hand: 2d 4h 7h kd ac

Name: xinyi

Hand: 2c 3c js qh ad



The result is

rachel 0 6

2d 4h 7h kd ac

xinyi 4 7

2c 3c js qh ad

ape 0 10

5d 5h 6d jh ah

joyce 1 0

4c 8s 9c 10h 10s

Does anyone want to quit the game? Please enter 'yes' or 'no'

yes

Enter your usernames(seperated by spaces)

ape

Does anyone want to join the game? Please enter 'yes' or 'no'

yes

Enter the names of newusers (seperate by spaces)                                             /*Take note that another automatic player join the game*/

michael*



Name: joyce Hand: 2c 6s 9d ks ad

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

1



Name: rachel Hand: 3d 4d 6c 8c kd

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



Name: xinyi Hand: 7c 7s qd qs kc

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



Name: michael Hand: 3c 9c 10d jd js

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

Name: joyce

Hand: 6s 9d kh ks ad

Name: rachel

Hand: 5c 8c 9s qc kd

Name: xinyi

Hand: 7c 7s jc qd qs

Name: michael

Hand: 2d 3s 10h jd js



The result is

rachel 0 7

5c 8c 9s qc kd

michael 1 3

2d 3s 10h jd js

joyce 1 1

6s 9d kh ks ad

xinyi 5 7

7c 7s jc qd qs

Automated player: rachel decided to quit                                                            /*Note that rachel who is the last in this round decides to quit.*/

Does anyone want to quit the game? Please enter 'yes' or 'no'

yes

Enter your usernames(seperated by spaces)

joyce

Does anyone want to join the game? Please enter 'yes' or 'no'

no



Name: xinyi Hand: 2h 3c 5h qc qh

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.



Name: michael Hand: 3h 4s 6h 10h kh

Which card do you want to discard?

Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces.

Name: xinyi

Hand: 4d 10s jc qc qh

Name: michael

Hand: 3s 8c 8h 10h kh



The result is

michael 1 4

3s 8c 8h 10h kh

xinyi 6 7

4d 10s jc qc qh

Automated player: xinyi decided to quit                      

Automated player: michael decided to quit                                                           /*Note that both players have the probability to quit games, regardless of their rank in the game, but the probability might be different */ 

Does anyone want to quit the game? Please enter 'yes' or 'no'

no

Does anyone want to join the game? Please enter 'yes' or 'no'

yes

Enter the names of newusers (seperate by spaces)

rachel

Game Over! There are not enough players.







========================================================================

    CONSOLE APPLICATION : lab3 Project Overview

========================================================================



AppWizard has created this lab3 application for you.



This file contains a summary of what you will find in each of the files that

make up your lab3 application.





lab3.vcxproj

    This is the main project file for VC++ projects generated using an Application Wizard.

    It contains information about the version of Visual C++ that generated the file, and

    information about the platforms, configurations, and project features selected with the

    Application Wizard.



lab3.vcxproj.filters

    This is the filters file for VC++ projects generated using an Application Wizard. 

    It contains information about the association between the files in your project 

    and the filters. This association is used in the IDE to show grouping of files with

    similar extensions under a specific node (for e.g. ".cpp" files are associated with the

    "Source Files" filter).



lab3.cpp

    This is the main application source file.



/////////////////////////////////////////////////////////////////////////////

Other standard files:



StdAfx.h, StdAfx.cpp

    These files are used to build a precompiled header (PCH) file

    named lab3.pch and a precompiled types file named StdAfx.obj.



/////////////////////////////////////////////////////////////////////////////

Other notes:



AppWizard uses "TODO:" comments to indicate parts of the source code you

should add to or customize.



/////////////////////////////////////////////////////////////////////////////

