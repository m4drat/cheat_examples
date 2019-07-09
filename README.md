
# Architecure
| Project | Description |ready to work|
| ------ | -------------|-------------|
| game | Main Project. Simple Console RPG-like game with basic inventory and fight systems. | ```yes```|
| gameUnitTests | Unit tests for game. | ```yes``` |
| injector | Simple dll injector (using ```CreateRemoteThread``` with ```LoadLibraryA```)  | ```yes```|
| internalCheat | DLL-library which can be injected in target process using ```injector``` | ```yes```|
| externalCheat | Simple external cheat, which uses ```ReadProcessMemory``` and ```WriteProcessMemory``` | ```yes```
 # Game
Sooo, thit is the main part of the project. The game is a turn-based RPG-like game with implemented inventory system, as well as battle system. 
__At the beginning you have 5 default options to use:__
- ```[c]reate``` - create new player with default stats (63hp, 4dmg). 
- ```[f]ight``` - fight with random enemy (only active, if you have created new player before)
- ```[s]tats``` - view your player stats
- ```[i]inventory``` - displays your inventory or allows you to select a new active item. (if player isn't empty)
- ```[e]xit``` - leave game.
### fight mode
__In this mode you have 3 options to choose from:__
- ```[a]ttack``` - attack enemy (if you have active weapon, damage will be bigger)
- ```[h]eal``` - heal yourself, if you have heal potions in inventory
- ```[r]un``` - run away and lose money with exp, which you could get for winning
### inventory menu
__Here you can select your default weapon, or list all inventory:__
- ```[d]isplay``` - display inventory
- ```[e]quip```   - equip new item

![Imgur](https://i.imgur.com/0kmwRTx.png)
# Game Unit Tests
Just unit tests, to check after any source-code editing.
#### Run them in visual studio: 
    Test -> Windows -> Test Explorer
    Test Explorer -> Run All
![Imgur](https://i.imgur.com/wV9JVZG.png)
# Injector
DLL-injector, which uses ```LoadLibraryA``` and ```CreateRemoteThread``` to load your DLL into process memory. After using this injector with your DLL you will get new thread, which will run all your code from beginning of ```DllMain```.
![Imgur](https://i.imgur.com/XlLDUwZ.png)
# Internal Cheat
In this example internal cheat is dll, that uses pattern-based memory searching technique to find player object in memory. This dll injected using injector (with help of ```LoadLibraryA```).
#### LifeCycle:
1.  At the beginning, the dll is injected in the address space of the target process using ```DLL injection``` technique.
```c++
// Write DLL path to newly allocated memory
WriteProcessMemory(psHandle, psMemoryLibPath, fullLibPath, MAX_PATH, &fullLibPathSize);

// Get address of LoadLibraryA
FARPROC loadLibraryA = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryA");

// Call LoadLibraryA in remote process to load DLL
CreateRemoteThread(psHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryA, psMemoryLibPath, NULL, NULL);
``` 
2. After this functions ```DllMain``` will be called inside memory space of the target process.
Next step is initialization. During this process cheat will try to find pattern in process memory, which later can be used to retrieve ```hp``` position.
```c++
// InternalCheat.cpp
mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_internal("50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD"));
```
3. And at the end the cheat simply changes the health value to the maximum every 5 seconds.
```c++
// InternalCheat.cpp
const auto player_health = reinterpret_cast<int*>(reinterpret_cast<DWORDLONG>(mem_region) + hpOffset);
while (true)
{
	*player_health = INT_MAX; // set player healt to INT_MAX val
	std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // sleep for 5 seconds
}
```
__Overall:__
![Imgur](https://i.imgur.com/EuwAd19.png)
# External Cheat
Simplified version of injector-like cheat.
This version uses ```ReadProcessMemory``` and ```WriteProcessMemory``` to manipulate values inside process memory space.

#### LifeCycle:
1. Initially cheat trying to open handle to target process.
```c++
// Open handle to process with full access
activePsHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
```
2. If everything is good cheat trying to find pattern in memory space of the target process. (At this time using different technique which finds all memory regions of the process, and then iterate over them)
```c++
// ExternalCheat.cpp
mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_external(activePsHandle, "50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD"));
```
3. If cheat manages to find a pattern. It will try to rewrite ```hp``` value with ```INT_MAX```.
```c++
while (true)
{
	int newHp = INT_MAX;
	if (!WriteMem(activePsHandle, reinterpret_cast<DWORDLONG>(mem_region) + hpOffset, &newHp))
	{
		std::wcout << "[-] Cannot write process memory!\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
```
__Overall:__
![Imgur](https://i.imgur.com/2LeTFqy.png)
