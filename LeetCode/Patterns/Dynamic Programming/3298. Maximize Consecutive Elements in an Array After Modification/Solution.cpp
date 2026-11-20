#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    int maxSelectedElements(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        
        // dp[x] stores the max length of a consecutive sequence ending at value x
        std::unordered_map<int, int> dp;
        int maxLen = 0;
        
        for (int num : nums) {
            // Option 1: Increase num by 1 (becomes num + 1)
            // Must be updated before Option 2 so it doesn't chain off the same element
            dp[num + 1] = std::max(dp[num + 1], dp[num] + 1);
            
            // Option 2: Keep num as is
            dp[num] = std::max(dp[num], dp[num - 1] + 1);
            
            maxLen = std::max({maxLen, dp[num], dp[num + 1]});
        }
        
        return maxLen;
    }
};