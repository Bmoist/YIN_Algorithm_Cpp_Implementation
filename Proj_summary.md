# Workflow:
1. Study YIN algorithm paper: YIN, a fundamental frequency estimator for speech and music ```[DOI: 10.1121/1.1458024]```
  - Understand relationships between functions
  - Write pseudo code for implementation
2. Write a C++ file for audio file processing (optional)
  - Study RIFF format convention
  - Write C++ Read bytes method according to wav format
  - Put them into a folder
3. Write classes for implementing YIN algorithm

# Tips:
- $\tau_{max} = sample\_rate / freq_{min}$
- Window should be at least $2 * period$ or $2 * \tau_{max}$
  - Search range can be optimized to $\tau_{max} + \tau$ by YIN step 4 absolute threshold function (as pointed out in the paper)
  - where $\tau$ is $1/F_0$, or "the fundamental period"
- Debug method I used: 
```c++
for (Function f : {difference_function, cumulative_mean, etc..}){
  callFunctions(f);
  printFunctions(f);
  system("read -n 1 -s -p \"Press any key to continue...\"");
  system("clear");
}

```
# Still to dos:
- Generating signal on 2pi/tau instead of 2pi/F0 and convert answer back to F0 gives an error of about +0.2%
- 

# Questions/hypothesis
1. fread() into a chunk of memory, if the chunk ptr is a struct, are the bytes automatically assigned to the struct variables? Ex. char[4] (1 byte)
  - header of wav file: each byte is 2 hexadecimal digits long
2. New questions about the paper, after I started implementing the algorithm
  1. why function (8) in C section take the sum from j=1 to tau? Can I do $\sum_{j=\tau_{min}}^{\tau}{d_t(j)}$

# Reflections:
1. I got trapped by details a lot. Think again. Are they that important?
  - "I need a c++ audio parser!"
  - "I need a random signal generator to test!"
  - "What is the mechanics of rand() srand()? Why srand(time(NULL)) does not work inside a function?"
2. I got lost with my own designs. 
  - I have df[k] ranged [min_tau:max_tau]. I wrote this down already - the final answer tau is k + min_tau. But I kept making a lot of erroneous assumptions about array structure.
3. YIN algorithm is a smart way of finding periodicity among signal data. I can now understand the paper. It appears less daunting than it first seemed. I should learn about other more modern machine learning algorithms on pattern recognition, HMM, CNN, LSTM etc.

