#pragma once

#include<cstddef>
#include<list>
#include<unordered_map>
#include<utility>

template<typename K, typename V>
class LRUCache{
private:
    //类型别名
    using KVPair = std::pair<K, V>;
    using List = std::list<KVPair>;
    using Iterator = typename List::iterator;
    using Map = std::unordered_map<K, Iterator>;

    //成员变量
    std::size_t capacity_;
    List items_;
    Map index_;

public:
    //构造函数
    explicit LRUCache(std::size_t capacity): capacity_(capacity){}

    //成员函数
    bool put(const K& key, V value){
	if(capacity_ == 0){
	    return false;
	}
	auto it = index_.find(key);
	if(it != index_.end()){
	    it->second->second = std::move(value);
	    items_.splice(items_.begin(), items_, it->second);
	    return true;
	}
	items_.emplace_front(key, std::move(value));
	index_.emplace(key, items_.begin());
	if(items_.size() > capacity_){
	    auto old_key = items_.back().first;
	    index_.erase(old_key);
	    items_.pop_back();
	}
	return true;
}

    bool get(const K& key, V* value){
	if(value == nullptr){
	    return false;
	}
	auto it = index_.find(key);
	if(it == index_.end()){
	    return false;
	}
	*value = it->second->second;
	items_.splice(items_.begin(), items_, it->second);
	return true;
}

    bool remove(const K& key){
	auto it = index_.find(key);
	if(it == index_.end()){
	    return false;
	}
	items_.erase(it->second);
	index_.erase(it);
	return true;
}

    std::size_t size() const noexcept{
        return items_.size();
    }

    bool empty() const noexcept{
        return items_.empty();
    }
};
