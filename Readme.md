# Thread-safe LRU Cache in C++

## Overview
This project implements a thread-safe Least Recently Used (LRU) cache in C++17.

The cache supports O(1) `get` and `put` operations using a combination of:
- Hash map (`std::unordered_map`)
- Doubly linked list (`std::list`)

Thread safety is ensured using `std::mutex`.

---

## Features
- O(1) lookup and insertion
- Automatic eviction of least recently used elements
- Thread-safe operations
- Clean and modular design

---

## Design
- Most recently used (MRU) items are stored at the front
- Least recently used (LRU) items are evicted from the back
- Hash map provides fast access
- Doubly linked list maintains usage order

---

## Complexity
| Operation | Time |
|----------|------|
| get      | O(1) |
| put      | O(1) |

---

## Build & Run

```bash
g++ -std=c++17 -pthread main.cpp -o lru
./lru