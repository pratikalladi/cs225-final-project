# FastPairFinders CS225 Final Project

Final project for CS225 FA2022

**FastPairFinders Developers:**

- William Deng

- Max Jing

- Pratik Alladi

## Deliverables Quick Links:

Results.md file found here:
(https://github.com/pratikalladi/cs225-final-project/blob/main/documents/Results.md)

Video Presentation found here:
(https://youtu.be/btaWNC3K8Pc)

## Github Organization:

`documents` folder:

Includes Project Proposal, Team Contract, Weekly Development Log, and Results.md written report

`final_proj` folder:

* #### ./data

Includes datasets for airports, routes, and airlines as well as specialized versions to test them on algorithms

* #### ./entry

Includes Jupyter notebook about test cases with visuals and main program (main.cpp)

* #### ./lib

Includes libraries such as cs225 and lodepng

* #### ./src

Includes source code for data ingestion algorithm, BFS, Dijkstra`s, and PageRank

* #### ./tests

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

* `airports`

* `flights`

* `stats`

* `exit`

Simply type the option you want to use.

`airports` can be used to find the following:

* direct and indirect destinations

* direct destinations only

* indirect destinations only

`flights` can be used to find the following:

* direct flights between 2 airports

`stats` can be used to find the following:

* Find an airport`s PageRank

* List top 50 airports by PageRank

* List top 100 airports by international destinations

* List top 100 airports by total destinations

* List top 100 most connected airports

In all cases, user can type "exit" to quit program

The main program will tell users exactly what input and format are needed

Here is a quick rundown for simpler visualization:

* `airports`

  * `code`

    * [3 letter IATA code]

      * `y`

        * `y`

          * `e`

        * `n`

          * `e`

      * `n`

        * `y`

          * `e`

        * `n`

          * `e`

  * `city`

    * [city name with proper capitalization]

      * [3 letter IATA code]

        * `y`

          * `y`

            * `e`

          * `n`

            * `e`

        * `n`

          * `y`

            * `e`

          * `n`

            * `e`

  * `exit

* `flights`

  * [3 letter IATA code]

    * [3 letter IATA code]

      * `e`

  * `exit`

* `stats`

  * `1`

    * [3 letter IATA code / 4 letter ICAO code]

      * `e`

  * `2`

    * `e`

  * `3`

    * `e`

  * `4`

    * `e`

  * `5`

    * `e`

  * `exit`

* `exit`

## Tests:

* type `make` or `make test` into terminal while in `build folder`

* run `./test` to run test cases