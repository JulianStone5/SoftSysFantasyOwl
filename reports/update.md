# Battleship.net
### Jack Mao, Casey May, Julian Stone

1. We plan on making a two way server that allows the connection and interaction of two players via their own terminals in order to play the game battleship. Our lower bound involves using a single computer pinging a single server in which the computer makes educated random guesses as an AI vs the human player. Our upper bound is a third computer that controls the server communications of two other computers playing battleship against each other and also runs our game algorithm.

2. We all have very similar learning goals. All of us want to learn about server-client interaction. This is the most difficult part of our code and the most interesting as well. Although we spent a bit of time working on the actual game algorithm, that was mostly comfortable coding and not the primary focus of our project. We also get some experience working with a small basis on previous sets of code (hackerchat from a previous year provides a good basis for our coding).

3. We have access to all of the resources we need in order to finish the project at this point. We have gotten a huge chunk of our necessary coding done. Our game itself is entirely done, meaning we can play a game of battleship on one computer already in the terminal. We have also done some initial one-way server connection, we can send a message to the server from a client and have that same message appear in another terminal, given that they have specified the IP of the first computer.

4. We have to work now on keeping the server continually open and having it monitor and manage gameplay. As far as specific task we’re working on, the following are the primary ones:
    1. Write a rudimentary game AI in case of lower bound: Julian Stone
    2. Open up server to allow for multiple client access points: Jack Mao
    3. Allow for server monitoring and managing of gameplay: Casey May

GitHub: https://github.com/JulianStone5/SoftSysFantasyOwl

Trello: https://trello.com/b/hbnPjdwA/fantasyowl
