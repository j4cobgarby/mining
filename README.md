# A cool mining game

## A bit like Terraria

![mockup](https://github.com/j4cobgarby/mining/blob/menustuff/.for_github/screenshot.png)

### Worlds and stuff file architecture
```
/worlds
    └── <worldname>
        ├── data ........................ a directory containing data about the world
        │   └── blocks.dat .............. a binary file containing all the blocks in the world
        │   └── dims .................... the dimensions of the world, seperated by a space
        │   └── seed .................... the seed of the world
        │   └── spawn_position .......... spawn position of the player, seperated by a tab
        └── players ..................... a directory containing binaries for each of the players who've been in this world
            └── <playername>.dat ........ a binary file containing player info, like their name, inventory, position, etc.
            └── <anotherplayer>.dat
```

### Requirements for building:
 - CMake (>= 3.4)
 - Your favourite C++ compiler/linker.
 - SFML (>= 2)
 - TGUI (>= 0.7) [[link](https://tgui.eu)]
 - Any block must be adjacent to at least one other block.
 - You can't place too far away from youself.

### Installation

If you're on a Unix system, with bash installed, you can use the provided shell scripts. They should be executable, but if not then you'll need to chmod them yourself (`chmod a+x *.sh`).

To install it to /usr/bin, run (**doesn't actually work at the moment due to asset paths**)

```
./install.sh # You may need to sudo this
```

Or if you don't want to do that, you can just run

```
./run.sh
```

To build it in the `build` directory and run it from there - it's up to you.

If you're not on a Unix-based system and so can't run the shell scripts, you can still build it (as long as you have CMake.)

```
# Make a directory called build inside `mining`, and enter it
cmake ../src -G <A makefile type, or leave out the -G flag for the default>
# Then use whatever sort of makefile you generated for your platform to build it, and run the executable.
```