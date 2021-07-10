# External Control

To simplify the use of Open-JIP, this Python script allows users to run OJIP fluorescence measurements without the need to edit any software or firmware. 

This program provides a guided intoduction into:

1. Taking a measurement
2. Saving the data from a captured OJIP transient locally (`.csv` form)
3. Plotting the data from consecutive measurments (i.e. if you take multiple measurments in one experiment or trial you can compare them automatically)

## Getting Started

Navigate to the `External Control` folder in your compters terminal and run the following command to install the required Python modules.

```bash
pip install -r requirements.txt
# or (depending on your python installation)
pip3 install -r requirments.txt
```

If you see an error that there is no command pip3, then you need to install Python and pip on your machine. Here is a [link](https://www.makeuseof.com/tag/install-pip-for-python/) explaining how this can be done in a few minutes.

## Operating

Ensuring the Open-JIP device is plugged into our computer and ready to measure, we can run the program in the terminal with the command:

```bash
python3 Open-JIP.py
# or (depending on your python installation)
python Open-JIP.py
```

The program will run you through a series of questions to understand what kind of settings and type of measurement you wish to conduct.


