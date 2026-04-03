#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <list>
#include <mutex>

template <typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t capacity);

    bool get(const Key& key, Value& value);
    void put(const Key& key, const Value& value);

    bool contains(const Key& key);
    size_t size() const;
    size_t capacity() const;

private:
    using ListIt = typename std::list<Key>::iterator;

    size_t capacity_;
    mutable std::mutex mtx_;

    std::list<Key> usageList_; // MRU at front
    std::unordered_map<Key, std::pair<Value, ListIt>> cacheMap_;

    void moveToFront(ListIt it);
};

#include "LRUCache.cpp"  // Template implementation

#endif