/*
 * @lc app=leetcode.cn id=380 lang=cpp
 *
 * [380] O(1) 时间插入、删除和获取随机元素
 */
#include <common.h>
#include <vector>
#include <random>
// @lc code=start
class RandomizedSet {
   public:
    RandomizedSet() {}

    bool insert(int val) {
        if (m_.contains(val)) {
            return false;
        }
        v_.push_back(val);
        m_.insert({val, v_.size() - 1});
        return true;
    }

    bool remove(int val) {
        if (auto it = m_.find(val); it != m_.end()) {
            int pos = it->second;
            m_.erase(v_.back());
            std::swap(v_[pos], v_[v_.size() - 1]);
            m_.insert({v_[pos], pos});
            m_.erase(v_[v_.size() - 1]);
            v_.pop_back();
            return true;
        } else {
            return false;
        }
    }

    int getRandom() {
        std::uniform_int_distribution<int> u(0,
                                             static_cast<int>(v_.size()) - 1);
        int random = u(d);
        return v_[random];
    }

   private:
    unordered_map<int, int> m_;
    vector<int> v_;
    std::default_random_engine d;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
// @lc code=end
