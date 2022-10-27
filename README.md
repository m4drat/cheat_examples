# Cheat examples

## Project modules

| Project | Description |
| ------ | -------------|
| injector | Dll injector (uses ```CreateRemoteThread``` with ```LoadLibraryA```) |
| internalCheat | DLL-library to inject into the target process using ```injector``` |
| externalCheat | External cheat, which uses ```ReadProcessMemory``` and ```WriteProcessMemory``` |
| game | RPG-like game with basic inventory and fight systems. |
| gameUnitTests | Unit tests for the game. |

## Injector

The injector is a simple console application, which injects a DLL into a target process. It uses ```CreateRemoteThread``` with ```LoadLibraryA``` to inject the DLL.

![Imgur](https://i.imgur.com/XlLDUwZ.png)

## Internal Cheat

Internal cheat is a DLL-library, which is injected into the target process using ```injector```. It uses pattern scanning to find the addresses of the game's variables.

### How it works

1. The DLL is injected into the target process using ```injector```.

    ```c++
    // Write DLL path to newly allocated memory
    WriteProcessMemory(psHandle, psMemoryLibPath, fullLibPath, MAX_PATH, &fullLibPathSize);

    // Get address of LoadLibraryA
    FARPROC loadLibraryA = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryA");

    // Call LoadLibraryA in remote process to load DLL
    CreateRemoteThread(psHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryA, psMemoryLibPath, NULL, NULL);
    ```

2. After the dll is injected it will begin it's execution in the memory space of the target process. The first thing it does is to find the address of the `hp` variable.

    ```c++
    // InternalCheat.cpp
    mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_internal("50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD"));
    ```

3. The final step is to start the cheat loop. Every 5 seconds the cheat will set `hp` variable to INT_MAX.

    ```c++
    // InternalCheat.cpp
    const auto player_health = reinterpret_cast<int*>(reinterpret_cast<DWORDLONG>(mem_region) + hpOffset);
    while (true)
    {
        *player_health = INT_MAX; // update player's health
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // sleep for 5 seconds
    }
    ```

Final results:

![Imgur](https://i.imgur.com/EuwAd19.png)

## External Cheat

Simplified version of injector-like cheat.
This version uses ```ReadProcessMemory``` and ```WriteProcessMemory``` to manipulate values inside process memory space.

### How it works

1. The cheat tries to acquire a handle to the target process.

    ```c++
    // Get a handle to the process
    activePsHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    ```

2. If previous step was successful, the cheat will try to find the address of the `hp` variable.

    ```c++
    // ExternalCheat.cpp
    mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_external(activePsHandle, "50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD"));
    ```

3. If pattern scanning was successful, the cheat will start the cheat loop. Every 5 seconds the cheat will set `hp` variable to INT_MAX.

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

Final results:

![Imgur](https://i.imgur.com/2LeTFqy.png)

## The Game

To test developed cheats I've created a simple game with basic inventory and fight systems. The game is written in C++.

Main menu:

- ```[c]reate``` - Creates a new player with default stats (63hp, 4dmg).
- ```[f]ight``` - fight with a random enemy (only active, if you have an active player)
- ```[s]tats``` - view your player stats
- ```[i]inventory``` - displays your inventory or allows you to select a new active item. (if you have an active player)
- ```[e]xit``` - closes the game

Fight menu:

- ```[a]ttack``` - attack an enemy
- ```[h]eal``` - heal yourself
- ```[r]un``` - run away from the enemy

Inventory menu:

- ```[d]isplay``` - displays your inventory
- ```[e]quip```   - allows you to select a new active item

![Imgur](https://i.imgur.com/0kmwRTx.png)

## Game Unit Tests

How to run

1. Test -> Windows -> Test Explorer
2. Test Explorer -> Run All
