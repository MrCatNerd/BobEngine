.PHONY: default compile run clean

default: run

run: compile
	./BobEngine

compile: build
	cmake -B build -S .
	make -C build

clean:
	rm -f BobEngine
	rm -rf build
	rm -f CMakeCache.txt
	rm -rf .cache
	rm -f compile_commands.json


compile_commands.json: build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build -S .
	cp build/compile_commands.json .

build:
	@mkdir build

