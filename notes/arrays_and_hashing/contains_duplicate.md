# Contains Duplicate: approaches and review takeaways

Origin: [Mistakes Log #1 and #2](../mistakes_log.md).

## Approach comparison

| Approach | Time | Space | Mutates input | Early exit |
| --- | --- | --- | --- | --- |
| Brute force (all pairs) | O(n²) | O(1) | no | yes |
| Sort, then compare neighbours | O(n log n) | O(1) to O(log n) depending on the sort | yes | only after the full sort |
| Hash set, check as you go | O(n) average | O(n) | no | yes, at the first repeat |
| Hash set built from the whole array, compare sizes | O(n) average | O(n) | no | no, always builds everything |

Which to pick:
- Memory tight and mutating the input is allowed: sort.
- Speed matters: hash set with early exit.
- The size-comparison version is short but never exits early and always pays full memory.

## Review takeaways

- Keep `int size = nums.size()`: with an unsigned `size_t`, `size - 1` on an empty array underflows to a huge number.
- Do the "fewer than 2 elements" check before sorting; sorting first is wasted work.
- With a set, `insert` already reports whether the key was new, so a separate `count` plus `insert` does two hash lookups where one is enough.
- A set could `reserve` its expected size up front to avoid rehashing.
- Name functions and variables after what they call. A variable called `ansBF` that holds the hash set result is misleading when swapping approaches.
- The constraints allow an empty array (length 0). Add it to the test input, along with a single element and all-equal elements.
- When comparing approaches in one file, run all of them on the same input and assert they agree.
- Compiled binaries in the repo are clutter. Consider ignoring them with `.gitignore`.

## Pattern

"Have I seen this before?" with a set. The same idea shows up in:
- Two Sum (map: value → index)
- Longest Consecutive Sequence
- Valid Sudoku
- Longest Substring Without Repeating Characters (sliding window plus a set)

## Interview follow-ups

- What if the input is a stream and you can't store it all? (hash set grows without bound; mention Bloom filters as a space-saving, approximate answer)
- What if memory is very limited? (sort in place, accept O(n log n))
- Why is the hash set O(1) only on average? (collisions; see [C++ Maps and Sets](../cpp/hash_containers.md))
- Does the value range (±10⁹) allow a plain array instead of a hash set? (No: the range is far larger than n, so a direct-address table would be huge.)
