CXX ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g -Iinclude
SOURCES := $(wildcard src/*.cpp)
LIB_SOURCES := $(filter-out src/main.cpp,$(SOURCES))
TEST_SOURCES := $(wildcard tests/test_*.cpp)
TEST_BINS := $(patsubst tests/%.cpp,build/%,$(TEST_SOURCES))

.PHONY: all run test clean
all: build/pfm

build:
	mkdir -p build

build/pfm: $(SOURCES) $(wildcard include/*.h) | build
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

build/test_%: tests/test_%.cpp $(LIB_SOURCES) $(wildcard include/*.h) | build
	$(CXX) $(CXXFLAGS) $< $(LIB_SOURCES) -o $@

run: build/pfm
	./build/pfm

test: $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do echo "Running $$t"; ./$$t; done

clean:
	rm -rf build
