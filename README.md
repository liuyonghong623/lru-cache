# LRU Cache

A generic LRU Cache implementation based on C++17.

## Features

- Generic key-value cache
- O(1) average-time get, put, and remove operations
- LRU eviction policy

## Technologies

- C++17
- STL
- CMake
- Git

## Project Status

Core implementation and automated tests completed.

## Project Structure

```text
lru-cache/
├── CMakeLists.txt
├── include/
│   └── lru_cache.h
├── tests/
│   └── test_lru_cache.cpp
├── .gitignore
└── README.md
```

## Requirements

- C++17 compatible compiler
- CMake 3.16 or later

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run Tests

```bash
ctest --test-dir build --output-on-failure
```

## Usage Example

```cpp
#include <iostream>
#include "lru_cache.h"

int main(){
	//Create a cache with capacity 2
	LRUCache<int, int> cache(2);

	//Insert elements
	cache.put(1, 100);
	cache.put(2, 200);

	//Retrieve an element
	int value = 0;
	if (cache.get(1, &value)){
		std::cout << "key 1: " << value << '\n';
	}

	//Insert another element and trigger eviction
	cache.put(3, 300);

	//Key 2 should have been evicted
	if (!cache.get(2, &value)){
		std::cout << "Key 2 was evicted." << '\n';
	}

	return 0;
}
```

Expected output:

```text
Key 1: 100
Key 2 was evicted.
```
