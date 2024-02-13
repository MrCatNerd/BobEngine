# BobEngine
A game engine

---

## Compiling and Running

### Run
```sh
make
```

### Compile only
```sh
make normal
```

## Requirements
Ensure you have the following installed on your system

### GLFW
```sh
# installs GLFW on debian based systems
udo apt-get install -y make cmake git
sudo git clone https://github.com/glfw/glfw.git "/usr/local/lib/glfw" --depth 1
sudo cmake -S "/usr/local/lib/glfw" -B "/usr/local/lib/glfw/build"
sudo make -C "/usr/local/lib/glfw/build"
sudo make -C "/usr/local/lib/glfw/build" install
```

### GLEW
```sh
# installs GLEW on debian based systems
sudo apt-get update
sudo apt-get install -y libglew-dev
```

## TODO
- CMake
- The whole engine thingy
