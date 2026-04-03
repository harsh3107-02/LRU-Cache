#ifndef LRU_CACHE_CPP
#define LRU_CACHE_CPP

#include "LRUCache.h"

template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t capacity) : capacity_(capacity) {}

template <typename Key, typename Value>
void LRUCache<Key, Value>::moveToFront(ListIt it) {
    usageList_.splice(usageList_.begin(), usageList_, it);
}

template <typename Key, typename Value>
bool LRUCache<Key, Value>::get(const Key& key, Value& value) {
    std::lock_guard<std::mutex> lock(mtx_);

    auto it = cacheMap_.find(key);
    if (it == cacheMap_.end()) return false;

    moveToFront(it->second.second);
    value = it->second.first;
    return true;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::put(const Key& key, const Value& value) {
    std::lock_guard<std::mutex> lock(mtx_);

    auto it = cacheMap_.find(key);

    if (it != cacheMap_.end()) {
        it->second.first = value;
        moveToFront(it->second.second);
        return;
    }

    if (cacheMap_.size() >= capacity_) {
        Key lruKey = usageList_.back();
        usageList_.pop_back();
        cacheMap_.erase(lruKey);
    }

    usageList_.push_front(key);
    cacheMap_[key] = {value, usageList_.begin()};
}

template <typename Key, typename Value>
bool LRUCache<Key, Value>::contains(const Key& key) {
    std::lock_guard<std::mutex> lock(mtx_);
    return cacheMap_.find(key) != cacheMap_.end();
}

template <typename Key, typename Value>
size_t LRUCache<Key, Value>::size() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return cacheMap_.size();
}

template <typename Key, typename Value>
size_t LRUCache<Key, Value>::capacity() const {
    return capacity_;
}

#endif