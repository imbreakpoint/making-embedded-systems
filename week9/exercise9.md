I did a comparison for a couple of different standard implementations for the number of 1's in the binary representation of a number.

Loop Algorithm-
This just loops over all the bits, right shifiting on each iteration and testing if the bit is set.

RAM: 28 bytes used
Flash: 284 bytes used

section             size        addr

.isr_vector          428   134217728

.text                284   134218156

.rodata                0   134218440

.ARM.extab             0   134218440

.ARM                   0   134218440

.preinit_array         0   134218440

.init_array            4   134218440

.fini_array            4   134218444

.bss                  28   536870912

.data                  0   536870940

._user_heap_stack   1540   536870940

.ARM.attributes       42           0

.comment             126           0

.debug_frame          44           0

Total               2500


Lookup Table
This one has a 256 entry look-up table that just looks at each byte in our uint32 to find the number of ones.

RAM: 284 bytes used
Flash: 556 bytes used


section             size        addr

.isr_vector          428   134217728

.text                300   134218156

.rodata              256   134218456

.ARM.extab             0   134218712

.ARM                   0   134218712

.preinit_array         0   134218712

.init_array            4   134218712

.fini_array            4   134218716

.bss                  28   536870912

.data                  0   536870940

._user_heap_stack   1540   536870940

.ARM.attributes       42           0

.comment             126           0

.debug_frame          44           0

Total               2772


Here is a short comparison-
		Loop Algorithm		Lookup Table
RAM			28					284
Flash		284					556
.rodata		0					256
.text		284					300
Exec in ms	80ms				36ms	


A few conclusions-
Loop algorithm is efficient in terms of RAM space and flash size but it is also slower in comparison for execution time.
Lookup table on the other hand is faster but consumes a lot more RAM where it stores our lut.

Here is where I tried a few optimizations and saw how the assembly listing changes, especially
the jump instructions and register usage as well as the execution time.

https://godbolt.org/z/91E9vejdq
