# <Open-JIPtoCSV Operates "Open-JIP" which is an Open-source Chlorophyll fluorometer>
# Copyright (C) <2020>  <Harvey Bates>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>

# For more information contact: harvey_bates@hotmail.com
import sys
import csv
import glob
import serial
import time
import datetime
from time import strftime
import plotly
import plotly.graph_objects as go
import csv
import atexit

usb_baudrate = 115200  # Baudrate to match Teensy
fileName = "Open-JIP_Data.csv"  # Filename of output .csv file
fo_pos = 3

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
            if("Bluetooth" not in port):  # Excludes bluetooth port on Mac OS
                result.append(port)
        except (OSError, serial.SerialException):
            pass
    if(len(result) == 0):
        raise IndexError("No USB devices found. Ensure Open-JIP is pugged in.")
    else:
        return result


def connect(portAddress):
        # Connect to the Open-JIP fluorometer (Teensy Microcontroller)
    global openJIP
    if(len(portAddress) > 1 and type(portAddress) is not str):
        print("Which port do you want to connect to:")
        for i in range(len(portAddress)):
            print("\t{}. {}".format(i, portAddress[i]))
        portID = input("Port number: ")
        portID = int(portID)
        print("Port {} selected.".format(portAddress[portID]))
    else:
        portID = 0
    openJIP = serial.Serial(
        portAddress[portID], usb_baudrate)  # Connect to Teensy
    if(openJIP.is_open):
        print("Connected to Open-JIP fluorometer.")
    else:
        print("Open-JIP USB device not found.")

def set_gain():
    gain = input("Set the detection gain: (1 (Lowest) - 4 (Highest))")
    if(int(gain) > 0 and int(gain) <= 4):
        openJIP.flush()
        time.sleep(0.1)
        message = "F" + gain
        openJIP.write(bytes(message.encode('utf-8')))
        print("Gain set to: {}".format(gain))
    else:
        print("Invalid detection gain. Default settings will be used.")

def set_intensity():
    intensity = input("Set the actinic LED intensity: (1 (Lowest) - 4 (Highest))")
    if(int(intensity) > 0 and int(intensity) <= 4):
        openJIP.flush()
        time.sleep(0.1)
        message = "A" + intensity
        openJIP.write(bytes(message.encode('utf-8')))
        print("Actinic intensity set to: {}".format(intensity))
    else:
        print("Invalid actinic intensity. Default settings will be used.") 

def measure_fluorescence(readLength):
    # Read fluorescence and create two arrays of corresponding values
    print("Measuring fluorescence, please wait...")
    openJIP.flush()  # Clear serial bus
    time.sleep(1)  # Wait for bus to be cleared
    openJIP.write(b'MF')  # Send byte command to Teensy
    timeStamps = []  # Create array to hold timeStamp
    fluorescenceValues = []  # Create array to hold data
    for _ in range(readLength):
        line = openJIP.readline()  # Read line from Teensy serial bus
        # Decde data from serial bus
        decodedLine = str(line[0:len(line) - 2].decode("utf-8"))
        # Split into time and values
        splitLine = [float(s) for s in decodedLine.split("\t")]
        timeStamps.append(splitLine[0])
        fluorescenceValues.append(float(splitLine[1]))
    print("Transient captured.")
    # Return arrays to be passed into csv upload function
    return timeStamps, fluorescenceValues


def calculate_parameters(fluorescenceValues, timeStamps):
    fo = fluorescenceValues[fo_pos]
    fm = max(fluorescenceValues[2:])
    fj_found = False
    fi_found = False

    for i in range(len(fluorescenceValues)):
        if(not fj_found and int(timeStamps[i]) == 2):
            fj = fluorescenceValues[i]
            fj_time = timeStamps[i]
            fj_found = True
        elif(not fi_found and int(timeStamps[i]) == 30):
            fi = fluorescenceValues[i]
            fi_time = timeStamps[i]
            fi_found = True
    
    fv = (fm - fo)
    quantumYield = fv / fm
    
    print("Fo: {}".format(fo))
    print("Fj: {} at {}".format(fj, fj_time))
    print("Fi: {} at {}".format(fi, fi_time))
    print("Fm: {}". format(fm))
    print("Fv: {}".format(fv))
    print("Quantum yield: {}".format(round(quantumYield, 3)))


