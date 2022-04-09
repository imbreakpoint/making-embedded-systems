** Blinky **
What build environment are you using? VSCode with Platformio

What are the hardware registers that cause the LED to turn on and off?
- GPIOG_ODR

What are the registers that you read in order to find out the state of the button?
- GPIOA_IDR

Can you read the register directly and see the button change in a debugger or by
printing out the value of the memory at the register’s address?
- I used a scope to see what is going on the button pin.
Scope capture here-
![scope-capture](https://github.com/imbreakpoint/making-embedded-systems/blob/main/week3/btn.jpeg?raw=true)
