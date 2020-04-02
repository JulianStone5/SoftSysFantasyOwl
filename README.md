# README

## Two Computer Operation
In order to run the battleship game, two computers must first pull this repository.  Once completed, each computer must navigate to the `SoftSysFantasyOwl` folder on their computer and run the command:
```
make -B
```
Now before continuing, make sure that both computers are on the same network so the socket connections can be made. Next, on one computer run this command to begin the server executable:
```
./server
```
Now, on the other computer run this command to begin the game:
```
./client <ip-address>
```
Make sure `<ip-address>` is filled in with the IP address of the computer running the server executable. From here, follow the games instructions and enjoy!.

## One Computer Operation
If you want to run this game on one computer in one terminal window, first run this command:
```
make -B
```
Then simply run the `main` executable:
```
./main
```
