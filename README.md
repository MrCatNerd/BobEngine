# BobEngine
BobEngine is a WIP game engine written in C++

current features: phong lighting, triangels, and BLOCKS

---

<img src="https://github.com/MrCatNerd/BobEngine/blob/dev/res/bob.jpg?raw=true" alt="Bob Ross" style="max-width:70%; max-height:70%;">

> [!WARNING]
> this engine is still a WIP

---

<details>
<summary>screenshots</summary>

<img src="https://github.com/MrCatNerd/BobEngine/blob/main/res/readme_screenshots/screenshot1.png?raw=true" alt="screenshot" style="max-width:100%; max-height:50%;">

</details>

---

## Compiling Running and Cleaning

### General Stuff
```sh
### Running
make
# or
#make run

### Compiling
make compile

### Cleaning
make clean
```

### Build profiles
```sh
# Debug mode (default)
make PROFILE=Debug

# Release mode
make PROFILE=Release

# If you want to only compile
#make compile PROFILE=<profile>
```

### Compilation databases

```sh
make compile_commands.json
```

---

## Requirements
Ensure you have the following installed on your system

### GLFW
<details>
<summary>How to install GLFW manually on a Debian based system</summary>

```sh
# installs GLFW on debian based systems
sudo apt-get install -y make cmake git
sudo git clone "https://github.com/glfw/glfw.git" "/usr/local/lib/glfw" --depth 1
sudo cmake -S "/usr/local/lib/glfw" -B "/usr/local/lib/glfw/build"
sudo make -C "/usr/local/lib/glfw/build" install # you can use cmake --build --install if you really want to
```
</details>

<details>
<summary>How to install GLFW with <a href="https://github.com/microsoft/vcpkg">vcpkg</a></summary>

```sh
vcpkg install glfw3
```
</details>

### GLEW

<details>
<summary>How to install GLEW manually on a Debian based system</summary>

```sh
# installs GLEW on debian based systems
sudo apt-get install -y libglew-dev
```
</details>

<details>
<summary>How to install GLEW with <a href="https://github.com/microsoft/vcpkg">vcpkg</a></summary>

```sh
vcpkg install glew
```
</details>

### OpenGL

<details>
<summary>How to install OpenGL manually on a Debian based system</summary>

```sh
sudo apt-get install -y libgl1-mesa-dev
```

</details>

<details>
<summary>How to install OpenGL with <a href="https://github.com/microsoft/vcpkg">vcpkg</a></summary>

```sh
vcpkg install opengl
```

</details>

### GLM
I am too lazy to add debian installation instructions (maybe ill do it later)

<details>
<summary>How to install GLM with <a href="https://github.com/microsoft/vcpkg">vcpkg</a></summary>

```sh
vcpkg install glm
```

</details>

---


## TODO
mostly sorted by priority

- [x] CMake
- [ ] Good README
- [ ] a THICC TOC
- [ ] Examples
- [ ] Docs
- [ ] Tests (i got no idea how do you test a game engine)
