# String processing Algorithms
## Copyright 2021 Adina-Maria Amzarescu 321CA

This is a project that tests 2 string processing algorithms, **Rabin-Karp** and **Knuth-Morris-Pratt**.
The algorithms were tested in C language.

______________________________________________________________________________________________________________

### `` Rabin-Karp - approximate match``

It checks the pattern by moving window one by one, but without checking all characters for all cases,
it finds the hash value. When the hash value is matched, then only it tries to check each character.
This procedure makes the algorithm more efficient.

The time complexity is O(m+n), but for the worst case, it is O(mn).

* Source of inspiration: https://github.com/Chediak/ds-in-c/blob/main/rabin-karp.c

  I changed the function to match my tests, I added the out file in the header and also
  added the "ok" variable to check if there is at least one pattern.
  
______________________________________________________________________________________________________________

### ``Knuth-Morris-Prat - exact match``

It is an algorithm which checks the characters from left to right. When a pattern has a sub-pattern
appears more than one in the sub-pattern, it uses that property to improve the time complexity.

The time complexity of KMP is O(n).

* Source of inspiration: https://www.geeksforgeeks.org/c-program-for-kmp-algorithm-for-pattern-searching-2/

  I changed the function to match my tests, I added the out file in the header and also
  added the "ok" variable to check if there is at least one pattern.
 
______________________________________________________________________________________________________________

## Tests

  * Source
    * Some of them were created by me
    * Some were generated using https://pinetools.com/random-string-generator
    * Some were generated using https://loremipsum.io/generator/
    * For the genetic codes: http://faculty.ucr.edu/~mmaduro/random.htm

For testing the 2 aglorithms I created 40 tests. You can find them in _input_.

For both algorithms I used the same tests. As you can see, the results are the same. You can find the output
of each algorithm in _out-rk_ and _out-kmp_.

### _Details_

  * Multiple spacing (test 1, 2, 5, 7)
  * Large and small texts
  * Binary text (test 4)
  * The pattern is not found (tests 5, 12, 14, 19, 36 and 40)
  * A single letter search (tests 7 and 11)
  * Word and phrase searching 
  * One text contains only one letter (test 3)
  * The 15th test is empty
  * I also have tests that contain only
  
      * numbers (tests 16, 17 and 18)
      
      * letters
       
          * lower (tests 30 and 31)
          * upper (tests 32 and 33)
          * mixt (tests 27, 28 and 29)
       
      * symbols (tests 19, 20 and 21)
   * Tests 22 to 25 have as a pattern a paragraph
   * The 26th test has the same pattern and text
   * Since those 2 algorithms are used to detect plagiarism I included 5 tests (34 to 38)
     in which the text is a senior thesis
   * Also those 2 algorithms are used to detect abnormalities in the genetic code, I also
     included 2 tests (38 and 39) in which the text is a DNA sequence

In order to test other files, you need to add it in the **in_files** array.

In every input file you can find the pattern on the first line and then the text.
