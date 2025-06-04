#include <memory>
#include <memory_resource>
#include <thread>
#include <utility>
#include <vector>
#include "common.h"
#include "my/monotonic_buffer_resource.h"
#include "my/unique_ptr.h"
#include "my/shared_ptr.h"
#include "my/memmove.h"
#include <spdlog/spdlog.h>

using My::SharedPtr;
using My::WeakPtr;

// 基类
class Base {
   public:
    virtual ~Base() { SPDLOG_DEBUG("Base destructor called"); }

   private:
    int a = 1;
};

// 派生类
class Derived : public Base {
   public:
    ~Derived() override { SPDLOG_DEBUG("Derived destructor called"); }

   private:
    int b = 2;
};

MYTEST(1) {
    My::UniquePtr<Base> p1(new Derived());
    SPDLOG_DEBUG("p1 is created");

    My::UniquePtr<Base> p2(std::move(p1));
    SPDLOG_DEBUG("p2 is created");

    if (!p1) {
        SPDLOG_DEBUG("p1 is null after move");
    }

    p2.reset(new Derived());
    SPDLOG_DEBUG("p2 is reset with a new Derived object");

    std::shared_ptr<int> kk;
}

MYTEST(2) { My::UniquePtr<int[]> p1(new int[3]); }

// 测试 SharedPtr 的基本功能
TEST(SharedPtrTest, BasicUsage) {
    SharedPtr<int> sp1(new int(42));
    EXPECT_EQ(*sp1, 42);
    EXPECT_EQ(sp1.use_count(), 1);

    {
        SharedPtr<int> sp2 = sp1;
        EXPECT_EQ(sp1.use_count(), 2);
        EXPECT_EQ(sp2.use_count(), 2);
        EXPECT_EQ(*sp2, 42);
    }

    EXPECT_EQ(sp1.use_count(), 1);
}

// 测试 SharedPtr 的移动语义
TEST(SharedPtrTest, MoveSemantics) {
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2(std::move(sp1));

    EXPECT_EQ(sp1.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 1);
    EXPECT_EQ(*sp2, 42);
}

// 测试 SharedPtr 的自定义删除器
TEST(SharedPtrTest, CustomDeleter) {
    int* ptr = new int(42);
    bool deleted = false;
    auto deleter = [&deleted](int* p) {
        deleted = true;
        delete p;
    };

    {
        SharedPtr<int> sp1(ptr, deleter);
        EXPECT_EQ(sp1.use_count(), 1);
        EXPECT_EQ(*sp1, 42);
    }

    EXPECT_TRUE(deleted);
}

// 测试 WeakPtr 的基本功能
TEST(WeakPtrTest, BasicUsage) {
    SharedPtr<int> sp1(new int(42));
    WeakPtr<int> wp1(sp1);

    EXPECT_EQ(wp1.use_count(), 1);

    {
        SharedPtr<int> sp2 = wp1.lock();
        EXPECT_EQ(sp2.use_count(), 2);
        EXPECT_EQ(*sp2, 42);
    }

    EXPECT_EQ(wp1.use_count(), 1);
}

// 测试 WeakPtr 的线程安全性
TEST(WeakPtrTest, ThreadSafety) {
    SharedPtr<int> sp1(new int(42));
    WeakPtr<int> wp1(sp1);

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&wp1]() {
            for (int j = 0; j < 100; ++j) {
                SharedPtr<int> sp = wp1.lock();
                if (sp) {
                    EXPECT_EQ(*sp, 42);
                }
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }
}

// 测试 SharedPtr 的 reset 方法
TEST(SharedPtrTest, ResetMethod) {
    SharedPtr<int> sp1(new int(42));
    EXPECT_EQ(*sp1, 42);
    EXPECT_EQ(sp1.use_count(), 1);

    sp1.reset(new int(100));
    EXPECT_EQ(*sp1, 100);
    EXPECT_EQ(sp1.use_count(), 1);

    sp1.reset();
    EXPECT_EQ(sp1.get(), nullptr);
    EXPECT_EQ(sp1.use_count(), 0);
}

TEST(MemResTest, pmrTest) {
    My::MonotonicBufferResource res;
    pmr::vector<int> v(&res);
    v.assign({1, 2, 3, 4, 5});
}

namespace Nodes {
thread_local My::MonotonicBufferResource res;
struct A;
auto node_deleter = [](A* p) { res.deconstruct(p); };
using NodeUniquePtr = std::unique_ptr<A, decltype(node_deleter)>;
struct A {
    explicit A(int v = 0) : children(&res), a(v) {}
    virtual ~A() { SPDLOG_DEBUG("destruct A ,v:{}", a); }
    int a = 0;
    std::pmr::vector<NodeUniquePtr> children;
};

struct B : A {
    explicit B(int v = 0) : b(v) {}
    virtual ~B() { SPDLOG_DEBUG("destruct B,v:{}", b); }
    int b;
};

struct C : A {
    explicit C(int v = 0) : c(v) {}
    virtual ~C() { SPDLOG_DEBUG("destruct B,v:{}", c); }
    int c;
};
}  // namespace Nodes

TEST(MemResTest, pmrTest2) {
    using namespace Nodes;
    My::MonotonicBufferResource& res = Nodes::res;
    A* a = res.new_as_row_ptr<A>(1);
    B* b = res.new_as_row_ptr<B>(2);
    b->children.push_back(NodeUniquePtr(res.new_as_row_ptr<C>(3)));
    a->children.push_back(NodeUniquePtr(b));
    a->children.push_back(NodeUniquePtr(res.new_as_row_ptr<C>(4)));
    res.deconstruct(a);
}

struct D {
    ~D() { SPDLOG_DEBUG("destruct D"); }
};

TEST(MemResTest, pmrTest3) {
    My::MonotonicBufferResource res;
    auto p = res.new_as<D>();

    std::atomic<int> k2;
}

// 测试无重叠
TEST(MemmoveTest, NoOverlap) {
    char buffer[50] = "Hello, World!";
    My::memmove(buffer + 13, buffer, 5);
    EXPECT_STREQ(buffer, "Hello, World!Hello");
}

// 测试部分重叠，源在目标前面
TEST(MemmoveTest, PartialOverlapSrcBeforeDest) {
    char buffer[50] = "abcdefghij";
    My::memmove(buffer + 3, buffer, 7);
    EXPECT_STREQ(buffer, "abcabcdefg");
}

// 测试部分重叠，源在目标后面
TEST(MemmoveTest, PartialOverlapSrcAfterDest) {
    char buffer[50] = "abcdefghij";
    My::memmove(buffer, buffer + 3, 7);
    EXPECT_STREQ(buffer, "defghijhij");
}

// 测试完全重叠
TEST(MemmoveTest, FullOverlap) {
    char buffer[50] = "abcdefghij";
    My::memmove(buffer, buffer, 10);
    EXPECT_STREQ(buffer, "abcdefghij");
}

// 测试零长度
TEST(MemmoveTest, ZeroLength) {
    char buffer[50] = "abcdefghij";
    My::memmove(buffer + 3, buffer, 0);
    EXPECT_STREQ(buffer, "abcdefghij");
}

struct A {
    alignas(16) int a;
    void kk(int a) {}
};

struct B : public A {
    int kk(string a) { return 0; }
};

TEST(HiddenTest, hidden) {
    B k;
    // k.kk(1); 报错
    std::unordered_map<int, int> k2;
    deque<int> k3;
    k3[1] = 100;
}