#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

class Solution {
    struct PairHash {
        size_t operator()(const pair<uint64_t, uint64_t>& p) const {
            return p.first ^ (p.second * 0x9e3779b97f4a7c15ULL);
        }
    };

    bool hasUniqueSubarray(const vector<int>& nums, int len,
                           const vector<uint64_t>& h1, const vector<uint64_t>& p1, uint64_t m1,
                           const vector<uint64_t>& h2, const vector<uint64_t>& p2, uint64_t m2) {
        int n = nums.size();
        unordered_map<pair<uint64_t, uint64_t>, int, PairHash> freq;
        freq.reserve(n - len + 1);

        for (int i = 0; i <= n - len; ++i) {
            uint64_t sub1 = (h1[i + len] + m1 - (h1[i] * p1[len]) % m1) % m1;
            uint64_t sub2 = (h2[i + len] + m2 - (h2[i] * p2[len]) % m2) % m2;
            freq[{sub1, sub2}]++;
        }

        for (const auto& entry : freq) {
            if (entry.second == 1) {
                return true;
            }
        }
        return false;
    }

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        
        // Double hash parameters to avoid collisions
        const uint64_t b1 = 1315423911ULL, m1 = 1000000007ULL;
        const uint64_t b2 = 146527ULL,     m2 = 1000000009ULL;

        vector<uint64_t> h1(n + 1, 0), p1(n + 1, 1);
        vector<uint64_t> h2(n + 1, 0), p2(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            // Add 1 to nums[i] so values are strictly positive
            uint64_t val = static_cast<uint64_t>(nums[i]) + 1;
            h1[i + 1] = (h1[i] * b1 + val) % m1;
            p1[i + 1] = (p1[i] * b1) % m1;

            h2[i + 1] = (h2[i] * b2 + val) % m2;
            p2[i + 1] = (p2[i] * b2) % m2;
        }

        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueSubarray(nums, mid, h1, p1, m1, h2, p2, m2)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};