def upload(timeStamps, fluorescenceValues):
    # Upload data from fluorescence reading to .csv file with time stamp
    print("Uploading to {}, please wait...".format(fileName))
    # Join array into a single string seperated by a comma
    timeStamps = ", ".join(str(x) for x in timeStamps)
    # Same as above for the values
    fluorescenceValues = ", ".join(str(x) for x in fluorescenceValues)
    with open(fileName, 'a') as f:
        try:
            writer = csv.writer(f)
            currentTime = str(datetime.datetime.now().strftime(
                "%Y/%m/%d %H:%M:%S"))  # Get current time for csv
            # Upload data to a single row
            writer.writerow([currentTime, timeStamps, fluorescenceValues])
            print("Data written to {}.".format(fileName))

        except:
            print("Failed to write data to {}.".format(fileName))
    f.close()


def query_user_plot():
    # Get an input from the user to determine if they want to plot the data
    plotData = input(
        "Would you like to plot data from {}? (y/n)".format(fileName))
    if(plotData == "Y" or plotData == "y"):
        get_data_from_csv(fileName)
        readTimes, timeStamps, fluorescenceValues = get_data_from_csv(fileName)
        plot_transients(readTimes, timeStamps, fluorescenceValues)
    else:
        print("Exiting.")


def get_data_from_csv(fileName):
    # Read the csv file and create arrays of values
    readTimes = []
    timeStamps = []
    fluorescenceValues = []
    with open(fileName, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            if row:
                readTimes.append(row[0][11:]) # Get the date/time stamp
                timeStamps.append([float(s) for s in row[1].split(',')])
                fluorescenceValues.append([float(s)
                                           for s in row[2].split(',')])
            else:
                raise IndexError("No data found in {}.".format(fileName))
    f.close()
    return readTimes, timeStamps, fluorescenceValues


def plot_transients(readTimes, timeStamps, fluorescenceValues):
    # Plot data from all the transients found in the csv file
    print("Plotting data from {}, please wait...".format(fileName))
    updatemenus = list([
        dict(active=1,
             buttons=list([
                 dict(label='Logarithmic Scale',
                      method='update',
                      args=[{'visible': [True, True]},
                            {'xaxis': {'type': 'log'}}]),
                 dict(label='Linear Scale',
                      method='update',
                      args=[{'visible': [True, True]},
                            {'xaxis': {'type': 'linear'}}])
             ]),
             )
    ])

    data = []
    for index, (readTime, times, values) in enumerate(zip(readTimes, timeStamps, fluorescenceValues)):
        data.append(go.Scatter(x=times, y=values, mode='markers',
                               name="Transient{} at {}".format(index+1, readTime)))
    layout = dict(updatemenus=updatemenus, title='Open-JIP Transients')
    fig = go.Figure(data=data, layout=layout)
    fig.update_xaxes(title_text="Time (ms)")
    fig.update_yaxes(title_text="Fluorescence (V)")
    fig.layout.template = "seaborn"
    fig.show()

def close():
    if(openJIP.is_open):
        openJIP.close()
        print("Exited cleanly.")

atexit.register(close)

if __name__ == "__main__":
    port = serial_ports()
    connect(port)
    measure = input("Do you want measure an OJIP curve now? (y/n)")
    if(measure == "y" or measure == "Y"):
        # Takes the length of the corresponding array in the Teensy script
        adjust = input("Set gain and actinic intensity? (y/n)")
        if(adjust == "y" or adjust == "Y"):
            set_intensity()
            set_gain()
        timeStamps, fluorescenceValues = measure_fluorescence(2000)
        calculate_parameters(fluorescenceValues, timeStamps)
        upload(timeStamps, fluorescenceValues)
        query_user_plot()
    else:
        print("Exiting...")
