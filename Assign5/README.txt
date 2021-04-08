Name: Emily Becher
ONID: 933966976
Section: CS 161 W21
Assignment 5, due 3/14/2021

Description:

Welcome to Connect4! You can play a game of connect 4 with two 
players or against an easily beatable computer. You can select
the size of the board by adjusting the rows from 4 to 20 and 
columns from 4 to 20. Good luck getting 4 X's in a row.

Instructions:

1) Compile the program with
	g++ connect4.cpp -o connect4

2) Run the program with
	./connect4 [a] [b] [c]

	a) number of players
		range 1-2

	b) number of rows
		range 4-20

	c) number of columns
		range 4-20

3) Possible in game prompts

	a) Enter number of players: 
		Options: 1-2

	b) Enter number of rows:
		Options: 4-20

	c) Enter number of columns:
		Options: 4-20

	d) Would you like to go first?: 
		Yes responses: y, Y, 1
		No responses: n, N, 0

	e) Enter Player (1 or 2)'s move: 
		Options 1 to number of columns
		column needs to have an empty board space

	f) Would you like to play again?:
		Yes responses: y, Y, 1
		No responses: n, N, 0

Limitations:

1) User must restart program to change board size or number of players

2) User can't choose the character they are on the board

3) Board size must be between 4x4 and 20x20
