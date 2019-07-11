# Open-JIP
Information regarding the operation of the Open-JIP Chlorophyll Fluorometer is enclosed in this repository. Open-JIP is a low-cost instrument for quantifying photosynthesis in plants and algae.

<img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Algae.png" height="250" width="250"> Open-JIP Algae
<img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Plant.png" height="250" width="250"> Open-JIP Plant

Topics discussed:
1. About Chlorophyll Fluorescence
2. About Open-JIP
3. Construction manual for Open-JIP
4. Software manual for Open-JIP
5. User modification of Open-JIP

# About Chlorophyll Fluorescence
Chlorophyll a fluorescence can be used to monitor photosynthetic activity in plants. Light absorbed by a plants antenna complexes is channeled to a protein complex known as Photosytem II (which is a special chlorophyll) and results in three processes. The first is a series of reduction and oxidisation reactions called photochemisty. The result of photochemisty is the production of energy in the form of NADPH and ATP and helps the plant to grow. The second fate of light that has been channeled to PSII is the formation of heat due to a process known as non-photochemical quenching. The final process is the one we can measure directly, this is known as chlorophyll a fluorescence. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Chl%20excitation.png" height="459" width="495">
</p>

The chlorophyll fluorescence that is emitted has a peak intensity at ~680nm (Far-Red in color) however, the spread of the emission streatches far into the infra-red portion of the spectrum. The basic interpreation of chlorophyll fluorescence is that an increase in relative fluorescence is an indicator of poor photochemisty where as a decrease in relative fluorescence intensity indicates higher photochemistry. The interpretation of fluorescence is a bit more complicated than this and will be expalined below.

There are a few different methods of assessing chlorophyll fluorescence:
1. Pulse Amplitude Modulated Fluorometery (PAM)
2. Fast Repetition Rate (FRR) 
3. Fast Rise Fluorometry (OJIP)

The chlorophyll fluorometer presented here utiliases fast rise (OJIP) fluorometry, this techniques name is based on its three main phases, O-J, J-I and I-P:

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/OJIP%20Relative.png" height="315" width="494">
</p>

- O-J   is the photochemical phase and corrosponds the rate of which the first electron acceptor (Qa) is reduced
- J-I   corrosponds to the reduction of the pladtoquinone pool (PQ-pool) 
- I-P   is the result of a satuation of electrons on the acceptor side of PSI

OJIP fluorometry is typically preformed in a single test lasting for one second. The fluorometer uses a very bright (>2100 uE) light source to excite the plant/algaes PSIIs' causing them to fluoresce. The intensity of the resulting fluorescence is measured by the fluorometer and by interpreting the information recieved we can make infrences about the photochemisty of the organism. As mentioned above photochemistry involves a series of oxidation and reduction reactions occuring around the thylakoid of a plant enclosed within the chloroplast. PSII when excited wants to be reduced back to a more stable state, to do this it can loose energy by emitting photons (fluorescence). Alternatively the excited PSII can expell excess energy in the form of heat (not discussed here). Finally the excited PSII can get rid of a electrons into the electron transport chain of photosynthesis (the process of which is shown below). 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Z-Scheme.png">
</p>
The above figure is known as a Z-scheme. It displays the transfer of energy from component to component in the electron transport chain. Energy is transported in the form of electron transfer from left to right. Hv in the figure refers to irradiance, it excites P680 also known as PSII to an excited state. Energy is transfered to phenophytin and then to Qa. The rate at which Qa accepts electrons from PSII governs the intensity of fluorescence until Qa itself can pass electrons futher into the electron transport chain. This is shown as the J-step in an OJIP measurment. Electrons are then held up at the cytochrome b6f complex represented as the I-step. Plastocyanin (PC) accepts electrons and passes energy to P700 also known as Photosystem I (PSI). Irradiance channeled to PSI excites it to a higher state allowing electrons to continue futher into the electron transport chain. The P-step isn't as well characterised as the other two steps and corrosponds to some point between PSI excitation and Ferredoxin (Fd). FNR also known as Ferredoxin NADP+ Reductase represents the site at which NADP+ is converted to NADPH for use in the Calvin Benson Cycle. Not shown in the figure is the series of processes that acidfy the thylakoid lumen. This occurs as a result of proton saturation from the conversion of water into oxygen and other processes in the electron transport chain. Proton saturation inside the thylakoid lumen helps to drive ATP synthase which outputs ATP again for use in the Calvin Benson Cycle. 

