# BobEngine
BobEngine is a WIP game engine written in C++

current features: triangles, triangles, triangles and bugs lol

---

<img src="https://github.com/MrCatNerd/BobEngine/blob/dev/res/bob.jpg?raw=true" alt="Bob Ross" style="max-width:70%; max-height:70%;">

> [!WARNING]
> this engine is still a WIP

---

## Compiling Running and Cleaning

### Running
```sh
make
# or
#make run
```

### Building
```sh
make compile
```

### Cleaning
```sh
make clean
```

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
sudo make -C "/usr/local/lib/glfw/build"
sudo make -C "/usr/local/lib/glfw/build" install
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
# installs OpenGL on debian based systems
vcpkg install opengl
```

</details>


## Compilation databases

```sh
make compile_commands.json
```

---


## TODO
mostly sorted by priority

- [ ] The whole engine thingy
- [x] CMake
- [ ] Good README
- [ ] a THICC TOC
- [ ] Examples
- [ ] Docs
- [ ] Tests (i got no idea how do you test a game engine)
