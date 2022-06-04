Here is my worksheet, actual numbers from my class board-https://docs.google.com/spreadsheets/d/1EMiU7SHOIllH87asKg54Vjg6JW9zqpKPwHtsIDa2OWY/edit?usp=sharing

<br/>
<br/>
I measured directly at the Idd pins (JP3) on the board by connecting a DMM.
<br/>
The measurements that I see look reasonable based on what is in the datasheet.
<br/>

What bothers me though is if I connect the meter in series with power supply to the board then I see read 136mA, which drops down to 104mA in sleep mode
and this offset of about ~30mA or so between 'on' and 'sleep' mode is consistent with what is measured directly at the processor pins. 
<br/>
But what I haven't been able to figure out is what the rest of the 100mA is all about..Need to look at what other things are actively running ?
