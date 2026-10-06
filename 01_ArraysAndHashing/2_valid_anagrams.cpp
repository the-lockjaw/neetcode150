/*
Valid Anagram
Easy

Given two strings s and t, return true if the two strings are anagrams of each other, otherwise return false.

Two strings are anagrams if they contain the same characters, with each character appearing the same number of times, regardless of order.


Example 1:
Input: s = "racecar", t = "carrace"
Output: true

Example 2:
Input: s = "jar", t = "jam"
Output: false

Example 3:
Input: s = "x", t = "x"
Output: true

Constraints:
1 <= s.length, t.length <= 5 * 10^4
s and t consist of lowercase English letters.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// the approach that comes first in my mind : using a map
bool isAnagram(string s, string t)
{
    if (s.length() != t.length())
        return false;

    unordered_map<char, int> mp;
    int l = s.length();

    for (int i = 0; i < l; i++)
        mp[s[i]]++;

    for (int i = 0; i < l; i++)
        mp[t[i]]--;

    for (auto a : mp)
        if (a.second != 0)
            return false;

    return true;
}

// better complexity using just an array
bool isAnagramArray(string s, string t)
{
    if (s.length() != t.length())
        return false;

    vector<int> mp(26);
    int l = s.length();

    for (int i = 0; i < l; i++)
        mp[s[i] - 'a']++;

    for (int i = 0; i < l; i++)
        mp[t[i] - 'a']--;

    for (auto a : mp)
        if (a != 0)
            return false;

    return true;
}

// sorting
bool isAnagramSort(string s, string t)
{
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    if (s == t)
        return true;
    else
        return false;
}

/*
4
racecar
carrace
jar
jam
x
x
a
ab
*/

int main()
{
    int tests;
    cin >> tests;
    while (tests--)
    {
        string s, t;
        cin >> s >> t;
        bool ans = isAnagramSort(s, t);
        if (ans)
            cout << "true";
        else
            cout << "false";
        cout << "\n";
    }
}