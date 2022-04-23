I plan to create a simple game - timer/reaction based wherein you rotate the board left or right depending on which color led is switched on. Switching on the led will be controlled by some algorithm (TBD - maybe fizzbuzz or something more complex).
Not rotating or, rotating in the wrong direction or, missing the deadline within which you should rotate leads to end of the game.

I plan to use gyro to determine rotation direction. I will use a button to start/restart the game.
For debugging and/or an alternative to physically rotating I plan to make serial commands available which can also be used simultaneously.
I want to integrate the display if at all possible and provide other typical game configuration options - but will be my last thing to implement depending on how busy work keeps me in and around the project completion dates.

Here is a first pass at the state chart-
![state-chart](https://github.com/imbreakpoint/making-embedded-systems/blob/main/week4/final_project_state_chart.PNG?raw=true)
