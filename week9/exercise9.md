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
section             size        addr

.text                284   134218156

.rodata                0   134218440

.bss                  28   536870912

.data                  0   536870940

Total               2500

<br/>
<br/>

Lookup Table-<br/>
This one has a 256 entry look-up table that just looks at each byte in our uint32 to find the number of ones.
<br/>
<br/>
RAM: 284 bytes used
Flash: 556 bytes used
section             size
.text                300
.rodata              256 
.bss                  28
.data                  0
Total               2772

<br/>
<br/>
Here is a short comparison-<br/>
		Loop Algorithm		Lookup Table
RAM			28					284
Flash		284					556
.rodata		0					256
.text		284					300
Exec in ms	80ms				36ms	

<br/><br/>
A few conclusions-<br/>
Loop algorithm is efficient in terms of RAM space and flash size but it is also slower in comparison for execution time.
Lookup table on the other hand is faster but consumes a lot more RAM where it stores our lut.
<br/>
Here is where I tried a few optimizations and saw how the assembly listing changes, especially
the jump instructions and register usage as well as the execution time.

https://godbolt.org/z/91E9vejdq
