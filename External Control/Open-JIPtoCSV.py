# 
import csv
import serial
import time
import datetime
from time import strftime

usb_address = '/dev/usbmodem81502101' # See Tools/Port in arduino IDE for port address
usb_baudrate = 115200 # Baudrate to match teensy

ser = serial.Serial(usb_address, usb_baudrate) # Connect to teensy

fileName = "Open-JIP_Data.csv"

def measure_fluorescence(readLength):
    ser.flush() # Clear serial bus
    time.sleep(1) # Wait for bus to be cleared
    ser.write(b'MF') # Send byte command to teensy 
    timeStamps = [] # Create array to hold timeStamp
    fluorescenceValues = [] # Create array to hold data
    for _ in range(readLength):
        line = ser.readline()
        decodedLine = str(line[0:len(line) - 2].decode("utf-8"))
        splitLine = [float(s) for s in decodedLine.split("\t")]
        timeStamps.append(splitLine[0])
        fluorescenceValues.append(float(splitLine[1]))
    return timeStamps, fluorescenceValues

def upload(timeStamps, fluorescenceValues):
    timeStamps = ", ".join(str(x) for x in time_stamps)
    fluorescenceValues = ", ".join(str(x) for x in values)
    worksheet_name = fileName
    with open(worksheet_name, 'a') as f:
        try:
            writer = csv.writer(f)
            currentTime = str(datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S"))
            writer.writerow([currentTime, timeStamps, fluorescenceValues])
            print("Written to local .csv")

        except:
            print("Failed to write to local csv file...")
    f.close()

if __name__ == "__main__":
    timeStamps, fluorescenceValues = measure_fluorescence(2000)
    upload(timeStamps, fluorescenceValues)

