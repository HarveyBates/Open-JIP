# Construction of Open-JIP (Electronics)
Below contains an instruction manual for building Open-JIP (Algae).

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Pictures/Schematic_Open-JIP.png">
</p>

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

# Construction of Open-JIP (Hardware)

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(28%20of%2034).JPG">
</p>

For the hardware construction of Open-JIP we will need, the 3D printed scaffold, an arduino mega, the circuit board we just made, the 10W LED of choice (R, B, G, O), a heat sink for the LED (optional), a 695nm longpass filter and an IR-filter (as shown in the above image). You will also need some hookup wire (solid core), a soldering iron, some solder and some wire snips. To start off attach a decent length of hookup wire to the terminals of the LED with some solder, take note of the polarity of the LED when doing this.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(29%20of%2034).JPG">
</p>

Next up attach the heatsink to the back of the LED. These usually have some thermal adheasive in which case you must peal off its cover before attaching. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(30%20of%2034).JPG">
</p>

Now its time to glue the LED to the 3D printed part, you can use any glue for this however I recommend 5 minute epoxy (not what is shown in the photo). 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(31%20of%2034).JPG">
</p>
<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(32%20of%2034).JPG">
</p>

Once cured we can attach the circuit board to the top of the Arduino and push it into its holder. Route and cut the wires from the LED though the holes and insert them into the spot on the PCB marked "Actinic LED". Push the photodiode into the small hole on the back side of the 3D printed structure it should be a tight fit. If not use a small amount of expoxy to secure it in place, ensuring that no expoxy gets on the face of the photodiode. 

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(33%20of%2034).JPG">
</p>

Lastly place the filters in the corrosponding spots. IR infront of the LED and 695nm longpass infront of the photodiode.

<p align="center">
  <img src="https://github.com/Open-JIP/Open-JIP/blob/master/Open-JIP%20Assembly/pic%20(34%20of%2034).JPG">
</p>

You have now assembled Open-JIP Algae.