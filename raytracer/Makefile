.PHONY: configure build run test clean

configure:
	cmake --preset debug

build: configure
	cmake --build --preset debug

run: configure
	cmake --build --preset debug --target run

test: build
	ctest --preset debug

clean:
	cmake -E rm -rf build
