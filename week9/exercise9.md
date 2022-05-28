I did a comparison for a couple of different standard implementations for the number of 1's in the binary representation of a number.

<br/>
Loop Algorithm-<br/>
This just loops over all the bits, right shifiting on each iteration and testing if the bit is set.
<br/>
<br/>
RAM: 28 bytes used<br/>
Flash: 284 bytes used
<br/>
<br/>


Lookup Table-<br/>
This one has a 256 entry look-up table that just looks at each byte in our uint32 to find the number of ones.
<br/>
<br/>
RAM: 284 bytes used<br/>
Flash: 556 bytes used
<br/>
<br/>

Here is a short comparison-<br/>
![algo-comparison](https://github.com/imbreakpoint/making-embedded-systems/blob/main/week9/ex9_comparison.png?raw=true)	

<br/><br/>
A few conclusions-<br/>
Loop algorithm is efficient in terms of RAM space and flash size but it is also slower in comparison for execution time.
Lookup table on the other hand is faster but consumes a lot more RAM where it stores our lut.
<br/>
Here is where I tried a few optimizations and saw how the assembly listing changes, especially
the jump instructions and register usage as well as the execution time.
<br/>

https://godbolt.org/z/91E9vejdq
