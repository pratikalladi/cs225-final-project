# cs225-final-project

Final project for CS225 FA2022

**FastPairFinders Developers:**

- William Deng

- Max Jing

- Pratik Alladi

Documentation inside the `documents` folder

## Github Organization:

'documents' folder:

Includes Project Proposal, Team Contract, and Weekly Development Log

'final_proj' folder:

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

Navigate to directory using `cd cs225-final-project`

Go into code files using `cd final_proj`

Create a build folder using `mkdir build `

Navigate into that build folder using `cd build`

Run CMake to confgure makefile using `cmake ..`

Finally, run `make` to compile our full program

Alternatively, run `make test` to compile our test suite

Run our main program by typing `./main` and our test suite by typing `./test`

## Main Program:

After running './main', the user will have 4 options:

* airports

* flights

* stats

* exit

Simply type the option you want to use