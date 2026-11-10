#include "lru_cache.h"
#include <cassert>

int main() {
    LRUCache<int, int> cache(2);

    int value = 0;

    // 测试 put
    assert(cache.put(1, 100));
    assert(cache.put(2, 200));

    // 测试 get
    assert(cache.get(1, &value));
    assert(value == 100);

    // 测试更新已有 Key
    assert(cache.put(1, 150));
    assert(cache.get(1, &value));
    assert(value == 150);

    // 测试容量淘汰
    assert(cache.put(3, 300));
    assert(!cache.get(2, &value));

    // 测试 remove
    assert(cache.remove(1));
    assert(!cache.get(1, &value));

    // 测试删除不存在的 Key
    assert(!cache.remove(1));

    // 测试 size 和 empty
    assert(cache.size() == 1);
    assert(cache.remove(3));
    assert(cache.empty());

    //测试容量为0
    {
	LRUCache<int, int> zero_cache(0);
	bool inserted = zero_cache.put(1, 200);
	assert(!inserted);

	assert(zero_cache.size() == 0);

	assert(zero_cache.empty());
    }

    //测试不存在的key和空指针
    {
	LRUCache<int, int> missing_cache(2);
	int value = 0;

	// 测试查询不存在的 Key
	bool found = missing_cache.get(5, &value);
	assert(!found);

	// 测试删除不存在的 Key
	bool removed = missing_cache.remove(5);
	assert(!removed);

	// 插入一个 Key
	bool inserted = missing_cache.put(5, 100);
	assert(inserted);

	// 测试空指针
	bool null_result = missing_cache.get(5, nullptr);
	assert(!null_result);

	// 确认空指针操作没有破坏缓存
	bool found_again = missing_cache.get(5, &value);
	assert(found_again);
	assert(value == 100);
    }
    // 测试 get 是否更新 LRU 顺序
   {
	LRUCache<int, int> cache(2);
	int value = 0;

	// 1. 插入两个元素
	bool p1 = cache.put(1, 100);
	bool p2 = cache.put(2, 200);
	assert(p1 && p2);

	// 2. 访问 Key=1，使其变成最近使用
	bool found = cache.get(1, &value);
	assert(found);
	assert(value == 100);

	// 3. 插入 Key=3，触发容量淘汰
	bool p3 = cache.put(3, 300);
	assert(p3);

	// 4. 验证 Key=2 已经被淘汰
	bool found2 = cache.get(2, &value);
	assert(!found2);

	// 5. 验证 Key=1 和 Key=3 仍然存在
	bool found1 = cache.get(1, &value);
	assert(found1 && value == 100);

	bool found3 = cache.get(3, &value);
	assert(found3 && value == 300);
    }
    // 测试 put 更新已有 key 是否刷新顺序
    {
	LRUCache<int, int> cache(2);
	int value = 0;

	//插入两个元素
	bool p1 = cache.put(1, 100);
	bool p2 = cache.put(2, 200);
	assert(p1 && p2);

	//刷新已有的 key=1 的值
	bool p = cache.put(1, 300);
	assert(p);

	//插入 key=3 触发容量淘汰
	bool p3 = cache.put(3,300);
	assert(p3);

	//验证是 key=2 被淘汰
	bool found2 = cache.get(2, &value);
	assert(!found2);

	// 验证 Key=1 仍然存在，且 Value 已更新
	bool found1 = cache.get(1, &value);
	assert(found1);
	assert(value == 300);

	//验证 Key=3 仍然存在
	bool found3 = cache.get(3, &value);
	assert(found3);
	assert(value == 300);
    }

    return 0;
}
