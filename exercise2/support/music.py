from math import *
from scale import scale

def sine_samples(frequency=440.0, framerate=44100):
    period = int(framerate / frequency)
    steps = range(period)

    l = [sin(2.0 * pi * frequency * (float(i % period) / float(framerate))) for i in steps]
    l = [0.5 * x for x in l]
    l = [x + 0.5 for x in l]
    l = [0xFFF * x for x in l]
    l = [int(x) for x in l]

    return l

def print_struct():
    print "typedef struct Note {"
    print "\t" + "uint8_t num;"
    print "\t" + "uint16_t samples[];"
    print "} Note;"


def print_notes(notes):
    for note in notes:
	freq = scale[note]
	samples = sine_samples(freq)
	num = str(len(samples))
	samples = ", ".join(str(s) for s in samples)

	print "Note " + note + " = { " + num + ", { " + samples + " } };"


def print_sheet(sheet, name='TUNESKIT'):
    print "static Note *" + name + "[] = { " + ", ".join("&" + s for s in sheet) + " };"
    print "static uint8_t " + name + "_LEN = " + str(len(sheet)) + ";"

if __name__ == "__main__":
    JACOB = "C4 D4 E4 C4 C4 D4 E4 C4 E4 F4 G4 E4 F4 G4 G4 A4 G4 F4 E4 C4 G4 A4 G4 F4 E4 C4 C4 G3 C4 C4 G3 C4".split(" ")
    SCOM = "G3 G4 D4 C4 C5 D4 B3 D4 G3 G4 D4 C4 C5 D4 B3 D4 A3 G4 D4 C4 C5 D4 B3 D4 A3 G4 D4 C4 C5 D4 B3 D4 C4 G4 D4 C4 C5 D4 B3 D4 C4 G4 D4 C4 C5 D4 B3 D4".split(" ")

    print_struct()
    print
    print_notes(set(JACOB))
    print
    print_sheet(JACOB, 'JACOB')
