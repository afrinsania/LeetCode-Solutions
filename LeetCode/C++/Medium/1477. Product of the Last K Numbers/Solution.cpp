class ProductOfNumbers {
private:
    vector<int> prefix;

public:
    ProductOfNumbers() {
        prefix = {1};
    }
    
    void add(int num) {
        if (num == 0) {
            prefix = {1}; // Reset because any product including this 0 will be 0
        } else {
            prefix.push_back(prefix.back() * num);
        }
    }
    
    int getProduct(int k) {
        int n = prefix.size() - 1;
        if (k > n) {
            return 0; // A zero was encountered within the last k elements
        }
        return prefix[n] / prefix[n - k];
    }
};