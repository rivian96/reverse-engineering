This repository contains an simple web  page that simulates the Fetch-Decode-Execute cycle of a basic CPU. It allows you to load, step through, and run a program with a simplified instruction set, including instructions like LOAD, ADD, SUB, STORE, and JUMP.

### Example program
```assembly
LOAD R0, 5
LOAD R1, 10
ADD R2, R0, R1
STORE 20, R2
LOAD R3, 20
SUB R3, R3, R0
JUMP 0
```