import os

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from pylab import *

from scale import scale
from music import sine_samples

if __name__ == "__main__":
    # plot for report
    plt.plot(sine_samples(scale["A4"]), '.')
    x1,x2,y1,y2 = plt.axis()
    plt.axis((x1,x2,0,0x100))
    plt.axes = plt.gca()
    plt.xlabel('Samples')
    plt.title('Samples producing A4')
    plt.ylabel('Amplitude (hexadecimal)')
    plt.axes.get_yaxis().set_major_locator(ticker.MultipleLocator(0x10))
    plt.axes.get_yaxis().set_major_formatter(ticker.FormatStrFormatter("%x"))
#    plt.show()
    path = os.path.join(os.path.dirname(__file__), '../report/img/A4.png') 
    plt.savefig(path, bbox_inches='tight')
