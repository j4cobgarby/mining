# A cool mining game

## A bit like Terraria

![mockup](https://github.com/j4cobgarby/mining/blob/menustuff/.for_github/mockup.png)

### Worlds and stuff file architecture
```
/worlds
    └── <worldname>
        ├── data ........................ a directory containing data about the world
        │   └── blocks.dat .............. a binary file containing all the blocks in the world
        └── players ..................... a directory containing binaries for each of the players who've been in this world
            └── <playername>.dat ........ a binary file containing player info, like their name, inventory, position, etc.
            └── <anotherplayer>.dat
```

### Requirements for building:
 - CMake (>= 3.4)
 - g++
 - SFML (>= 2)
 - TGUI (>= 0.7) [[link](https://tgui.eu)]
 - Any block must be adjacent to at least one other block.
 - You can't place too far away from youself.