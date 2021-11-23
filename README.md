# String processing Algorithms
## Copyright 2021 Adina-Maria Amzarescu 321CA

This is a project that tests 2 string processing algorithms, **Rabin-Karp** and **Knuth-Morris-Pratt**.

_________________________________________________________________________________________________________

### `` Rabin-Karp - approximate match``

It checks the pattern by moving window one by one, but without checking all characters for all cases,
it finds the hash value. When the hash value is matched, then only it tries to check each character.
This procedure makes the algorithm more efficient.

The time complexity is O(m+n), but for the worst case, it is O(mn).

* Source of inspiration: https://github.com/Chediak/ds-in-c/blob/main/rabin-karp.c

  I changed the function to match my tests, I added the out file in the header and also
  added the "ok" variable to check if there is at least one pattern.
  
_________________________________________________________________________________________________________

### ``Knuth-Morris-Prat - exact match``

It is an algorithm which checks the characters from left to right. When a pattern has a sub-pattern
appears more than one in the sub-pattern, it uses that property to improve the time complexity.

The time complexity of KMP is O(n).

* Source of inspiration: https://www.geeksforgeeks.org/c-program-for-kmp-algorithm-for-pattern-searching-2/

  I changed the function to match my tests, I added the out file in the header and also
  added the "ok" variable to check if there is at least one pattern.
 
_________________________________________________________________________________________________________
