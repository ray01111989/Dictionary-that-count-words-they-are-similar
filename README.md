# Phrase Counter

A C program from CSE 224 (Project 4) that reads text and counts how many times each phrase appears.

## What it does

1. Reads text from standard input.
2. Converts every letter to uppercase.
3. Ignores the characters `( ) ' " -`.
4. Turns tabs and new lines into spaces, collapses runs of spaces into one, and trims spaces from the ends of each phrase.
5. Splits the text into phrases at every separator: `, . ; : ? !`.
6. Counts each distinct phrase (a repeat adds one to its counter).
7. Sorts the phrases by length, shortest first, and prints them.

## Build and run

```bash
gcc -Wall -o p4 p4.c
./p4 < input.txt
```

Example:

```bash
printf 'Hello, world. hello world! (Hello) world; hello, WORLD?\n' | ./p4
```

```
00002 <HELLO>
00002 <WORLD>
00002 <HELLO WORLD>
```

Each line is a 5-digit count followed by the phrase in angle brackets.

## Limits

- A phrase is truncated to 200 characters.
- The dictionary holds up to 1000 different phrases; if it fills up, a warning is written to standard error and further new phrases are not counted.

## Files

```
p4.c   The whole program
```
