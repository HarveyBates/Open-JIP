# Open-JIP
Open-JIP is an open-source chlorophyll fluorometer used for quantifying photosynthetic processes is terrestrial plants and microalgae. The original device was published in [Photosynthesis Research](https://doi.org/10.1007/s11120-019-00673-2) in 2019. Since then a number of upgrades have been made to improve the performace of the device. 

If you would like to see what the device is capable of, you may be interested in this recent [publication](https://doi.org/10.1016/j.algal.2020.102105) which uses Open-JIP as a flow-through fluorometer.

<img src="Open-JIP Pictures/Teensy (v0.2).jpg" width="300">

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
3. 3D-printer
4. Wire strippers / cutters
5. Tweesers

#### Circuit Board

Here you will find all the components needed to construct the Open-JIP circuit board. These components can be bought from common electronics suppliers such as [digikey](https://www.digikey.com/), [LCSC](https://lcsc.com/en) or [farnell](https://au.element14.com/) etc. 

Note that most of the comonents are suface mount (SMD), this is due to their increased reliablity and in my opinion its easier to assemble SMD compared to through-hole (THT) components. 

#### Other

In addition to the above electronics you will need a few components such as a Teensy microcontroller, power supply and computer to use the device. A list of all these additional items can be found in the folder location ```Open-JIP/Bill of Materials/Other```.

#### 3D Models

The 3D-models used for 3D-printing Open-JIP can be found in the ```Open-JIP/3D Models``` folder. Two file types are specified (1) ```.stl``` can be directly imported into 3D-printing software such as [Ultimaker-Cura](https://ultimaker.com/software/ultimaker-cura) or sent to a 3D-printing manufactuer. (2) ```.STEP``` is the modifiable Open-JIP 3D-model and as such can be configured whichever way you want before being exported as a ```.stl``` file. 

### Software

Open-JIP operates via a computers serial port, the user sends commands in the form of strings that are converted to bytes then read by the Teensy microcontroller. This results in the device taking a measurement or other tasks. 

To setup the Teensy (flash the program to the Teensy microcontroller) you will need **both** [Arduino IDE](https://www.arduino.cc/en/software) and [TeensyDuino](https://www.pjrc.com/teensy/teensyduino.html) if running on Linux or Windows, or just [TeensyDuino](https://www.pjrc.com/teensy/teensyduino.html) if using a Mac. Instructions on how to do this is provided in the provided links. 

When first using Open-JIP: 

1. Plug the Teensy into your computer
2. Open Arduino-IDE
3. Select ```Tools>Board>Teensy 3.6``` (*may be in another part called Teensyduino)
4. Select ```Port>"Your Teensy Device"```
5. ```File>Open``` the "Teensy.ino" file found in ```Open-JIP/Teensy/Teensy.ino```
6. ```Sketch>Upload``` to flash the file onto the Teensy

After this you only need to flash the Teensy again after changing settings in the Teensy.ino file.

#### Basic Operations

To take a measurment open the serial monitor (```Tools>Serial Monitor```) and type in the command ```MF```. This will (in the default configuration) take a one second measurement of fluorescence and print the resulting measurments out into the serial monitor. 

You can copy and paste this into excel to graph the measurment. If you want to automate this you can create a script that sends and recieves commands to/from the serial port. I reccomend using python and the [pyserial](https://pypi.org/project/pyserial/) (```pip install pyserial```) package. 










