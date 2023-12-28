# Build & Compile

> For all of the following installations, make sure to have [Cmake](https://cmake.org/download/) installed

## Windows

### MSVC Compiler

1. `git clone -b main https://github.com/UsernameDP/Chaos-Equations.git Chaos-Equations` - Clone the Repository.
2. `cd Chaos-Equations` - open the Chaos Equations Directory.
3. `cmake -S . -B build` - Build using the CMakeLists.txt files.
4. `cmake --build build --config Release` - Compile using MSVC in the Release build.
5. `cd build/Release/bin` - Enter the bin directory where all executables are located.
6. `./Chaos_Equations.exe` - This will run the program / executable.

# Tutorial

## Hot Keys

- **ESC** - To hide all GUIs
- **W A S D** - to rotate about the _Camera Target_

## GUI

### Particles

- **Number of Particles** - Number of particles you would like to spawn. Depending on your GPU, you will be able to spawn more or less.
- **Spawn Point** - Where to spawn your particles.
- **Displacement** - Defines the maximum distance in which your particles will spawn.

### Colors

- **Highest Speed** - Defines the highest speed for reaching the
