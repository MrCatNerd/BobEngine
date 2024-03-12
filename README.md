# BobEngine
BobEngine is a WIP game engine written in C++

current features: triangles, triangles, triangles and bugs lol

---


### WARNING: this engine is still a WIP and currently only supports Linux


## Compiling and Running

### Running
```sh
make

# or
#mkdir -p build
#cmake . -B build
#make -C build
```

### Building
```sh
make compile

# or
#mkdir -p build
#cmake . -B build
```

## Requirements
Ensure you have the following installed on your system

### GLFW
<details>
<summary>How to install GLFW manually on a Debian based system</summary>

```sh
# installs GLFW on debian based systems
sudo apt-get install -y make cmake git
sudo git clone https://github.com/glfw/glfw.git "/usr/local/lib/glfw" --depth 1
sudo cmake -S "/usr/local/lib/glfw" -B "/usr/local/lib/glfw/build"
sudo make -C "/usr/local/lib/glfw/build"
sudo make -C "/usr/local/lib/glfw/build" install
```
</details>

<details>
  <summary>How to install GLFW with <a href="https://github.com/microsoft/vcpkg">vcpkg</a></summary>

  ```sh
  vcpkg install --head glfw3
  ```
</details>

### GLEW

<details>
<summary>How to install GLEW manually on a Debian based system</summary>

```sh
# installs GLEW on debian based systems
sudo apt-get update
sudo apt-get install -y libglew-dev
```
</details>

<details>
  <summary>How to install GLEW with <a href="https://github.com/microsoft/vcpkg">vcpkg</a></summary>

  ```sh
  vcpkg install --head glew
  ```
</details>

## LSP and compilation databases

BobEngine currently uses Make instead of CMake.
If you're using Neovim with an LSP like Clangd, you'll need a compilation database to avoid errors
you can use a tool like bear to do it

```sh
#sudo apt install -y bear
#yes | sudo pacman -S bear
make clean; bear -- make all
```

---


## TODO
mostly sorted by priority

 - [ ] The whole engine thingy
 - [ ] CMake
 - [ ] Good README
 - [ ] Examples
 - [ ] Docs
 - [ ] Tests (i got no idea how do you test a game engine)