# About Open-JIP
Open-JIP as the name suggests is a fast rise fluorometer (OJIP). Its design is simple, an actinic (drives photosynthesis) light source with an IR-filter, a sample, a ~680nm longpass filter and a detector. Light emitted from the light source is filtered of heat using the IR-filter. The sample is excited by the light source and fluorescence is emitted. The fluorescence is filtered from the actinic light source using the ~680nm longpass filter and detected by a photodiode. The entire measurment takes one second however longer protocals can be designed if the user wishes.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Open-JIP%20Diagram.png" height="544" width="626">
</p>
As can be seen from the figure, Open-JIP operates using a controller (Arduino Mega) that sends a signal to a excitation LED circuit (Actinc LED) which excites the algae or plant. The resulting fluorescence is detected by the photodiode circuit and interpreted by the Arduino.
The algae version uses a 90 degree angle between detector and emitter. The LED is activated and filtered by the infrared filter to remove far infra-red radiation (heat). The sample (housed in a polystyrene cuvette) is surrounded on the two opposing walls by mirrors. These mirrors help to focus more fluorescence into the detector and also aid to increase the average light intensity within the cuvette. As the sample fluoresces the detector records the intensity while the LED is on. As the LED is on at the time of measurment and light it emits needs to be filtered from the measured light intensity and this is done though the use of a 695nm long-pass filter that is located infront of the photodiode.
The plant version using the same setup as the algae version however as it utalises a blue excitation (actinic) LED there is no need for an infrared filter as it emits very little IR. An apature infront of the sample reduces the exposure of PSIIs' to be measured and results in reduced fluorescence intensity ensuring the detector doesn't saturate. The size of the apature can be changed to suit the plants which are being measured. 

# Construction of Open-JIP
Below contains an instruction manual for building Open-JIP (Algae).

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(1%20of%2034).JPG">
</p>

The above image shows all the components needed to assemble the electronics of Open-JIP. You will also need some hookup wire (we use solid core wire, PRT-11367) a soldering iron, some solder and a pair of wire snips. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(3%20of%2034).JPG">
</p>

Start with the small components, the capacitors and resistors. Look at the capacitors and you will see a code on the side (for this design we want 1, 473 and 104) this corosponds to a specific value of capacitance. On the printed circuit board (PCB) look for areas that match the code of capacitor and insert its legs into the holes. Orientation does not matter for these types of capacitors. On the opposite side of the PCB bend the legs of the capacitors to hold them in place. Continue this process until you have inserted all capacitors.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(4%20of%2034).JPG">
</p>

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(5%20of%2034).JPG">
</p>

Once complete you want to solder the capacitors in place. To do this hold the soldering irons tip on the joint you want to solder for roughly two seconds and then add some solder, it should melt and envelop the joint and look like the photos below. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(6%20of%2034).JPG">
</p>

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(7%20of%2034).JPG">
</p>

Once you have soldered all capacitors then you can sip the trailing ends on the underside of the board as shown below.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(8%20of%2034).JPG">
</p>

Follow the same process for all the resistors. Their specific resistance is marked on the PCB. Follow by adding the OP-AMP located in the top left corner of the below photo. Ensure the OP-AMPs orientation is correct by keeping the dot on the OP-AMP the same as in the photo below. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(9%20of%2034).JPG">
</p>

In the above photo you can see an LED which corrosponds to position on the PCB marked LED1. The anode is the shorter leg and goes on the flat side of the while marking on the PCB. 
Next up is the battery connector, this goes at position P1 with the short legs going into the PCB. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(11%20of%2034).JPG">
</p>

We will now place the two indicator LEDs' at the front of the board. The same as in the last LED keep the short leg on the flat edge of the markings on the PCB. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(12%20of%2034).JPG">
</p>

The next item is the photodiode preperation. We are using the solid core wire mentioned above and with the use of some solder we are going to attach the wire to the terminals of the photodiode. Black wire is used on the side with the extrusion on the photodiode and red for the other terminal. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(13%20of%2034).JPG">
</p>

