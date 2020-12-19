import plotly.graph_objects as go
import plotly
import csv

fileName = "Open-JIP_Data.csv"


def get_data_from_csv(fileName):
    readTimes = []
    timeStamps = []
    fluorescenceValues = []
    with open(fileName, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            readTimes.append(row[0][11:])
            timeStamps.append([float(s) for s in row[1].split(',')])
            fluorescenceValues.append([float(s) for s in row[2].split(',')])
    f.close()
    return readTimes, timeStamps, fluorescenceValues


def plot_transients(readTimes, timeStamps, fluorescenceValues):

    updatemenus = list([
        dict(active=1,
             buttons=list([
                 dict(label='Logarithmic Scale',
                      method='update',
                      args=[{'visible': [True, True]},
                            {'xaxis': {'type': 'log'}}]),
                 dict(label='Linear Scale',
                      method='update',
                      args=[{'visible': [True, False]},
                            {'xaxis': {'type': 'linear'}}])
             ]),
             )
    ])

    data = []
    for index, (readTime, times, values) in enumerate(zip(readTimes, timeStamps, fluorescenceValues)):
        data.append(go.Scatter(x=times, y=values, mode='markers',
                               name="Transient{} at {}".format(index+1, readTime)))

    layout = dict(updatemenus=updatemenus, title='Open-JIP Transient')
    fig = go.Figure(data=data, layout=layout)

    fig.show()


if __name__ == "__main__":
    readTimes, timeStamps, fluorescenceValues = get_data_from_csv(fileName)
    plot_transients(readTimes, timeStamps, fluorescenceValues)
