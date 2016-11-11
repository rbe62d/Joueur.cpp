# GAME_NAME C++ Client

This is the root of you AI. Stay out of the `joueur/` folder, it does most of the heavy lifting to play on our game servers. Your AI, and the game objects it manipulates are all in `games/game_name/`, with your very own AI living in `games/game_name/ai.h` and `games/game_name/ai.cpp` files for you to make smarter.

## How to Run

This client has been tested and confirmed to work on the Campus rc##xcs213 Linux machines, but it can work on your own Windows/Linux/Mac machines if you desire.

Also make sure **NOT** to try to compile this in your Missouri S&T S-Drive. This is not a fault with the client, but rather the school's S-Drive implementation changing some file permissions during run time. We cannot control this. Instead, we recommend cloning your repo outside the S-Drive and use an SCP program like [WinSCP](https://winscp.net/eng/download.php) to edit the files in Windows using whatever IDE you want if you want to code in Windows, but compile in Linux.

### Linux

    make
    ./testRun MyOwnGameSession

If you are on your own machine, make sure you've installed boost. The `libboost-all-dev` package should be up to date. You'll also need the `cmake` package for make to work.

### Windows

For Windows, Boost has a simple way to [compile from source using bootstrap](http://www.boost.org/doc/libs/1_58_0/more/getting_started/windows.html). You'll need to do that. This client does work with VC++, you can create a solution at the root or ask a dev for the sln file. Just add the directory you built Boost in the Project's linker configuration. You'll also need to use the following command line arguments:

`Chess -s r99acm.device.mst.edu`

## Other notes

The initial `make` step may take upwards of 2 minutes. You should see a percent progress updating on your screen, but it will be slow. Subsequent `make`s should be only a few seconds if you don't `make clean`.

The only file you should ever modify to create your AI are the `ai.cpp` and `ai.h` files. All the other files are needed for the game to work. In addition, you should never be creating your own instances of the Game's classes, nor should you ever try to modify their variables. Instead, treat the Game and its members as a read only structure that represents the game state on the game server. You interact with it by calling the game functions.

### Notice for CS 1570 Students

We use pointers extensively throughout this C++ client. If you are not familiar with pointers here's the quick and dirty on what you need to know. Normally you'd use the `.` (dot) operator to access member variables:

    point.x = 0;

However with pointers, use the `->` (arrow) operator instead:

    point->x = 0;

Once you take Data Structures you will learn why this is the case. And for those on you in Data Structures, we manage the memory of the game objects automatically for you, just don't try to delete or modify any of our game structures.
