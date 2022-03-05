This is a search engine project .
It reads a file (master.txt) that tells which sites to upload to the database. (task1)
It can search do simple (task2) and advanced (task3) search.
In task4.c I created a program that checks if certain urls are correspondent with legit websites (checksum = XOR on site content).
In browser.c I coded a search engine in ncurses using the features mentioned above and the menu library.
Additionally, I put all functions I created and the structures' & enumerations' definition in functions.h.


Explanation:
simple search - search only the words
advanced search - search sequences and exclude words from websites
