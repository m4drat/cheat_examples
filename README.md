# Architecure
| Project | Description |ready to work|
| ------ | -------------|-------------|
| game | Main Project. Simple Console RPG-like game with basic inventory and fight systems. | ```yes```|
| gameUnitTests | Unit tests for game. | ```yes``` |
| injector | Simple dll injector (using ```CreateRemoteThread``` with ```LoadLibraryA```)  | ```yes```|
| internalCheat | DLL-library which can be injected in target process using ```injector``` | ```yes```|
| externalCheat | Simple external cheat, which uses ```ReadProcessMemory``` and ```WriteProcessMemory``` | ```no```
 # Game
Sooo, thit is the main part of the project. The game is a turn-based RPG-like game with implemented inventory system, as well as battle system. 
__At the beginning you have 5 default options to use:__
- ```[c]reate``` - create new player with default stats (63hp, 4dmg). 
- ```[f]ight``` - fight with random enemy (only active, if you have created new player before)
- ```[s]tats``` - view your player stats
- ```[i]inventory``` - displays your inventory or allows you to select a new active item. (if player isn't empty)
- ```[e]xit``` - leave game.
##### fight mode
__In this mode you have 3 options to choose from:__
- ```[a]ttack``` - attack enemy (if you have active weapon, damage will be bigger)
- ```[h]eal``` - heal yourself, if you have heal potions in inventory
- ```[r]un``` - run away and lose money with exp, which you could get for winning
# Game Unit Tests
Just simple unit tests, to check after any source-code editing. (by default anything is working)
#### Run them in visula studio: 
    Test -> Windows -> Test Explorer
    Test Explorer -> Run All
![Imgur](https://i.imgur.com/wV9JVZG.png)
# Injector
DLL-injector, which uses ```LoadLibraryA``` and ```CreateRemoteThread``` to load your DLL into process memory. After using this injector with your DLL you will get new thread, which will run all your code from beginning of ```DllMain```.
![Imgur](https://i.imgur.com/XlLDUwZ.png)
# Internal Cheat
DLL which can be used with injector.
# External Cheat
Simplified version of injector-like cheat.
This version uses ```ReadProcessMemory``` and ```WriteProcessMemory``` to manipulate values inside process.
