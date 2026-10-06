# Mistakes Log

Newest entries at the bottom. One entry per problem where I missed something, with a link to the note that fixes the gap.

| # | Date | Problem | What I missed | Note |
| --- | --- | --- | --- | --- |
| 1 | 2026-10-05 | 1. Contains Duplicate | Used a hashmap where a hash set was enough. Did not know the map vs set and ordered vs unordered distinctions or the C++ syntax. | [C++ Maps and Sets](cpp/hash_containers.md) |
| 2 | 2026-10-05 | 1. Contains Duplicate (code review) | Minor: misleading variable name (`ansBF` calls the hash set version), no empty-input test case, two lookups where `insert`'s return value suffices, sort-first before the size check. | [Contains Duplicate](arrays_and_hashing/contains_duplicate.md) |
| 3 | 2026-10-06 | 2. Valid Anagram | Forgot to compare the two string lengths before building the hash map (free O(1) early exit). | [Valid Anagram](arrays_and_hashing/valid_anagram.md) |

## Entry template

When adding a row: date, problem number and name, the specific gap (not "got it wrong"), and a link to a note. If no note exists yet, write one under `notes/<topic>/`.
