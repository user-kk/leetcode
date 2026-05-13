#include "460.lfu-缓存.cpp"

MYTEST(1) {
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    lfu.get(1);
    lfu.put(3, 3);
    lfu.get(2);
    lfu.get(3);
}
