# Circular Linked List with Sentinel Node

## Features
- Type-stable and generic
- Circular singly linked list with sentinel node
- thread safety
- Insert, delete, retrieve, iterate, delete_node_by_predication, change_nodes_data_by_predication

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run

```bash
./test_linked_lists
```

## Structure

- `inc/linked_lists.h`: Public API
- `src/linked_lists.c`: Implementation
- `test/test_linked_lists.c`: Simple test
- `CMakeLists.txt`: Build config
