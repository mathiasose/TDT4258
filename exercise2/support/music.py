import random
from math import *
from scale import scale

def sine_samples(frequency=440.0, framerate=44100):
    period = int(framerate / frequency)
    steps = range(period)

    l = [sin(2.0 * pi * frequency * (float(i % period) / float(framerate))) for i in steps]
    l = [0.5 * x for x in l]
    l = [x + 0.5 for x in l]
    l = [0xFF * x for x in l]
    l = [int(x) for x in l]

    return l


def print_structs():
    print "typedef struct Note {"
    print "\t" + "uint16_t num;"
    print "\t" + "uint8_t samples[];"
    print "} Note;"
    print
    print "typedef struct Song {"
    print "\t" + "uint8_t length;"
    print "\t" + "Note* notes[];"
    print "} Song;"


def print_notes(notes):
    for note in notes:
	freq = scale[note]
	samples = sine_samples(freq)
	num = str(len(samples))
	samples = ", ".join(str(s) for s in samples)

	print "Note " + note + " = { " + num + ", { " + samples + " } };"

'''
def print_sheet(sheet, name='TUNESKIT'):
    print "static Note *" + name + "[] = { " + ", ".join("&" + s for s in sheet) + " };"
    print "static uint8_t " + name + "_LEN = " + str(len(sheet)) + ";"
'''

def print_song(name, song):
    print "static Song " + name + " = { " + str(len(song)) +  ", {" + ", ".join("&" + s for s in song) + "} };"

def transpose(sheet, level=1):
    for i, n in enumerate(sheet):
	sheet[i] = n[:-1] + str(int(n[-1]) + level)
    
    return sheet


if __name__ == "__main__":
    songs = dict()
    songs["JUMP"] = "C5 D5 E5 F5 G5 A5 B5 C6".split(" ")
    songs["SCOM"] = transpose("G3 G4 D4 C4 C5 D4 B4 D4 G3 G4 D4 C4 C5 D4 B4 D4 A3 G4 D4 C4 C5 D4 B4 D4 A3 G4 D4 C4 C5 D4 B4 D4 C4 G4 D4 C4 C5 D4 B4 D4 C4 G4 D4 C4 C5 D4 B4 D4 A4 D4 G4 D4 A4 D4 B4 D4 C5 D4 B4 D4 A4 D4 G4 D4 G4".split(" "), 1)
    # 0bSunset
    songs["THATSNOMOON"] = "D4 D4 D4 G4 G4 G4 G4 A4 A4 A4 AS4 C5 AS4 AS4 AS4 AS4 D4 D4 D4 D4 D4 D4 G4 G4 G4 G4 A4 A4 AS4 D4 AS4 G4 D5 C5 C5 C5 C5".split(" ")
    songs["PEWPEW"] = "D5 C5 B4 A4 G4 F4 E4 D4 C4 B3 A3 G3 F3".split(" ")
    songs['ENIGMA'] = "C4 E4 G4 C4 E4 G4 C5 E5 G5 C5 E5 G5 C6 E6 G6 C7 E7 G7".split(" ")
    songs['CANON'] = "A7 FS7 D7 A6 FS6 D5 A5 CS5 E6 A6 CS7 E7 FS7 D7 B7 FS6 D6 B6 ".split(" ")
    print_structs()
    print
    
    all_notes = set()
    for sheet in songs.values():
        for note in sheet:
            all_notes.add(note)
    print_notes(all_notes)
    print
    
    for name, sheet in songs.iteritems():
	print_song(name, sheet)

    print '''
static uint32_t i = 0;
static uint16_t note_c = 0;
static uint16_t c = 0;
static Song* current_song = &SCOM;
static uint16_t current_note_length = 0x27FF;

void note0(Note* n, int offset) {
    *DAC0_CH0DATA = n->samples[offset];
}

void note1(Note* n, int offset) {
    *DAC0_CH1DATA = n->samples[offset];
}

void note(Note* n, int offset) {
    note0(n, offset);
    note1(n, offset);
}
'''
