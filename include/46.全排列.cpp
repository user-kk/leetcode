/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */
#include "common.h"

// @lc code=start
class Solution {
   public:
    void dfs(vector<int>& nums, vector<bool>& visited, vector<int>& t,
             vector<vector<int>>& ret) {
        if (t.size() == nums.size()) {
            ret.push_back(t);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) {
                continue;
            }
            visited[i] = true;
            t.push_back(nums[i]);
            dfs(nums, visited, t, ret);
            t.pop_back();
            visited[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) {
            return {};
        }
        vector<bool> visited(nums.size(), false);
        vector<vector<int>> ret;
        vector<int> t;
        t.reserve(nums.size());

        stack<int> st;

        st.push(0);

        while (!st.empty()) {
            if (st.size() == nums.size() + 1) {
                ret.push_back(t);
                st.pop();
            }
            bool can_go = false;  // 是否还有可走的方向
            int direction = st.top();
            for (; st.top() < nums.size(); st.top()++) {
                if (visited[st.top()]) {
                    continue;
                }
                can_go = true;
                visited[st.top()] = true;
                t.push_back(nums[st.top()]);
                st.top()++;
                st.push(0);
                break;
            }
            if (!can_go) {
                st.pop();
                visited[direction] = false;
                t.pop_back();
            }
        }
        return ret;
    }

    // vector<vector<int>> permute(vector<int>& nums) {
    //     vector<bool> visited(nums.size(), false);
    //     vector<vector<int>> ret;
    //     vector<int> t;
    //     t.reserve(nums.size());
    //     dfs(nums, visited, t, ret);
    //     return ret;
    // }
};
// @lc code=end
