# Valid Anagram: approaches and review takeaways

Origin: [Mistakes Log #3](../mistakes_log.md).

## The gap

Forgot the length check before building the frequency map. If `s.length() != t.length()` the answer is already false, so every later step is wasted work, and in some variants it is also a correctness bug (see below).

## Why the length check matters

- It is an O(1) early exit. `length()` on a string is constant time.
- It is a correctness guard in some variants. If you only count `s` and then decrement for `t` while checking "any count < 0", a longer `s` leaves positive leftovers you must still scan for. A longer `t` goes negative. Different variants need different final checks, and the length check makes the reasoning trivial: equal lengths plus "no count goes negative" implies all counts are zero.
- General habit: before any work, ask "what cheap property must hold for the answer to be true?" (length, parity, sum, set size) and test it first.

## Correctness argument

- Let count_s(c) and count_t(c) be the occurrences of character c in each string. Anagram ⟺ count_s(c) = count_t(c) for every c.
- After incrementing for s and decrementing for t, mp[c] = count_s(c) − count_t(c). So anagram ⟺ every entry is 0. This is an "if and only if", so the check is right in both directions.
- Characters only in t get created as −1 by the decrement, so the final scan sees them. Characters in neither string have both counts 0.
- Sum over all c of mp[c] = |s| − |t|. If the lengths differ, some entry must be nonzero, so a version that loops over each string's own length returns false anyway and the length check is just an optimisation.
- In a version that shares one `l = s.length()` across both loops, the length check is required for correctness: a longer t has an unread tail (wrong true), a shorter t reads out of bounds.
- With equal lengths the sum is 0, so if no entry ever goes negative during the decrement pass, no entry can be positive either. That is why the final scan can be dropped when you exit early on a negative count.

## Approach comparison

| Approach | Time | Space | Notes |
| --- | --- | --- | --- |
| Sort both, compare | O(n log n) | O(1) to O(n) depending on the sort and whether you copy | Short. Length check still saves two sorts on mismatch. |
| Hash map of counts | O(n) average | O(k), k = distinct characters | Works for any alphabet, including Unicode. |
| Fixed array of 26 counts | O(n) | O(1) | Only valid because the constraints say lowercase a to z. |

Which to pick:
- Constraints say lowercase English letters: the 26-slot array. No hashing, better cache behaviour, truly O(1) space.
- Alphabet is unbounded or unknown (Unicode): the hash map.
- Memory is extremely tight and mutating the input is fine: sort.

## Review takeaways

- Put the length check first in every variant, including the sorting one.
- A single count array can be used for both strings: increment for `s`, decrement for `t`. Equal lengths means the two passes can share one loop.
- Early exit: while decrementing for `t`, if a count drops below zero you can return false immediately, since `t` has a character `s` lacks.
- Iterating a container with `for (auto a : x)` copies each element. For small types it does not matter, but `const auto&` is the habit to build.
- In `main`, the inner `string t` shadows the outer `int t` (the test-case counter). It compiles, but rename one so the loop condition and the strings are not confusable.
- Test cases worth adding: different lengths (`a`, `ab`, already there), identical strings, same letters with different counts (`aab` vs `abb`), and the maximum length.

## Pattern

"Compare two multisets" by counting. The same idea shows up in:
- Group Anagrams (the sorted string or the 26-count tuple becomes the hash key)
- Ransom Note and Permutation in String (counting plus a sliding window)
- Find All Anagrams in a String

## Interview follow-ups

- What if the strings contain Unicode? (Use a hash map, not a fixed array; mention that "character" may mean code point or grapheme.)
- What if you must compare one string against millions of candidates? (Precompute a canonical key per string, either the sorted form or the count signature, and hash it. This is Group Anagrams.)
- Can you do it in O(1) extra space without sorting? (Yes with the fixed 26-slot array, because the alphabet is bounded.)
- Why is the hash map version O(n) only on average? (See [C++ Maps and Sets](../cpp/hash_containers.md).)
