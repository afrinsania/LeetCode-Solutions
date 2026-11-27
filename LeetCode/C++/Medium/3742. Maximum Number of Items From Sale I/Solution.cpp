class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int max_factor = 1500;
        vector<int> freq(max_factor + 1, 0);
        int min_price = 1e9;
        
        for (auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, item[1]);
        }
        
        vector<int> div_count(max_factor + 1, 0);
        for (int f = 1; f <= max_factor; ++f) {
            if (freq[f] == 0) continue;
            for (int mult = f; mult <= max_factor; mult += f) {
                div_count[f] += freq[mult];
            }
        }
        
        vector<int> dp(budget + 1, -1e9);
        dp[0] = 0;
        
        for (auto& item : items) {
            int f = item[0];
            int p = item[1];
            int val = div_count[f];
            
            for (int b = budget; b >= p; --b) {
                if (dp[b - p] != -1e9) {
                    dp[b] = max(dp[b], dp[b - p] + val);
                }
            }
        }
        
        int ans = 0;
        for (int b = 0; b <= budget; ++b) {
            if (dp[b] != -1e9) {
                ans = max(ans, dp[b] + (budget - b) / min_price);
            }
        }
        
        return ans;
    }
};