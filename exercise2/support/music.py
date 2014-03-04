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
    print "\t" + "uint8_t num;"
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

def print_song(song, name='TUNEZ'):
    print "static Song " + name + " = { " + str(len(song)) +  ", {" + ", ".join("&" + s for s in song) + "} };"

def transpose(sheet, level=1):
    for i, n in enumerate(sheet):
	sheet[i] = n[:-1] + str(int(n[-1]) + level)
    
    return sheet


if __name__ == "__main__":
    JUMP = "C5 D5 E5 F5 G5 A5 B5 C6".split(" ")
    SCOM = "G3 G4 D4 C4 C5 D4 B4 D4 G3 G4 D4 C4 C5 D4 B4 D4 A3 G4 D4 C4 C5 D4 B4 D4 A3 G4 D4 C4 C5 D4 B4 D4 C4 G4 D4 C4 C5 D4 B4 D4 C4 G4 D4 C4 C5 D4 B4 D4 A4 D4 G4 D4 A4 D4 B4 D4 C5 D4 B4 D4 A4 D4 G4 D4 G4".split(" ")
    # 0bSunset
    THATSNOMOON = "D4 D4 D4 G4 G4 G4 G4 A4 A4 A4 AS4 C5 AS4 AS4 AS4 AS4 D4 D4 D4 D4 D4 D4 G4 G4 G4 G4 A4 A4 AS4 D4 AS4 G4 D5 C5 C5 C5 C5".split(" ")

    SCOM = transpose(SCOM, 1)
    songs =  [(JUMP, 'JUMP'), (SCOM, 'SCOM'), (THATSNOMOON, 'THATSNOMOON')]
    print_structs()
    print
    print_notes(set(JUMP + SCOM + THATSNOMOON))
    print
    #print_sheet(SCOM, 'SCOM')
    for song in songs:
	print_song(song[0], song[1])

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
