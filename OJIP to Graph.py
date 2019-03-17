import serial
import time
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/cu.usbmodem14101', 74880)

def measureOJIP():
    global xdataArray
    global ydataArray
    ser.flush()
    time.sleep(1)
    ser.write(b'MF')
    time.sleep(1)
    xdataArray = []
    ydataArray = []
    for i in range(1100):
        OJIP_bytes = ser.readline()
        decoded_OJIP_bytes = str(OJIP_bytes[0:len(OJIP_bytes) - 2].decode("utf-8"))
        dataSplit = [float(s) for s in decoded_OJIP_bytes.split("\t")]
        xdata = dataSplit[0]
        ydata = dataSplit[1]
        xdataArray.append(xdata)
        ydataArray.append(ydata)


measureOJIP()
plt.figure(figsize=(5,5))
plt.plot()
plt.semilogx(xdataArray, ydataArray, label='OJIP', color='xkcd:blue', marker=None)
plt.ylabel("Bits (a.u)")
plt.xlabel("Time (ms)")
plt.xlim(0.04, 1000)
plt.yticks([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000])
plt.legend(loc = 'best')
plt.show()
