/*
1. Two Sum
Easy

You are given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]


Constraints:
2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

/*
3
4 9
2 7 11 15
3 6
3 2 4
2 6
3 3
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

string vec_str(const vector<int> &v)
{
    string s = "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        s += to_string(v[i]);
        if (i + 1 < v.size())
            s += ", ";
    }
    return s + "]";
}

vector<int> twoSum(vector<int> &nums, int target)
{
    int size = nums.size();

    // naive approach
    // for (int i = 0; i < size; i++)
    //     for (int j = i + 1; j < size; j++)
    //         if (nums[i] + nums[j] == target)
    //             return {i, j};

    // hashmap
    unordered_map<int, int> mp;
    for (int i = 0; i < size; i++)
    {
        if (mp.find(target - nums[i])!=mp.end())
            return {mp.find(target - nums[i])->second,i };
        mp[nums[i]] = i;
    }

    return {-1, -1};
}

int main()
{
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        int n, target;
        cin >> n >> target;
        vector<int> nums(n);
        for (auto &a : nums)
            cin >> a;

        vector<int> ans = twoSum(nums, target);

        cout << "Case " << tc << "\n";
        cout << "  nums   = " << vec_str(nums) << "\n";
        cout << "  target = " << target << "\n";
        cout << "  output = " << vec_str(ans) << "\n\n";
    }
}