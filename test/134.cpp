#include "134.加油站.cpp"

MYTEST(1) {
    Solution s;
    auto gas = "[5,1,2,3,4]"_vec;
    auto cost = "[4,4,1,5,1]"_vec;
    s.canCompleteCircuit(gas, cost);
}
