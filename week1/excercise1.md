**Bird Feeder**

The goal of the system is to record sound of birds and store data to analyze behaviors.

A bird feeder that uses a motion sensor to detect any activity on the feeder. On detecting presence using the sensor in combination with the load cell, the microphone starts recording sounds if any as well as weight of the bird. The timestamped sound and weight gets stored to a memory card for analysis or simply playback the sounds.

Block Diagram-
![block-diagram](https://github.com/imbreakpoint/making-embedded-systems/blob/main/week1/week1_block_diagram.png?raw=true)

It uses motion sensor based off the I2C bus and a load cell as inputs, RTC is used to generate timestamps. The data gets written to the memory card. The A/D is multiplexed for both microphone and load cell and should be fine switching as we don't need to meet any critical timing. Also, simply writing to a memory card and then using that data for analysis off-chip should save us computations, power, and data out interfaces for e.g. USB. Throwing in a few debug leds and uart for capturing trace information if required.

![hierarchy-diagram](https://github.com/imbreakpoint/making-embedded-systems/blob/main/week1/week1_hierarchy_diagram.png?raw=true)
