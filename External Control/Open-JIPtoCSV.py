# 
import csv
import serial
import time
import datetime
from time import strftime

usb_address = '/dev/usbmodem81502101' # See Tools/Port in arduino IDE for port address
usb_baudrate = 115200 # Baudrate to match teensy

ser = serial.Serial(usb_address, usb_baudrate) # Connect to teensy

def measure_fluorescence():
	ser.flush() # Clear serial bus
	time.sleep(1) # Wait for bus to be cleared
	ser.write(b'MF') # Send byte command to teensy 
    timeStamps = [] # Create timeStamp
    fluorescenceValues = []
	for _ in range(2000):
		fluorescence_bytes = ser.readline()
        decoded_fluorescence_bytes = str(fluorescence_bytes[0:len(fluorescence_bytes) - 2].decode("utf-8"))
        data_split = [float(s) for s in decoded_fluorescence_bytes.split("\t")]
        x_data = data_split[0]
        y_data = float(data_split[1])
        time_stamps.append(x_data)
        values.append(y_data)


def upload():
    global day_night
    # time_stamps = ", ".join(str(x) for x in time_stamps)
    # values = ", ".join(str(x) for x in values)
    worksheet_name = "Open-JIP Data.csv"
    with open(worksheet_name, 'a') as f:
        try:
            writer = csv.writer(f)
            spreadsheet_time = str(datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S"))
            writer.writerow([spreadsheet_time, time_stamps, values])
            print("Written to local csv")

        except:
            print("Failed to write to local csv file...")
    f.close()

if __name__ == "__main__":
    measure_fluorescence()
    upload()

