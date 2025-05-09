lab4 questions.txt
David Wang CSE31

Q1) There is no closing bracket for the main function. Furthermore, issues can arise since the arrays dont have predefined space.
Q2) Define hello[] with a set amount of space, like hello[100]. In case there isnt enough space in the character array when the contents of world[] are added to hello[] through strcat.
Q3) To run a program in GCC, compile with the -g tag and then (gdb) run. C doesn't provide bounds checking because it requires more compiile and run-time to do so.
Q4) A pro of using character arrays for strings in C is that it is more efficient with memory/run time, since with an object you would be using up extra memory/processing power to constantly check for space. The con is that you can run into bounds issues.

