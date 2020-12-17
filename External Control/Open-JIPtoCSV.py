# 
import sys
import csv
import glob
import serial
import time
import datetime
from time import strftime

usb_baudrate = 115200 # Baudrate to match Teensy

fileName = "Open-JIP_Data.csv" # Filename of output .csv file


def serial_ports():
	# List serial ports available on each OS
	# For windows OS
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    # For linux OS
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        ports = glob.glob('/dev/tty[A-Za-z]*')
    # For Mac OS
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')
    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            if("Bluetooth" not in port): # Excludes bluetooth port on Mac OS
            	result.append(port)
        except (OSError, serial.SerialException):
            pass
    if(len(result) == 0):
    	raise IndexError("No USB devices found. Ensure Open-JIP is pugged in.")
    else:
    	return result


def connect(portAddress):
	# Connect to the Open-JIP fluorometer (Teensy Microcontroller)
	global ser
	if(len(portAddress) > 1 and type(portAddress) is not str):
		print("Which port do you want to connect to:")
		for i in range(len(portAddress)):
			print("\t{}. {}".format(i, portAddress[i]))
		portID = input("Port number: ")
		portID = int(portID)
		print("Port {} selected.".format(portAddress[portID]))
	else:
		portID = 0
	ser = serial.Serial(portAddress[portID], usb_baudrate) # Connect to Teensy
	if(ser.is_open):
		print("Connected to Open-JIP fluorometer.")
	else:
		print("Open-JIP USB device not found.")


def measure_fluorescence(readLength):
	# Read fluorescence and create two arrays of corresponding values
	print("Measuring fluorescence, please wait...")
	ser.flush() # Clear serial bus
	time.sleep(1) # Wait for bus to be cleared
	ser.write(b'MF') # Send byte command to Teensy 
	timeStamps = [] # Create array to hold timeStamp
	fluorescenceValues = [] # Create array to hold data
	for _ in range(readLength):
		line = ser.readline() # Read line from Teensy serial bus
		decodedLine = str(line[0:len(line) - 2].decode("utf-8")) # Decde data from serial bus
		splitLine = [float(s) for s in decodedLine.split("\t")] # Split into time and values
		timeStamps.append(splitLine[0])
		fluorescenceValues.append(float(splitLine[1]))
	print("Transient captured.")
	return timeStamps, fluorescenceValues # Return arrays to be passed into csv upload function


def upload(timeStamps, fluorescenceValues):
	# Upload data from fluorescence reading to .csv file with time stamp
	print("Uploading to {}, please wait...".format(fileName))
	timeStamps = ", ".join(str(x) for x in timeStamps) # Join array into a single string seperated by a comma
	fluorescenceValues = ", ".join(str(x) for x in fluorescenceValues) # Same as above for the values
	with open(fileName, 'a') as f:
		try:
			writer = csv.writer(f)
			currentTime = str(datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")) # Get current time for csv
			writer.writerow([currentTime, timeStamps, fluorescenceValues]) # Upload data to a single row
			print("Data written to {}.".format(fileName))

		except:
			print("Failed to write data to {}.".format(fileName))
	f.close()

if __name__ == "__main__":
	port = serial_ports()
	connect(port)
	timeStamps, fluorescenceValues = measure_fluorescence(2000) # Takes the length of the corresponding array in the Teensy script
	upload(timeStamps, fluorescenceValues)

