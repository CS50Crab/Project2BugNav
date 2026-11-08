# Project2BugNav

## Dependencies

- Git
- CMake 3.28+
- Ninja
- A C++17 compiler

## Build

(In Windows powershell) Run these commands from the folder that has `CMakeLists.txt`:

```powershell
cmake -S . -B build -G Ninja
cmake --build build -j 8
```

CMake downloads SFML 3.0.1 during configuration. 

## Run

For a map with 100,000 cells:

```powershell
.\build\bin\bug_nav_graphics.exe --large
```

For the smaller map:

```powershell
.\build\bin\bug_nav_graphics.exe
```

## Rebuild After Changes

Close the app, then run this to rebuild:

```powershell
cmake --build build -j 8
```
