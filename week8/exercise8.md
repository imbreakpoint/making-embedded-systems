Code (also checked-in)-

uint8_t initializedGlobal = 5;
uint8_t uninitializedGlobal;

int main(void)
{
	// configs
	HAL_Init();

	UARTinit();

	ConsoleInit();
	ConsoleProcess();

	static uint8_t staticInFunction = 2;

	uint8_t variableInFunction = 0;
	
	char buffer[80];
	uint8_t* pHeap = (uint8_t*)malloc(1);
	sprintf(buffer, "Heap Pointer:%p\r\n", pHeap);
	ConsoleSendString(buffer);

	volatile uint32_t reg;
    __asm volatile("mov %0, sp" : "=r"(reg));
    sprintf(buffer, "Stack Pointer:%08lX\r\n", (uint32_t)(reg));
	ConsoleSendString(buffer);


	sprintf(buffer, "&initialized global:%p\r\n", (void*)&initializedGlobal);
	ConsoleSendString(buffer);
	
	sprintf(buffer, "&uninitialized global:%p\r\n", (void*)&uninitializedGlobal);
	ConsoleSendString(buffer);

	sprintf(buffer, "&static in function:%p\r\n", (void*)&staticInFunction);
	ConsoleSendString(buffer);
	
	sprintf(buffer, "&variable in function:%p\r\n", (void*)&variableInFunction);
	ConsoleSendString(buffer);
}

Here's what I got-
Heap Pointer:0x200003b8<br>
Stack Pointer:2002FFA0<br>
&initialized global:0x20000008<br>
&uninitialized global:0x200002a4<br>
&static in function:0x20000009<br>
&variable in function:0x2002ffa3<br>

For the heap pointer the ._user_heap_stack from map file starts at 0x200003b0 so the heap pointer output location looks correct at 0x200003b8.
The data section starts at 0x20000000 and given that the initialized global and static go there it seems reasonable from the addresses above where they are getting stored.
The uninitialized global went to .bss common section which starts at 0x200001E0 and so that is also expected.
The variable in function did not have a place in map file as it went on the stack during execution. Having said that it also looks correct given the stack's starting location from the map file.


Now, for the swapping part -<br>
Heap Pointer:0x200003b8<br>
Stack Pointer:2002FFA0<br>
&initialized global:0x200001d8<br>
&uninitialized global:0x200000c4<br>
&static in function:0x200001d9<br>  
&variable in function:0x2002ffa3<br>

I swapped the order of sections for .data and .bss in .ld file, and the uninitialized global went from 0x200002a4 to 0x200000c4 while the initialized global went from 0x20000008 to 0x200001d8.<br>
More importantly,<br>
old .data = 0x20000000, new .data = 0x200001D0<br>
old .bss = 0x200001E0, new .bss = 0x20000000<br>
which does agree with what I see in the .map file