We can use some bluetack here to hold the wire and LED in place.
<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(15%20of%2034).JPG">
</p>

If the user wishes they may add some insulation around the solder joints to keep them from coming in contact.
Back to the board we want to add the attachement for plugging in the excitation LED. This is an offcut from the arduino header pins which you can cut off using your wire cutters as we only want two terminals. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(16%20of%2034).JPG">
</p>

The barrel connector for connecting the power supply is soldered next onto the front of the PCB.
<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(17%20of%2034).JPG">
</p>

Next up we have the four large components the LM7812 voltage regulator, the IRL44ZN mosfet, the KA7812 voltage regulator and the BD681 darlington transitor. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(18%20of%2034).JPG">
</p>

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(19%20of%2034).JPG">
</p>

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(20%20of%2034).JPG">
</p>

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(21%20of%2034).JPG">
</p>

Now its time for the boost coverter. This goes over the lettering on the PCB that says "Place boost Converter Here". First we want to prepare the pins to get as good of a connection as possible. Do this by snipping away the underside solder joints of the boost coverter. BE SURE not to snip Vout, GND and Vin as we need these to be long to attach it to the board.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(22%20of%2034).JPG">
</p>

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(23%20of%2034).JPG">
</p>

Place the boost coverter on the PCB with Vout, GND and Vin inserted into the corrosponding PCB holes. Use your soldering iron to heat up the solder joint as much as possible and use solder to create a strong connection.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(24%20of%2034).JPG">
</p>

We will now attach the headers for the arduino mega. To do this insert the headers into the outside holes of the PCB. These line up perfectly with an Arduino Mega and will allow you to mount the circuit on the top of the board.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(25%20of%2034).JPG">
</p>

Lastly measure the photodiode wires that we prepared above to be roughly ~105mm in length from the base of the photodiode to the inserts for the PCB. The red wire goes into the square solder mask on the PCB marked D1 and the black goes in the circular solder mask.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(27%20of%2034).JPG">
</p>

You have now assembled Open-JIPs electronics circuit. 


# User modification of Open-JIP
The user is encouraged to modify the device to suit there needs and trial different protocals. This can be done by redesigning the 3D models and/or the software aspect of Open-JIP. Below is a list of example changes that can be made to the device:
1. Open-JIP is designed around an Arduino Mega as these devices have a decent amount of memory (256kB) and are avalible around the world. However, another device the Teensy v3.0 to v3.6 would also be suitable for this application and possibly be faster at aquring data points. The probelm however would lie with the speed at which the LED can switch on and be detected by the sensor. An advantage of using a teensy would be the increase in bit resolution from 10 bits (of the Arduino) to 32 bits (of the Teensy v3.6). 
2. Increasing the gain of the detection circuit. This can be done by using a higher value feedback resistor. The baseline value in Open-JIP is 2.2Mohm however, we can increase this to a higher value such as 4.7Mohm. By doing so we induce some overshoot in the operational amplifiers functioning, this can be compinstated by using a higher feedback capactor (in the baseline Open-JIP unit the Cf is 1pF). Although by increasing the capacitance the rate at which the detection circuit can respond to changes is slowed so any changes should be checked using an oscilloscope to ensure the rise time is less than ~40us (to see how this can be done see below).
3. Increasing the length of measurment. In Open-JIPs' current design there are 200 fast data points taken roughly every 20 microseconds and another 900 taken every millisecond. This brings the total time of measurment to ~930ms and uses ~80% of the arduinos memory. However, the user may want to see some analysis of quenching after longer exposures. To do so they can reduce the size of the fast datapoints and increase the slow data points. Alternatively using a device with a greater writable memory would allow this to be achieved. The teensy v3.6 has 1 megabyte of flash storage and would be suitable for this purpose.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Detection_Rise-time.png" height="360" width="600">
</p>
The above image shows the detection speed of the photodiode circuit in the default Open-JIP setup. To achieve this a 5mm LED is flashed on an off every 100 microsecnds infront of the photodiode. The scope shows the rise time to be <17 microseconds. If another feedback resistor with feedback capactior combination is used the user must preform this same test. 
