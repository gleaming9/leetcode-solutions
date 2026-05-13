class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indexByValue;

        for (int i = 0; i < nums.size(); i++) {
            int a = 0;
            int need = target - nums[i];

            if (indexByValue.find(need) != indexByValue.end()) {
                return {indexByValue[need], i};
            }

            indexByValue[nums[i]] = i;
        }

        return {};
    }
};
