Your company needs a tool to automate a data production phase of your daily build.
They need a way to calculate the amount of water collectable by a generic container described in term of a rectangular matrix of heights (a sort of heightmap). You can suppose each matrix element represent the height of the container, in an arbitrary length unit L. You can suppose the adjacent terrain level is 0.

Write a C++ program `WaterCalc` that takes as input file by command line the height matrix and prints on screen the algorithm output.

Usage:
`c:\lol\asd> WaterCalc.exe input.txt`

Example file: `input.txt`:
```
1 2 3 44 5 6
2 22 2 22 0 234
0 0 0 2 33 32
0 2 33 4 4 55
```

p.s.
  * the program must notify if the input file is bad formatted.
  * matrix elements must be >= 0
  * you can change a little bit the file format, if you need
  * any design choice must be documented.
  * any ambiguity in the problem definition (if any) must be resolved and documented.

![http://andreacasaccia.net/wp-content/uploads/2012/08/heightmap-620x180-1.png](http://andreacasaccia.net/wp-content/uploads/2012/08/heightmap-620x180-1.png)