.PHONY: default run clean

default: run

run: build
	cmake -B build -S .
	make -C build
	./BobEngine

clean:
	rm -r build
	rm -r .cache
	rm CMakeCache.txt
	rm compile_commands.json
	rm BobEngine


compile_commands.json: build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build -S .
	cp build/compile_commands.json .

build:
	@mkdir build

