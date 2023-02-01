# Team Caleb Art Gallery Placements

### Problem:
Oh no! The art gallery director, Greg, has
forgotten, again, to place all the necessary art
pieces on the wall for the upcoming showing. It is up to me to help him.
I need to write a few algorithms to help Greg (since he's so useless) effectively place
the art on the wall. Remember, people love to see money, so get much money on that wall as possible!

### Solutions:
To help Greg, I created three algorithms to help him place the art pieces on the walls

- Algorithm 1: This one takes the paintings, so long as there are fewer than 11,
  and places them on the wall in a multitude of arrangements and keeps track of the best way to
  fit the most amount of money up on the wall. (brute force). This algorithm is a sort of adaptation to my previously used 'next fit' algorithms. In this one, I keep track of old shelves
  that have been closed or skipped over and go back and add paintings to them if there is room. The new shelves are still created
  in terms of height the same way as 'next fit'. This method allows for much less wasted space and will keep track of which
  orientations created the most expensive wall of art. The way I have this implemented should lead to worst case 0(n^2); (Tell Greg to watch out... Sometimes the coordinates for this one are a little wonky so there may be some guesswork involved)


- Algorithm 2: This one first orders the paintings to be fitted onto the wall, as long
  as space provides, in order of descending price per painting (the highest value). This was implemented by using a sort of 'next fit' shelving
  algorithm that creates a shelf of height = to the height of the current painting if there are no shelves yet or if the current
  shelf does not have space. This leads to some wasted space as the algorithm does not go back to check for shelves with empty
  space. Paintings are passed into this algorithm in order of most expensive-first. The way I have this implemented should lead to worst case 0(n);


- Algorithm 3: For this one, I added a few extra layers. The paintings will be fit onto the wall
  and always be capable of looking back at past spaces left unfilled and going back to fill them. (custom implementation).
  This was implemented using the same 'next fit' shelving as the first algorithm. The only difference is the art was first sorted by most expensive per square
  unit of wall space, as opposed to just most-expensive first. The way I have this implemented should lead to worst case 0(n);



### Input:
The input will be given as a text file to be read in as a command line argument. This file will contain the following:

- line 1: width and height of the art wall
- line 2: the number of art pieces the algorithms must decide between
- each subsequent line will be in the following format:

    - art id number, art price, art width, art height


### Output:
The program should run and produce three output files. You will name the files by appending “-bruteforce”, “-highvalue”,
and “-custom” to the name of the input file. So if the input was "testing.txt", the outputs would be testing "testing-bruteforce.txt"... and so on.

The output file format should be as follows:

- the first line should contain a single integer representing the cumulative value of all pieces of art placed on the wall for this particular algo.
- each additional line represents a picture and should consist of 6 integers, each separated by a space
    - first integer is the picture id
    - second integer is the value of that picture
    - third integer is the width of that picture
    - fourth integer is the height of that picture
    - fifth integer is the x coordinate of the upper left corner of the picture on the wall
    - sixth integer is the y coordinate of the upper left corner of the picture on the wall

## Note:
Do not run the brute force for any art sets greater than 10 pieces. If the set is greater than 10 pieces, print
"data set size exceeds maximum" in the brute force output file.


### Sample Input/Output
If the following was your input file:
```
1024 768 
4
12 300 1023 767
9 200 300 100
23 250 800 700
1 100 100 100
```
Then you should expect your output to produce 3 different files.
