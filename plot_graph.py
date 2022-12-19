import matplotlib.pyplot as plt
import pandas as pd
from os import environ


def suppress_qt_warnings():
    environ["QT_DEVICE_PIXEL_RATIO"] = "0"
    environ["QT_AUTO_SCREEN_SCALE_FACTOR"] = "1"
    environ["QT_SCREEN_SCALE_FACTORS"] = "1"
    environ["QT_SCALE_FACTOR"] = "1"


if __name__ == "__main__":
    suppress_qt_warnings()
    # Read the data from the csv file
    df = pd.read_csv('./cmake-build-debug/times.csv')

    # Get the x and y data
    x = df.iloc[:, 0]
    y = df.iloc[:, 1]

    # Plot the data
    plt.plot(x, y, 'o')
    plt.show()
