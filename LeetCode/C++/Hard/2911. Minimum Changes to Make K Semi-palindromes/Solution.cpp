class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        const int INF = 1e9;
        
        // Precompute divisors for every possible substring length (2 to n)
        vector<vector<int>> divs(n + 1);
        for (int len = 2; len <= n; ++len) {
            for (int d = 1; d < len; ++d) {
                if (len % d == 0) {
                    divs[len].push_back(d);
                }
            }
        }
        
        // cost[i][j]: min changes to make substring s[i..j] a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                for (int d : divs[len]) {
                    int current_changes = 0;
                    for (int offset = 0; offset < d; ++offset) {
                        int left = i + offset;
                        int right = j - (d - 1 - offset);
                        while (left < right) {
                            if (s[left] != s[right]) {
                                current_changes++;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    if (current_changes < cost[i][j]) {
                        cost[i][j] = current_changes;
                    }
                }
            }
        }
        
        // dp[i][p]: min changes to partition prefix s[0..i-1] into p semi-palindromes
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;
        
        for (int p = 1; p <= k; ++p) {
            for (int i = 2 * p; i <= n; ++i) {
                for (int m = 2 * (p - 1); m <= i - 2; ++m) {
                    if (dp[m][p - 1] != INF) {
                        int candidate = dp[m][p - 1] + cost[m][i - 1];
                        if (candidate < dp[i][p]) {
                            dp[i][p] = candidate;
                        }
                    }
                }
            }
        }
        
        return dp[n][k];
    }
};