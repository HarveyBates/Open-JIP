# Open-JIP
Open-JIP is an open-source chlorophyll fluorometer used for quantifying photosynthetic processes is terrestrial plants and microalgae. The original device was published in [Photosynthesis Research](https://doi.org/10.1007/s11120-019-00673-2) in 2019. Since then a number of upgrades have been made to improve the performace of the device. 

If you would like to see what the device is capable of, you may be interested in this recent [publication](https://doi.org/10.1016/j.algal.2020.102105) which uses Open-JIP as a flow-through chlorophyll *a* fluorometer with the microalga *Chlorella vulgaris*.

<p align="center">
  <img src="Pictures/Teensy (v0.2).jpg" width="400">
</p>

### Specficiations

| Feature            | Value / Description                                          |
| ------------------ | ------------------------------------------------------------ |
| Actinic LED Colors | **Blue** 455 – 485 nm (466 nm), **Green** 517 – 555 nm (532 nm), **Orange** 583 – 600 nm (593 nm), **Red** 617 – 635 nm (626 nm). |
| Resolution         | 10 to 16-bit (optimised for 12-bit)                          |
| Sampling rate      | 8 &mu;s at 12-bits (can be overclocked)                      |
| Operating voltage  | 15 V 1.2 A (Barrel plug)                                     |
| Communications     | USB                                                          |
| Microcontroller    | Teensy 3.5/3.6 or Teensy 4.1 (3.6 Recommended)               |

## Getting started

### Downloading the files

New users are refered to the releases tab (normally located on right hand side of screen) , here you will find published releases of finished versions of the device (currently v0.2). The main repository is updated constantly and I cannot garantee that everything will work if you choose to clone the master branch. Nonetheless feel free to clone the master branch if you know what you are doing:

```bash
git clone https://github.com/HarveyBates/Open-JIP.git
```

### Gathering materials

Open-JIP is very simple in desgin and can be built in an afternoon if you have all the equipment at hand. The folder "Bill of Materials" contains all the materials needed to build Open-JIP. This has been divided into two parts; (1) circuit board and (2) other. 

In addition to the Bill of Mateirals you will need to have access to:

1. Soldering iron
2. Solder (Paste or wire variety)
3. Reflow oven (not nessesary but makes the circuit board easier to assemble)
4. 3D-printer
5. Wire strippers / cutters
6. Tweesers

#### Circuit Board

Here you will find a table all the components needed to construct the Open-JIP circuit board. These components can be bought from common electronics suppliers such as [digikey](https://www.digikey.com/), [LCSC](https://lcsc.com/en) or [farnell](https://au.element14.com/) etc. 

Note that most of the comonents are suface mount (SMD), this is due to their increased reliablity and in my opinion its easier to assemble SMD compared to through-hole (THT) components. 

To order the circuit board I recommend using [JLCPCB](https://jlcpcb.com/) as they are cheap, easy and ship fast. Open the folder titled Electronics and compress the housed Gerber files into a ```.zip``` file. Then on the JLCPCB website drag and drop the ```.zip``` file into the order form. The default settings are sutiable and you will receive 5 circuit boards for around $30 AUD. 

#### Other

In addition to the above electronics you will need a few components such as a Teensy microcontroller, power supply and computer to use the device. A table of all these additional items can be found in the folder location ```Open-JIP/Bill of Materials/Other```.

#### 3D Models

The 3D-models used for 3D-printing Open-JIP can be found in the ```Open-JIP/3D Models``` folder. Two file types are specified:

1. ```.stl``` can be directly imported into 3D-printing software such as [Ultimaker-Cura](https://ultimaker.com/software/ultimaker-cura) or sent to a 3D-printing manufactuer.
2. ```.STEP``` is the modifiable Open-JIP 3D-model and as such can be configured whichever way you want before being exported as a ```.stl``` file. You can use 3D modeling software to do this such as [Fusion360](https://www.autodesk.com/products/fusion-360/overview) or [Solidworks](https://www.solidworks.com/).

### Software

Open-JIP operates via a computers serial port (USB connection), the user sends commands in the form of strings that are converted to bytes then read by the Teensy microcontroller. This results in the device taking a measurement or other tasks. 

To setup the Teensy (flash the program to the Teensy microcontroller) you will need **both** [Arduino IDE](https://www.arduino.cc/en/software) and [TeensyDuino](https://www.pjrc.com/teensy/teensyduino.html) if running on Linux or Windows, or just [TeensyDuino](https://www.pjrc.com/teensy/teensyduino.html) if using a Mac. Instructions on how to do this is provided in the above links. 

When first using Open-JIP: 

1. Plug the Teensy into your computer
2. Open Arduino IDE
3. Select ```Tools>Board>Teensy 3.6``` (*may be in another part called Teensyduino)
4. Select ```Port>"Your Teensy Device"```
5. ```File>Open``` the "Teensy.ino" file found in ```Open-JIP/Teensy/Teensy.ino```
6. ```Sketch>Upload``` to flash the file onto the Teensy

*Note* - You may need some libraries which can be downloaded easily if you follow [these instructions](https://www.arduino.cc/en/Guide/Libraries).

After this you only need to flash the Teensy again after changing settings in the Teensy.ino file.

#### Basic Operations

To take a measurment open the serial monitor (in the Arduino IDE when the deivce is connected to your computer) (```Tools>Serial Monitor```) and type in the command ```MF``` (denoting **m**easure **f**luorescence). This will (in the default configuration) take a one second measurement of chlorophyll fluorescence and print the resulting measurments out into the serial monitor. 

You can copy and paste the data into excel in order to graph the polyphasic rise. If you want to automate this you can create a script that sends and recieves commands to/from the serial port. I reccomend using python and the [pyserial](https://pypi.org/project/pyserial/) (```pip install pyserial```) package. 

There are a number of included functions that require the same method to operate:

1. ```MF``` - **M**easure **f**luorescence. Measure the chlorophyll *a* fluorescence signature of the microalga of interest. 
2. ```CP``` - **C**alculate **p**arameters. Calculate and print out basic fluorescence parameters from the most recently captured OJIP curve. 
3. ```CFo``` - **C**alibrate **Fo** (the minimum level fluoresence). Provides short flashes of illumination for calibrating the minimum level fluorescence. This command is useful if you want to know if your measurment is going to *saturate* (due to an overly concentrated sample) before taking a measurment. 
4. ```ML``` - Calibrate actinic intensity (**m**easure **l**ight). Turns on the actinic LED for a period of three seconds to allow the intensity to be measured by a 4\pi light meter.
5. ```Cr``` **C**alibrate **r**ise time of the actinic LED/amplifier combination. Provides some short  (100us) flashes of illumination from the actinic LED to calibrate your setup using an external oscilloscope. Useful if you want to ensure your Fo value is accurate (i.e. Fo should be measured when the actinic LED and amplifier are stable (usually around 40us)). *Note* this is only nessesary if you alter the default electronics configuration (see below).  

#### Custom Software Functions

The main feature of Open-JIP is its simple nature and customisability. Users can change things such as the length of the actinic saturation pulse and the sensitivity of the device.

##### Changing the actinic pulse length

In the Teensy/Teensy.ino file these lines are responsible for the actinic pulse length:

```C++
// Setup arrays that hold fluorescence data
int microRead [1000];
int milliRead[1000];

// Setup arrays that hold timestamps that correspond to fluorescence values
float microTime[1000]; 
float milliTime[1000];

int microLength = 1000, milliLength = 1000; // Change these to match the size of the above arrays
```

```microRead``` and ```milliRead``` are arrays containing the number of datapoints that should be captured at fast (microseconds) and slower (milliseconds) intervals. Teensy microcontrollers have alot of memory compared to the original Arduino version of Open-JIP. This allows the measurments times to be alot longer without running out of memory. 

If you want to change the actinic pulse length you can do so by adjusing the array size of ```milliRead```, ```milliTime``` (timestamps) and the ```milliLength``` value to match eachother. Unfortunatly, these adjustments are not representive of time so if you want for example 3 second exposures you will have to play around with the array size of these variables untill your measurements are 3 seconds in length. 

##### Changing the devices senstivity

This can be done easily if using a Teensy 3.6 as this device comes with two analog reference values (3.3V and 1.1V). The ```set_reference_voltage()``` function allows you to change the required analog reference dynamically. 

```c++
void set_reference_voltage(float voltage){
  // Sets and initalises the required reference voltage for measurments
  if(voltage == 3.3){
    analogReference(DEFAULT); // Set to 3.3 V
  }
  else if(voltage == 1.1){
    analogReference(INTERNAL1V1); // Set to 1.1 V
  }
  else{
    analogReference(DEFAULT); // Set to default (3.3 V) if unknown value is found
  }
  analogRead(readPin); // Initalise reference voltage
}
```

*Note* - This is usally done statically at the start of the program by adjusting the value of ```refVoltage``` to either 3.3 or 1.1 depending on you requirements.

The number of bits for these readings can be changed via this command in the ```void setup()``` function:

```c++
analogResolution(12); // 12 bit-resolution
```

*Note* - **Increasing** the resolution **decreases** the sampling rate so if you want to get alot of data points around Fo I reccomend you use a 12 or 10-bit resolution.

If you use have a 12 bit-resolution with a reference voltage of 1.1V the finest sensivitiy of the device is 0.00027 V per-division (1.1V / 2^12) and a 8 &mu;s sampling rate. 

### Hardware

While software adjustments are suitable for small changes in a number of factors, other adjustments need to made to the hardware to dial in the performance of Open-JIP.  This includes changing the brightness of the actinic LED and large changes to the senstivitiy of the detection circuitry. 

#### Changing the actinic LED brightness

The easiest way to accomplish this is through the use of neutral density filters placed infront of the actinic LED. However, we can also change this by adjusting a resistor value (R10) on the circuit board.

<p align="center">
  <img src="Pictures/ActinicCircuit.png" width="600">
</p>


**Increasing** the resistance of R10 results in **decreased** actinic brightness.

**Decreasing** the resistance of R10 results in **increased** actinic brightness.

Do this in 1Kohm steps to dial in the specific brightness you need for your application.

#### Changing the detection sensitivity

When measuring dilute or highly concentrated solutions of microalgae you may want to change the resistor value (R5) to suit your needs. 

<p align="center">
  <img src="Pictures/DetectionCircuit.png" width="600">
</p>


**Increasing** the resistance of R5 will **increase** the sensitivty of detection.

**Decreasing** the resistance of R5 will **decrese** the sensitivty of detection.

Do this with 200kohm steps to dial in the specific sensitivty that you need for your application.

*Note* - if you begin to get a large overshoot occuring at the start of your measurements you may need to increase the capacitor value (C5) to 2pF - 5pF. This [article](https://wiki.analog.com/university/courses/electronics/electronics-lab-1st) may help you if you encounter this issue.

### User customiabilty 

Users are encouraged to modify Open-JIP for their needs. Some examples of this may be to:

1. Customise the 3D-model to suit a flow-through cuvette arrangement 
2. Redesign the 3D-model to improve its water resistance
3. Make an array of Open-JIP devices of difference actinic colors
4. Change the desgin of the 3D printed mount
5. Add an external trigger (TTL)

### To do list

These are notes on features I would like to see the device have in the future:

1. Software customisable gain
2. Software customisable actinic brightness
3. Entirely USB powered
4. Mulit-wavelength actinic LED with software control 
5. Smaller overall footprint

### Licence

The software in this work is licensed under GNU AFFERO GENERAL PUBLIC LICENSE Copyright (C) (2020) (Harvey Bates)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/

For more information contact: [harvey_bates@hotmail.com](mailto:harvey_bates@hotmail.com)

<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/3.0/88x31.png" /></a>

The hardware (3D Models, Electronic Schematics) in this work is licensed under a [Creative Commons Attribution-ShareAlike 3.0 Unported License](http://creativecommons.org/licenses/by-sa/3.0/).



 
