Minimal Distinguishing Substring Finder

Program takes as input a string of words separated with spaces and returns the minimal string(s) or letter(s) for each that can be a unique identifier.

For example,


1. "dog doggo" input would return

    Your Words:

    1) dog
    2) doggo

    "dog" doesn't contain unique letter or combination of letters in the words given

    "doggo" contains unique combination of letters in the words given
    Smallest unique parts:
    gg , go

2. "trump trumpet donald don dog done does" input would return


    Your Words:

    1) trump
    2) trumpet
    3) donald
    4) don
    5) dog
    6) done
    7) does

    "trump" doesn't contain unique letter or combination of letters in the words given

    "trumpet" contains unique combination of letters in the words given
    Smallest unique parts:
    pe , et

    "donald" has the below unique letters:
    a , l

    "don" doesn't contain unique letter or combination of letters in the words given

    "dog" has the below unique letters:
    g 

    "done" contains unique combination of letters in the words given
    Smallest unique parts:
    ne 

    "does" has the below unique letters:
    s 