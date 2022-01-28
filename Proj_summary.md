# Workflow:
1. Study YIN algorithm paper: YIN, a fundamental frequency estimator for speech and music ```[DOI: 10.1121/1.1458024]```
  - Understand relationships between functions
  - Write pseudo code for implementation
2. Write a C++ file for audio file processing (optional)
  - Study RIFF format convention
  - Write C++ Read bytes method according to wav format
  - Put them into a folder
3. Write classes for implementing YIN algorithm
  - 


# Questions/hypothesis
1. fread() into a chunk of memory, if the chunk ptr is a struct, are the bytes automatically assigned to the struct variables? Ex. char[4] (1 byte)
  - header of wav file: each byte is 2 hexadecimal digits long

# Reflections:
1. I get trapped by details a lot. Think again. Are they that important?
  - "I need a c++ audio parser!"
  - "I need a random signal generator to test!"
  - "What is the mechanics of rand() srand()? Why srand(time(NULL)) does not work inside a function?"
