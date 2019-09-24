# Open-JIP
Information regarding the operation of the Open-JIP Chlorophyll Fluorometer is enclosed in this repository. Open-JIP is a low-cost instrument for quantifying photosynthesis in plants and algae.

<img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Algae.png" height="250" width="250"> Open-JIP Algae
<img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Plant.png" height="250" width="250"> Open-JIP Plant

Topics discussed:
1. About Open-JIP
2. Construction manual for Open-JIP
3. Software manual for Open-JIP
4. User modification of Open-JIP

# About Open-JIP
Open-JIP as the name suggests is a fast rise fluorometer (OJIP). Its design is simple, an actinic (drives photosynthesis) light source with an IR-filter, a sample, a ~680nm longpass filter and a detector. Light emitted from the light source is filtered of heat using the IR-filter. The sample is excited by the light source and fluorescence is emitted. The fluorescence is filtered from the actinic light source using the ~680nm longpass filter and detected by a photodiode. The entire measurment takes one second however longer protocals can be designed if the user wishes.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Diagram.png" height="544" width="626">
</p>
As can be seen from the figure, Open-JIP operates using a controller (Arduino Mega) that sends a signal to a excitation LED circuit (Actinc LED) which excites the algae or plant. The resulting fluorescence is detected by the photodiode circuit and interpreted by the Arduino.
The algae version uses a 90 degree angle between detector and emitter. The LED is activated and filtered by the infrared filter to remove far infra-red radiation (heat). The sample (housed in a polystyrene cuvette) is surrounded on the two opposing walls by mirrors. These mirrors help to focus more fluorescence into the detector and also aid to increase the average light intensity within the cuvette. As the sample fluoresces the detector records the intensity while the LED is on. As the LED is on at the time of measurment and light it emits needs to be filtered from the measured light intensity and this is done though the use of a 695nm long-pass filter that is located infront of the photodiode.
The plant version using the same setup as the algae version however as it utalises a blue excitation (actinic) LED there is no need for an infrared filter as it emits very little IR. An apature infront of the sample reduces the exposure of PSIIs' to be measured and results in reduced fluorescence intensity ensuring the detector doesn't saturate. The size of the apature can be changed to suit the plants which are being measured. 

# User modification of Open-JIP
The user is encouraged to modify the device to suit there needs and trial different protocals. This can be done by redesigning the 3D models and/or the software aspect of Open-JIP. Below is a list of example changes that can be made to the device:
1. Open-JIP is designed around an Arduino Mega as these devices have a decent amount of memory (256kB) and are avalible around the world. However, another device the Teensy v3.0 to v3.6 would also be suitable for this application and possibly be faster at aquring data points. The probelm however would lie with the speed at which the LED can switch on and be detected by the sensor. An advantage of using a teensy would be the increase in bit resolution from 10 bits (of the Arduino) to 32 bits (of the Teensy v3.6). 
2. Increasing the gain of the detection circuit. This can be done by using a higher value feedback resistor. The baseline value in Open-JIP is 2.2Mohm however, we can increase this to a higher value such as 4.7Mohm. By doing so we induce some overshoot in the operational amplifiers functioning, this can be compinstated by using a higher feedback capactor (in the baseline Open-JIP unit the Cf is 1pF). Although by increasing the capacitance the rate at which the detection circuit can respond to changes is slowed so any changes should be checked using an oscilloscope to ensure the rise time is less than ~40us (to see how this can be done see below).
3. Increasing the length of measurment. In Open-JIPs' current design there are 200 fast data points taken roughly every 20 microseconds and another 900 taken every millisecond. This brings the total time of measurment to ~930ms and uses ~80% of the arduinos memory. However, the user may want to see some analysis of quenching after longer exposures. To do so they can reduce the size of the fast datapoints and increase the slow data points. Alternatively using a device with a greater writable memory would allow this to be achieved. The teensy v3.6 has 1 megabyte of flash storage and would be suitable for this purpose.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Detection_Rise-time.png" height="360" width="600">
</p>
The above image shows the detection speed of the photodiode circuit in the default Open-JIP setup. To achieve this a 5mm LED is flashed on an off every 100 microsecnds infront of the photodiode. The scope shows the rise time to be <17 microseconds. If another feedback resistor with feedback capactior combination is used the user must preform this same test. 
