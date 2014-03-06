/*
    Generated 2014-03-06 17:43:40.231561
*/

#include <stdint.h>

typedef struct Note {
	uint16_t num;
	uint8_t samples[];
} Note;

typedef struct Song {
	uint8_t length;
	Note* notes[];
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
extern Note G7;
extern Note G6;
extern Note G5;
extern Note G4;
extern Note G3;
extern Note A3;
extern Note A5;
extern Note A4;
extern Note E5;
extern Note E4;
extern Note E7;
extern Note E6;
extern Note C7;
extern Note C6;
extern Note C5;
extern Note C4;
extern Note AS4;
extern Note CS5;
extern Note CS4;
extern Note F3;
extern Note F4;
extern Note F5;
extern Note B4;
extern Note B5;
extern Note FS3;
extern Note FS4;
extern Note FS5;
extern Note B3;
extern Note D4;
extern Note D5;
extern Note D3;
extern Song THATSNOMOON;
extern Song PEWPEW;
extern Song ONEUP;
extern Song SCOM;
extern Song CANON;
extern Song JUMP;
