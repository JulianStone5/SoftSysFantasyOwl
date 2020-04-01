# Battleship.net
### Jack Mao, Casey May, Julian Stone

## Goals
Casey
Our goal for the project was to create a two player interactive experience through network connection in the terminal. Our final product had to have two individuals being prompted for inputs and allowing some sort of gameplay to take place. It had to utilize network socket creation in order to communicate between our two aforementioned terminals. 

Our learning goals revolved around understanding network programming and proper ways to collaborate digitally. Because there is so much existing code on the internet that we could use as inspiration, we wanted to get a deep grasp of what it meant to create a network connection and what was required for terminal-terminal communication. On a side note, we were also motivated to learn structures that lend themselves to creating simple terminal based user interfaces, in this case specifically the utilization of two dimensional arrays. As far as digital collaboration, we wanted to learn how to traverse the world of Atom's Teletype. This software allows one host to invite other users to collaborate on their code and change things in real time, similar to the functionality of a shared google doc. We learned that this caused our commit history on github to look rather interesting, as nearly all the commits came from one user, but this was a result of the fact that our group programming all took place on Teletype.
## Resources
Casey
We had a few primary sources of information from our project. Much of our early informational searching was done via a previous project, "HackerChat." Beyond that, there were multiple geeksforgeeks articles that provided a great deal of vital information to make our network programming functional. These are linked here: 
https://www.geeksforgeeks.org/socket-programming-cc/ 
https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
Chapters 9 and 11 of HeadFirst C were also helpful in allowing us to understand what some of the basics were behind this process, as for all of is this was basically our first interaction with server/client work.

## What Was Done
Jack

In this project, our aim is create the battleship game that can be played remotely between two players. Battle ship is a game wherein two players are given a 9 x 11 board and 5 ships. The ships are sized 1 x 1, 2 x 1, 3 x 1, 4 x 1, and 5 x 1, respectively. Without looking at each others' board, the two players randomly place the five ship on the board. Then, the players take turns, each guessing a block on the board in hopes that they have successfully "hit" the enemy ship. The first player to "hit" all of the opposing player's ships is the victor.  

To create the game, we first have to consider the essential components of our game. The most important aspects of our game are the network and the game rules. As such, we created a 

show game working (screenshot)

## Design Decision
Jack

pivot from two client/one server to one client/one server

- time and overscoped, not necessary given scope, only need two users, etc

## Code Snippets
Julian

Network: basic socket stuff, delays

Data Storage: struct and storing board

## Reflection
Casey

Our project ended at a place that felt very good as far as progress goes. Our lower bound was a player vs. simple AI game, that would have allowed us to have the server manage one player's moves. Our higher bound was a central server creation and two separate clients that would both alternate communication with the central server. Where we ended was with two terminals, one which acted as the server and one which acted as the client, but both of which allowed player input. All of our learning goals felt achieved, though to varying levels. Our team felt very comfortable with the use of Atom's Teletype add-on by the conclusion of our project's code. We also all understand network programming, although there is some variance in what extent that knowledge exists, as there always is, considering varying learning speeds. Because of this, we believe that all of our learning goals and project goals have been achieved, if not exceeded. 
