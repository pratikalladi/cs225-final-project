# cs225-final-project

Final project for CS225 FA2022

**FastPairFinders Developers:**

- William Deng

- Max Jing

- Pratik Alladi

Documentation inside the `documents` folder

Results.md file found here:
(https://github.com/pratikalladi/cs225-final-project/blob/main/documents/Results.md)

Video Presentation found here:
(https://youtu.be/btaWNC3K8Pc)

## Github Organization:

`documents` folder:

Includes Project Proposal, Team Contract, Weekly Development Log, and Results.md written report

`final_proj` folder:

* ./data

Includes datasets for airports, routes, and airlines as well as specialized versions to test them on algorithms

* ./entry

Includes Jupyter notebook about test cases with visuals and main program (main.cpp)

* ./lib

Includes libraries such as cs225 and lodepng

* ./src

Includes source code for data ingestion algorithm, BFS, Dijkstra's, and PageRank

* ./tests

Includes test cases and Jupyter notebook about test cases

## To Run Program:

**Make sure you are inside the cs225 docker container environment**

1. Navigate to directory using `cd cs225-final-project`

2. Go into code files using `cd final_proj`

3. Create a build folder using `mkdir build `

4. Navigate into that build folder using `cd build`

5. Run CMake to confgure makefile using `cmake ..`

6. Finally, run `make` to compile our full program

7. Alternatively, run `make test` to compile our test suite

8. Run our main program by typing `./main` and our test suite by typing `./test`

## Main Program:

After running `./main`, the user will have 4 options:

* airports

* flights

* stats

* exit

Simply type the option you want to use.

airports:

* user must type "code" or "city" depending on which option they want to use

In all cases, user can type "exit" to quit program