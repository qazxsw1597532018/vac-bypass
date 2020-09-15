# vac-bypass
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)  [![forthebadge](https://forthebadge.com/images/badges/ctrl-c-ctrl-v.svg)](https://forthebadge.com)

## About
A very rudimentary Valve Anti-Cheat 3 bypass written in C99. Unlike other previous releases this can be used without running Steam as Administrator, and can be injected while already in-game as it hooks the call routine.

The code could still be improved with manual mapping, hashing VAC modules properly, and a few other things; but it works for the most part.

## Usage
1. Run Steam without admin rights
2. Download/compile everything and run `loader.exe` as Administrator
3. If everything goes well, a message should pop up saying it has successfully loaded
4. Enjoy playing without VAC scans

You may also use your own injector if you run Steam as Admin. Process Hacker also works for injecting into SteamService.exe.

## Compatibility

This was only tested on Windows 10 Enterprise 2004 in CS:GO. Some Steam and heartbeat modules might not be whitelisted, if you experience VAC kicks look at `C:/vac_log.txt` and whitelist any new blocked modules.

## Compilation

vac-bypass was made using CMake, LLVM and Ninja, I cannot guarantee it will build with MSVC/GCC out of the box. If you use Visual Studio you may easily create a VS project to build as it has no dependencies.

## Other
Some other functions of interest and bypass vectors (in steamservice.dll):
	
	55 8b ec 83 ec ? 53 56 8b 75 ? 8b d9 83 7e
    55 b8 ec 83 ec ? 53 56 57 51 8b c4 8d 4d ? c7 ? ? ? ? ? ff 75 ? e8 ? ? ? ? 8b 7d ? 8d 4d
	55 8b ec 6a ? 68 ? ? ? ? 68 ? ? ? ? 64 a1 ? ? ? ? 50 64 89 25 ? ? ? ? 83 ec ? 53 56 57 89 65 ? 8b f9

Also thanks to PhY1z on UC for some of his structs from vac3_inhibitor, and for inspiring me to reverse VAC back in February.