**Blinky**<br>
What build environment are you using? VSCode with Platformio

What are the hardware registers that cause the LED to turn on and off?
- GPIOG_ODR

What are the registers that you read in order to find out the state of the button?
- GPIOA_IDR

Can you read the register directly and see the button change in a debugger or by
printing out the value of the memory at the register’s address?
- If I look at the peripherals window and expand that down then yes, the pin change on interrupt is visible in debugger.
- I also used a scope to see what is going on the button pin.
Scope capture here-
![scope-capture](https://github.com/imbreakpoint/making-embedded-systems/blob/main/week3/btn.jpg?raw=true)
