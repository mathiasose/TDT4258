from math import *
from itertools import *

def sine_samples(frequency=440.0, framerate=44100):
    period = int(framerate / frequency)
    steps = range(period)

    l = [sin(2.0 * pi * frequency * float(i % period) / framerate) for i in steps]
    l = [0.5 * x for x in l]
    l = [x + 0.5 for x in l]
    l = [0xFFF * x for x in l]
    l = [int(x) for x in l]
    return l

c_maj = {   "C" : 440.0 ,
	    "D" : 293.66,
	    "E" : 329.63,
	    "F" : 349.23,
	    "G" : 392.0,
	    "A" : 440.0,
	    "B1" : 493.88,
	    "C1" : 523.25
}

for note, freq in c_maj.iteritems():
    samples = sine_samples(freq)

    print "struct", note, "{"
    print "\t" + "uint16_t num =", str(len(samples)) + ";"
    print "\t" + "uint16_t samples[] = {",
    print ", ".join(str(f) for f in samples), "};"
    print "};"
