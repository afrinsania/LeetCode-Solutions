class Solution {
    long long getGcd(long long a, long long b) {
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    long long getLcm(long long a, long long b) {
        return (a / getGcd(a, b)) * b;
    }

public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 2; // Any subarray of length 2 is always valid

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            long long currentGcd = nums[i];
            long long currentLcm = nums[i];

            for (int j = i; j < n; j++) {
                prod *= nums[j];
                currentGcd = getGcd(currentGcd, nums[j]);
                currentLcm = getLcm(currentLcm, nums[j]);

                // Max possible LCM for numbers <= 10 is 2520, max GCD is 10
                if (prod > 25200) {
                    break;
                }

                if (prod == currentLcm * currentGcd) {
                    int currentLen = j - i + 1;
                    if (currentLen > maxLen) {
                        maxLen = currentLen;
                    }
                }
            }
        }

        return maxLen;
    }
};