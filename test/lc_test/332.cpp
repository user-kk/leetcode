#include "332.重新安排行程.cpp"

MYTEST(1) {
    Solution s;
    auto v = createVector<string>(
        {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}});
    s.findItinerary(v);
}
