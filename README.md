# A cool mining game

## A bit like Terraria

---

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
