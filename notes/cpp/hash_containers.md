# C++ Maps and Sets: map, unordered_map, set, unordered_set

Origin: [Mistakes Log #1](../mistakes_log.md) (Contains Duplicate: used a hashmap where a hash set was enough).

## Terminology

"Map" is the abstract idea: key → value pairs with unique keys. "Hashmap" means a map implemented with a hash table. A map can also be implemented with a balanced tree.

| Concept | C++ | Java | Python |
| --- | --- | --- | --- |
| Hash map | `std::unordered_map` | `HashMap` | `dict` |
| Tree map (sorted) | `std::map` | `TreeMap` | none built in |
| Hash set | `std::unordered_set` | `HashSet` | `set` |
| Tree set (sorted) | `std::set` | `TreeSet` | none built in |

In C++ people say "hashmap" to mean `unordered_map`.

## Complexity and internals

| | `map` / `set` | `unordered_map` / `unordered_set` |
| --- | --- | --- |
| Backed by | red-black tree | hash table |
| Order | sorted by key | none |
| insert / find / erase | O(log n) | O(1) average, O(n) worst |
| Key needs | `operator<` | hash function and `==` |
| Extras | `lower_bound`, `upper_bound`, min/max via `begin()` / `rbegin()` | none |

The unordered versions are O(1) only on average because of collisions and rehashing.

## Map or set?

- Need data attached to each key (a count, an index)? Use a map.
- Only need "have I seen this key"? Use a set.
- A map whose values are never read is wasted memory and signals the wrong intent.

Default to the unordered versions. Reach for the ordered ones when you need:
- sorted iteration
- nearest-value lookups (`lower_bound` / `upper_bound`)
- min/max
- a key type with no hash, such as `pair<int,int>` or `vector<int>`

## Decision guide

Ask three questions in order.

1. **Set or map: what do I need to remember about each key?**

   | Need | Container |
   | --- | --- |
   | Just "have I seen this?" | set |
   | A count or frequency | map: key → int |
   | Where it was (index, position) | map: key → index |
   | A group of related items | map: key → vector |
   | Both "seen" and some data | map |

   The test: will I ever read a value back? If I only ask "is it in there?", use a set.

   Trigger words:
   - "duplicate", "exists", "visited", "unique", "distinct" usually mean a set
   - "how many times", "frequency", "count" mean a map to int
   - "return the indices", "pair up", "group by" mean a map to an index or list

2. **Ordered or unordered: do I need order?** Default to unordered. Switch to ordered only for sorted iteration, min/max, nearest-key lookups, or a key type with no hash.

3. **Is there a cheaper structure than a hash container?** If keys are small and bounded (26 lowercase letters, 10 digits, a small value range), a plain array indexed by the key beats a hash container. No hashing, no collisions, better constant factor.

```
Need to store data per key?
 ├─ no  → set
 └─ yes → map
Need sorted order / nearest key / min / max?
 ├─ yes → ordered (set / map)
 └─ no  → unordered
Keys tiny and bounded (e.g. 26 letters)?
 └─ yes → consider a plain array instead
```

Sanity check:
- Contains Duplicate: only "seen before?" → unordered set
- Valid Anagram: letter counts → map to int, or array of 26
- Two Sum: index of an earlier value → unordered map
- Longest Consecutive Sequence: membership only → unordered set
- Contains Duplicate III: nearest value in a window → ordered set

## Syntax

```cpp
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

unordered_set<int> s;
s.insert(5);               // returns pair<iterator,bool>; .second is false if already present
s.erase(5);
s.count(5);                // 0 or 1
s.find(5) != s.end();      // membership, the other common idiom
s.size(); s.empty(); s.clear();
for (int x : s) { }        // iteration, arbitrary order

unordered_set<int> t(v.begin(), v.end());   // build from a vector

unordered_map<string,int> m;
m["a"] = 3;                // operator[] INSERTS a default (0) if the key is missing
m["a"]++;                  // common counting idiom
m.count("a");              // check without inserting
m.find("a");               // iterator; it->first, it->second
m.at("a");                 // throws if missing
for (auto& [k, v] : m) { } // structured bindings (C++17)

set<int> o;                // ordered
o.insert(3);
*o.begin();                // smallest
*o.rbegin();               // largest
o.lower_bound(4);          // first element >= 4
o.upper_bound(4);          // first element > 4
```

## Gotchas

- `m[key]` on a missing key creates it. Use `count` or `find` for pure lookups.
- `insert` on a set reports whether the key was new, so a separate lookup first is not always needed.
- Building a set from a range and comparing sizes works, but think about its memory cost and the lack of early exit.
- `multiset` / `multimap` allow duplicate keys.
- `unordered_set<pair<int,int>>` does not compile out of the box (no default hash for `pair`). Provide a custom hash, encode the pair into one value, or use `set`.

## Interview questions to be ready for

- Why is `unordered_set` O(1) only on average?
- How does a hash table handle collisions? (chaining vs open addressing)
- When would you pick `set` over `unordered_set`?
- Can `pair<int,int>` be a key in `unordered_set`? How do you fix it?
- Trade-offs of sorting vs hashing for duplicate detection (time, space, mutating the input).

## Practice ladder

- Valid Anagram, Two Sum (map: value → index)
- Group Anagrams (map: key → list)
- Top K Frequent Elements (map + heap or bucket)
- Longest Consecutive Sequence (set)
- Contains Duplicate II (map or sliding-window set)
- Contains Duplicate III (needs an ordered set; shows when `set` beats `unordered_set`)
