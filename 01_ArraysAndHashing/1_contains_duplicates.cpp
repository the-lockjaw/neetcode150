/*
Contains Duplicate
Easy

Given an integer array nums, return true if any value appears more than once in the array, otherwise return false.

Example 1:
Input: nums = [1, 2, 3, 3]
Output: true

Example 2:
Input: nums = [1, 2, 3, 4]
Output: false

Constraints:
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
*/

/*
2
4
1 2 3 3
4
1 2 3 4
*/
#include <bits/stdc++.h>
using namespace std;

// brute force
// -------------------------------
bool hasDuplicateBF(vector<int> &nums)
{
    int size = nums.size();
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (nums[i] == nums[j])
                return true;
    return false;
}

// sorting
// -------------------------------
bool hasDuplicateSort(vector<int> &nums)
{
    int size = nums.size();
    sort(nums.begin(), nums.end());
    if (nums.size() < 2)
        return false;
    for (int i = 0; i < size - 1; i++)
        if (nums[i] == nums[i + 1])
            return true;
    return false;
}

// hash set
// -------------------------------
bool hashSet(vector<int> &nums)
{
    unordered_set<int> seen;
    for (int num : nums)
    {
        if (seen.count(num))
            return true;
        seen.insert(num);
    }
    return false;
}

// hash set length
// -------------------------------
bool hashSetLength(vector<int> &nums)
{
    return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> q(n);
        for (auto &a : q)
            cin >> a;
        bool ansBF = hashSet(q);
        if (ansBF)
            cout << "true";
        else
            cout << "false";
        cout << "\n";
    }
    return 0;
}