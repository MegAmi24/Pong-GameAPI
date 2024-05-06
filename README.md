# Pong GameAPI
A simple Pong clone made to demonstrate the use of [GameAPI](https://github.com/Rubberduckycooly/GameAPI) for creating standalone games in the Retro Engine. This project also serves as a template for anyone looking to make their own games.

# How to build
This repository assumes you are already familiar with [the building process for the RSDKv5(U) Decompilation](https://github.com/Rubberduckycooly/RSDKv5-Decompilation#how-to-build).

## Get the source code
Clone the repo **recursively**, using:
`git clone https://github.com/MegAmi24/Pong-GameAPI --recursive`

If you've already cloned the repo, run this command inside of the repository:
```git submodule update --init --recursive```

## Building

### Building with CMake
No external dependencies are required; simply type the following commands in the repository's root directory:
```
cmake -B build
cmake --build build --config release
```

The resulting build will be located somewhere in `build/` depending on your system.

The following CMake arguments are available when compiling:
- Use these on the `cmake -B build` step like so: `cmake -B build -DRETRO_REVISION=2`

#### CMake flags
- `RETRO_REVISION`: What RSDKv5 revision to compile for. Takes an integer, defaults to `3` (RSDKv5U).
- `RETRO_MOD_LOADER_VER`: Manually sets the mod loader version. Takes an integer, defaults to the current latest version.
- `GAME_INCLUDE_EDITOR`: Whether or not to include functions for use in certain RSDKv5 scene editors. Takes a boolean, defaults to `on`.

### Building in Visual Studio
Simply open the solution and build the project. Make sure that the architecture, engine revision, and mod loader version match with the target engine binary.

### Building for Android
After [setting up the RSDKv5(U) decompilation for building](https://github.com/Rubberduckycooly/RSDKv5-Decompilation#how-to-build), you will need to add a symbolic link for the directory to the Pong GameAPI repository so that the game will be built as part of the APK.
To add the symlink, write the appropriate command in `[RSDKv5-decompilation-root]/android/app/jni`:
  * Windows: `mklink /d Game "[path-to-pong-repo]"`
  * Linux: `ln -s "[path-to-pong-repo]" Game`
  * If you'd like to build this as a mod rather than the main game, replace `Game` with `PongGameAPI`.

After adding the symlink, build the RSDKv5(U) decompilation in Android Studio.

# FAQ
### Q: I found a bug!
A: Submit an issue in the issues tab and I might take a look into it.

### Q: I have a suggestion/feature request!
A: Unfortunately, I will most likely not implement it. This project isn't about creating the best version of Pong moreso than it is a demonstration of GameAPI as described at the beginning of this file.

### Q: Can I use this as a template for my own GameAPI project?
A: Of course! The reason I made this is because I've seen several people ask how to set up a standalone RSDK game, so hopefully this should help with just that. Just don't go doing anything illegal!

# Special Thanks
* [Rubberduckycooly](https://github.com/Rubberduckycooly) and [st×tic](https://github.com/stxticOVFL) for [GameAPI](https://github.com/Rubberduckycooly/GameAPI).
* [skyelineee](https://github.com/skyelineee) for creating [Sonic 2 Mania](https://github.com/skyelineee/Sonic-2-Mania-Development), a GameAPI project that I occasionally looked at for reference for C++ GameAPI.
* Everyone in the [Retro Engine Modding Server](https://dc.railgun.works/retroengine) for the support!
