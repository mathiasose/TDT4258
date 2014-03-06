import random
import os
from math import *
from datetime import datetime
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


def print_header_setup():
    return '''/*
    Generated ''' + str(datetime.now()) + '''
*/

#include <stdint.h>

typedef struct Note {
\tuint16_t num;
\tuint8_t samples[];
} Note;

typedef struct Song {
\tuint8_t length;
\tNote* notes[];
} Song;

extern uint32_t i;
extern uint16_t note_c;
extern uint16_t c;
extern Song* current_song;
extern uint16_t current_note_length;

void setSong(Song*, uint16_t);
void note0(Note*, int);
void note1(Note*, int);
void note(Note*, int);

void playSong(Song*, uint16_t);
void timer_cleanup(void);
'''

def print_implementation_base():
    return '''/*
    Generated ''' + str(datetime.now()) + '''
*/

#include "efm32gg.h"
#include "music.h"
#include "prototypes.h"

uint32_t i = 0;
uint16_t note_c = 0;
uint16_t c = 0;
Song* current_song = &SCOM;
uint16_t current_note_length = 0x24FF;

void setSong(Song* song, uint16_t note_length) {
    current_song = song;
    current_note_length = note_length;
}

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

void playSong(Song* song, uint16_t note_length) {
    setSong(song, note_length);

    setupSleep(0b010);
    setupDAC();
    setupTimer();
    startTimer();
}

void timer_cleanup() {
    stopTimer();
    i = 0;
    c = 0;
    note_c = 0;
}

'''


def print_notes(notes):
    ret = ''
    for note in notes:
	freq = scale[note]
	samples = sine_samples(freq)
	num = str(len(samples))
	samples = ", ".join(str(s) for s in samples)

	ret += "Note " + note + " = { " + num + ", { " + samples + " } };\n"
    return ret


def print_song(name, song):
    return "Song " + name + " = { " + str(len(song)) +  ", {" + ", ".join("&" + s for s in song) + "} };\n"


def transpose(sheet, level=1):
    for i, n in enumerate(sheet):
	sheet[i] = n[:-1] + str(int(n[-1]) + level)
    
    return sheet


if __name__ == "__main__":
    songs = dict()
    songs["JUMP"] = "C5 D5 E5 F5 G5 A5 B5 C6"
    songs["SCOM"] = "G3 G4 D4 C4 C5 D4 B4 D4 G3 G4 D4 C4 C5 D4 B4 D4 A3 G4 D4 C4 C5 D4 B4 D4 A3 G4 D4 C4 C5 D4 B4 D4 C4 G4 D4 C4 C5 D4 B4 D4 C4 G4 D4 C4 C5 D4 B4 D4 A4 D4 G4 D4 A4 D4 B4 D4 C5 D4 B4 D4 A4 D4 G4 D4 G4"
    songs["THATSNOMOON"] = "D4 D4 D4 G4 G4 G4 G4 A4 A4 A4 AS4 C5 AS4 AS4 AS4 AS4 D4 D4 D4 D4 D4 D4 G4 G4 G4 G4 A4 A4 AS4 D4 AS4 G4 D5 C5 C5 C5 C5" # aka 0bSUNSET
    songs["PEWPEW"] = "D5 C5 B4 A4 G4 F4 E4 D4 C4 B3 A3 G3 F3"
    songs['ONEUP'] = "C4 E4 G4 C4 E4 G4 C5 E5 G5 C5 E5 G5 C6 E6 G6 C7 E7 G7"
    songs['CANON'] = "A6 FS6 D6 A5 FS5 D5 A4 CS5 E5 A5 CS6 E6 FS6 D6 B5 FS5 D5 B4 FS4 A4 CS5 FS5 A5 CS6 D6 B5 G5 D5 B4 G4 D4 FS4 A4 D5 FS5 A5 B5 G5 D5 B4 G4 D4 A4 CS5 E5 A5 CS6 E6 A6 A6 A6 A6"

    for key, value in songs.iteritems():
	songs[key] = value.strip().split(" ")

    songs["SCOM"] = transpose(songs["SCOM"], 1)
    songs["CANON"] = transpose(songs["CANON"], -1)

    h = print_header_setup()
    c = print_implementation_base()
    
    all_notes = set()
    for sheet in songs.values():
        for note in sheet:
            all_notes.add(note)
    for note in all_notes:
	h += 'extern Note ' + note + ';\n'
    c += print_notes(all_notes) + '\n'
    
    for name, sheet in songs.iteritems():
	h += 'extern Song ' + name + ';\n'
	c += print_song(name, sheet)

    directory = os.path.dirname(__file__)
    with open(os.path.join(directory, '../src/music.h'), 'w') as h_file:
	h_file.write(h)

    with open(os.path.join(directory, '../src/music.c'), 'w') as c_file:
	c_file.write(c)
