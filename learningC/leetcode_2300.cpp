#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        std::sort(potions.begin(), potions.end());
        vector<int> res;
        for (int i = 0; i < spells.size(); i++) {
            int n = spells[i];
            if (n == 0) {
                res.push_back(0);
                continue;
            }

            long long need = (success + n - 1) / n - 1;
            res.push_back(potions.size() - (upper_bound(potions.begin(), potions.end(), need) - potions.begin()));
            
        }
        return res;
    }
};

int main() {
    Solution sol;

    // Test 1
    vector<int> spells1{5,1,3};
    vector<int> potions1{1,2,3,4,5};
    long long success1 = 7;
    auto res1 = sol.successfulPairs(spells1, potions1, success1);
    std::cout << "Test1 result: ";
    for (int v : res1) std::cout << v << ' ';
    std::cout << "\nExpected: 4 0 3\n\n";

    // Test 2 (额外测试)
    vector<int> spells2{10,2,0};
    vector<int> potions2{1,2,5,10};
    long long success2 = 20;
    auto res2 = sol.successfulPairs(spells2, potions2, success2);
    std::cout << "Test2 result: ";
    for (int v : res2) std::cout << v << ' ';
    std::cout << "\nExpected: 2 1 0\n";

    return 0;
}

