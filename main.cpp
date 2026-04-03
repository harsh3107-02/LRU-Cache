#include <iostream>
#include "LRUCache.h"

int main() {
    LRUCache<int, std::string> cache(3);

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    std::string value;

    if (cache.get(2, value)) {
        std::cout << "Key 2: " << value << std::endl;
    }

    cache.put(4, "four"); // evicts key 1

    if (!cache.get(1, value)) {
        std::cout << "Key 1 evicted\n";
    }

    if (cache.get(3, value)) {
        std::cout << "Key 3: " << value << std::endl;
    }

    return 0;
}