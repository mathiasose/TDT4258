from math import *

def sine_samples(frequency=440.0, framerate=44100):
    period = int(framerate / frequency)
    steps = range(period)

    l = [sin(2.0 * pi * frequency * (float(i % period) / float(framerate))) for i in steps]
    l = [0.5 * x for x in l]
    l = [x + 0.5 for x in l]
    l = [0xFFF * x for x in l]
    l = [int(x) for x in l]
    return l

octave = {
	    "G3"    : 196.00,
        "G_S3"  : 208.65,
	    "A3"    : 220.00,
        "A_S3"  : 233.08,
	    "B3"    : 246.94,
	    "C4"    : 261.63,
        "C_S4"  : 277.18,
	    "D4"    : 293.66,
        "D_S4"  : 311.13,
	    "E4"    : 329.63,
        "F4"    : 349.23,
        "F_S4"  : 369.99,
	    "G4"    : 392.00,
        "G_S4"  : 415.30,
        "A4"    : 440.00,
        "A_S4"  : 466.16,
        "B5"    : 493.88,
        "C5"    : 523.25
}

print "typedef struct Note {"
print "\t" + "uint8_t num;"
print "\t" + "uint16_t samples[];"
print "} Note;"
print

for note, freq in octave.iteritems():
    samples = sine_samples(freq)
    num = str(len(samples))
    samples = ", ".join(str(s) for s in samples)

    print "Note " + note + " = {\n\t" + num + ",\n\t{ " + samples + " }\n\t};\n"

jacob = "C4 D4 E4 C4 C4 D4 E4 C4 E4 F4 G4 E4 F4 G4 G4 A4 G4 F4 E4 C4 G4 A4 G4 F4 E4 C4 C4 G3 C4 C4 G3 C4".split(" ")

scom = "G3 G4 D4 C4 C5 D4 B3 D4 G3 G4 D4 C4 C5 D4 B3 D4 A3 G4 D4 C4 C5 D4 B3 D4 A3 G4 D4 C4 C5 D4 B3 D4 C4 G4 D4 C4 C5 D4 B3 D4 C4 G4 D4 C4 C5 D4 B3 D4".split(" ")

print "static Note *jacob[] = { " + ", ".join("&" + s for s in jacob) + "};"
print "static uint8_t JACOB_LEN = " + str(len(jacob)) + ";"

print "static Note *scom[] = { " + ", ".join("&" + s for s in scom) + "};"
print "static uint8_t SCOM_LEN = " + str(len(scom)) + ";"
