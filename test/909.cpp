#include "909.蛇梯棋.cpp"

MYTEST(1) {
    Solution s;
    auto v =
        "[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]"_vec2;
    s.snakesAndLadders(v);
}

MYTEST(2) {
    Solution s;
    auto v = "[[1,1,-1],[1,1,1],[-1,1,1]]"_vec2;
    s.snakesAndLadders(v);
}
