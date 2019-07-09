# Open-JIP
Information regarding the operation of the Open-JIP Chlorophyll Fluorometer is enclosed in this repository. Open-JIP is a low-cost instrument for quantifying photosynthesis in plants and algae.

<img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Algae.png" height="250" width="250"> Open-JIP Algae
<img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Plant.png" height="250" width="250"> Open-JIP Plant

# About Chlorophyll Fluorescence
Chlorophyll a fluorescence can be used to monitor photosynthetic activity in plants. Light interacting with a special chlorophylls called photosystems (specifically photosystem II or PSII) results in three processes. The first is a series of reduction and oxidisation reactions called photochemisty. The result of photochemisty is the production of energy in the form of NADPH and ATP. The second fate of light is the formation of heat due to a process known as non-photochemical quenching. The final fate is the one we can measure directly, this is known as chlorophyll a fluorescence. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Fate_of_Light.png" height="300" width="540">
</p>

The fluorescence occurs with a peak at 680nm (Far-Red in color) however, the spread of this peak streatches far into the infra-red portion of the spectrum. By measuring chlorophyll fluorescence we can derive information about the photochemistry of a plant as an increase in fluorescence is an indicator of poor photochemisty and decreases indicate high photochemistry. The interpretation of fluorescence is a bit more complicated than this and will be explained below. 

There are a few different methods of assessing chlorophyll fluorescence:
1. Pulse Amplitude Modulated Fluorometery (PAM)
2. Fast Repetition Rate (FRR) 
3. Fast Rise Fluorometry (OJIP)

# About Open-JIP
Open-JIP as the name suggests is a fast rise fluorometer (OJIP). Its design is simple, an actinic (drives photosynthesis) light source with an IR-filter, a sample, a ~680nm longpass filter and a detector. Light emitted from the light source is filtered of heat using the IR-filter. The sample is excited by the light source and fluorescence is emitted. The fluorescence is filtered from the actinic light source using the ~680nm longpass filter and detected by a photodiode. The entire measurment takes one second however longer protocals can be designed if the user wishes. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/OJIP.png" height="315" width="494">
</p>

The technique of OJIP is named based on its three main phases, O-J, J-I and I-P:

- O-J   is the photochemical phase and corrosponds the rate of which the first electron acceptor (Qa) is reduced. 
- J-I   corrosponds to the reduction of the pladtoquinone pool (PQ-pool) 
- I-P   is the result of a satuation of electrons on the acceptor side of PSI

# Modification of Open-JIP
The user is encouraged to modify the device to suit there needs and trial different protocals. This can be done by redesigning the 3D models and/or the software aspect of Open-JIP. Below is a list of example changes that can be made to the device:
1. Open-JIP is designed around an Arduino Mega as these devices have a decent amount of memory (256kB) and are avalible around the world. However, another device the Teensy v3.0 to v3.6 would also be suitable for this application and possibly be faster at aquring data points. The probelm however would lie with the speed at which the LED can switch on and be detected by the sensor. An advantage of using a teensy would be the increase in bit resolution from 10 bits (of the Arduino) to 32 bits (of the Teensy v3.6). 
2. Increasing the gain of the detection circuit. This can be done by using a higher value feedback resistor. The baseline value in Open-JIP is 2.2Mohm however, we can increase this to a higher value such as 4.7Mohm. By doing so we induce some overshoot in the operational amplifiers functioning, this can be compinstated by using a higher feedback capactor (in the baseline Open-JIP unit the Cf is 1pF). Although by increasing the capacitance the rate at which the detection circuit can respond to changes is slowed so any changes should be checked using an oscilloscope to ensure the rise time is less than ~40us (to see how this can be done see below).
3. Increasing the length of measurment. In Open-JIPs' current design there are 200 fast data points taken roughly every 20 microseconds and another 900 taken every millisecond. This brings the total time of measurment to ~930ms and uses ~80% of the arduinos memory. However, the user may want to see some analysis of quenching after longer exposures. To do so they can reduce the size of the fast datapoints and increase the slow data points. Alternatively using a device with a greater writable memory would allow this to be achieved. The teensy v3.6 has 1 megabyte of flash storage and would be suitable for this purpose.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Detection_Rise-time.png" height="360" width="600">
</p>
The above image shows the detection speed of the photodiode circuit in the default Open-JIP setup. To achieve this a 5mm LED is flashed on an off every 100 microsecnds infront of the photodiode. The scope shows the rise time to be <17 microseconds. If another feedback resistor with feedback capactior combination is used the user must preform this same test. 
