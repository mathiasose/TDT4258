/*
    Generated 2014-03-07 14:37:58.476086
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

Note G7 = { 14, { 127, 182, 226, 251, 252, 227, 184, 129, 74, 29, 3, 2, 25, 69 } };
Note G6 = { 28, { 127, 155, 182, 206, 226, 242, 251, 254, 252, 242, 227, 208, 184, 157, 129, 100, 74, 49, 29, 13, 3, 0, 2, 11, 25, 45, 69, 95 } };
Note G5 = { 56, { 127, 141, 155, 169, 182, 195, 206, 217, 226, 235, 242, 247, 251, 254, 254, 254, 252, 248, 242, 236, 227, 218, 208, 196, 184, 171, 157, 143, 129, 115, 100, 87, 74, 61, 49, 38, 29, 20, 13, 7, 3, 1, 0, 0, 2, 6, 11, 17, 25, 35, 45, 56, 69, 82, 95, 109 } };
Note G4 = { 112, { 127, 134, 141, 148, 155, 162, 169, 176, 182, 188, 195, 200, 206, 212, 217, 222, 226, 231, 235, 238, 242, 245, 247, 249, 251, 253, 254, 254, 254, 254, 254, 253, 252, 250, 248, 245, 242, 239, 236, 232, 227, 223, 218, 213, 208, 202, 196, 190, 184, 177, 171, 164, 157, 150, 143, 136, 129, 122, 115, 107, 100, 94, 87, 80, 74, 67, 61, 55, 49, 44, 38, 33, 29, 24, 20, 17, 13, 10, 7, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 4, 6, 8, 11, 14, 17, 21, 25, 30, 35, 40, 45, 51, 56, 62, 69, 75, 82, 88, 95, 102, 109, 116 } };
Note G3 = { 225, { 127, 131, 134, 138, 141, 145, 148, 152, 155, 159, 162, 166, 169, 172, 176, 179, 182, 185, 188, 192, 195, 198, 200, 203, 206, 209, 212, 214, 217, 219, 222, 224, 226, 229, 231, 233, 235, 237, 238, 240, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 252, 252, 251, 250, 249, 248, 247, 245, 244, 242, 241, 239, 237, 236, 234, 232, 230, 227, 225, 223, 221, 218, 216, 213, 210, 208, 205, 202, 199, 196, 193, 190, 187, 184, 180, 177, 174, 171, 167, 164, 160, 157, 154, 150, 147, 143, 139, 136, 132, 129, 125, 122, 118, 115, 111, 107, 104, 100, 97, 94, 90, 87, 83, 80, 77, 74, 70, 67, 64, 61, 58, 55, 52, 49, 46, 44, 41, 38, 36, 33, 31, 29, 27, 24, 22, 20, 18, 17, 15, 13, 12, 10, 9, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 14, 16, 17, 19, 21, 23, 25, 28, 30, 32, 35, 37, 40, 42, 45, 48, 51, 54, 56, 59, 62, 66, 69, 72, 75, 78, 82, 85, 88, 92, 95, 99, 102, 106, 109, 113, 116, 120, 123 } };
Note A3 = { 200, { 127, 131, 135, 139, 143, 147, 151, 155, 159, 162, 166, 170, 174, 178, 181, 185, 188, 192, 195, 199, 202, 205, 208, 211, 214, 217, 220, 222, 225, 228, 230, 232, 234, 237, 239, 240, 242, 244, 245, 247, 248, 249, 250, 251, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 253, 252, 252, 251, 250, 248, 247, 246, 244, 243, 241, 239, 237, 235, 233, 231, 228, 226, 223, 220, 218, 215, 212, 209, 206, 203, 199, 196, 193, 189, 186, 182, 178, 175, 171, 167, 163, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 104, 100, 96, 92, 89, 85, 81, 77, 74, 70, 67, 63, 60, 56, 53, 50, 47, 44, 41, 38, 35, 32, 30, 27, 25, 22, 20, 18, 16, 14, 12, 10, 9, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 7, 8, 9, 11, 13, 15, 16, 19, 21, 23, 25, 28, 30, 33, 36, 39, 41, 44, 48, 51, 54, 57, 61, 64, 68, 71, 75, 78, 82, 86, 90, 94, 97, 101, 105, 109, 113, 117, 121 } };
Note A5 = { 50, { 127, 143, 159, 174, 188, 202, 214, 225, 234, 242, 248, 252, 254, 254, 252, 248, 243, 235, 226, 215, 203, 189, 175, 160, 144, 128, 112, 96, 81, 67, 53, 41, 30, 20, 12, 6, 2, 0, 0, 2, 5, 11, 19, 28, 39, 51, 64, 78, 94, 109 } };
Note A4 = { 100, { 127, 135, 143, 151, 159, 166, 174, 181, 188, 195, 202, 208, 214, 220, 225, 230, 234, 239, 242, 245, 248, 250, 252, 253, 254, 254, 254, 254, 252, 251, 248, 246, 243, 239, 235, 231, 226, 220, 215, 209, 203, 196, 189, 182, 175, 167, 160, 152, 144, 136, 128, 120, 112, 104, 96, 89, 81, 74, 67, 60, 53, 47, 41, 35, 30, 25, 20, 16, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 2, 3, 5, 8, 11, 15, 19, 23, 28, 33, 39, 44, 51, 57, 64, 71, 78, 86, 94, 101, 109, 117 } };
Note E5 = { 66, { 127, 139, 151, 162, 174, 185, 195, 205, 214, 222, 230, 237, 242, 247, 250, 253, 254, 254, 254, 252, 249, 244, 239, 233, 226, 218, 209, 200, 189, 179, 168, 156, 144, 132, 120, 108, 97, 85, 74, 63, 53, 44, 35, 27, 20, 14, 9, 5, 2, 0, 0, 0, 1, 4, 8, 12, 18, 25, 32, 41, 50, 60, 70, 81, 93, 104 } };
Note E4 = { 133, { 127, 133, 139, 145, 151, 157, 162, 168, 174, 179, 185, 190, 195, 200, 205, 210, 214, 218, 222, 226, 230, 233, 237, 239, 242, 245, 247, 249, 250, 252, 253, 254, 254, 254, 254, 254, 254, 253, 252, 250, 249, 247, 244, 242, 239, 236, 233, 230, 226, 222, 218, 214, 209, 204, 200, 195, 189, 184, 179, 173, 168, 162, 156, 150, 144, 138, 132, 126, 120, 114, 108, 103, 97, 91, 85, 80, 74, 69, 63, 58, 53, 49, 44, 39, 35, 31, 27, 24, 20, 17, 14, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 3, 4, 6, 8, 10, 12, 15, 18, 21, 25, 29, 32, 37, 41, 45, 50, 55, 60, 65, 70, 76, 81, 87, 93, 99, 104, 110, 116 } };
Note E7 = { 16, { 127, 174, 214, 242, 254, 249, 226, 189, 144, 97, 53, 20, 2, 1, 18, 50 } };
Note E6 = { 33, { 127, 151, 174, 195, 214, 230, 242, 250, 254, 254, 249, 239, 226, 209, 189, 168, 144, 120, 97, 74, 53, 35, 20, 9, 2, 0, 1, 8, 18, 32, 50, 70, 93 } };
Note C7 = { 21, { 127, 164, 199, 226, 245, 254, 251, 238, 214, 183, 147, 109, 73, 41, 17, 3, 0, 8, 26, 53, 87 } };
Note C6 = { 42, { 127, 146, 164, 182, 199, 213, 226, 237, 245, 251, 254, 254, 251, 246, 238, 227, 214, 200, 183, 166, 147, 128, 109, 91, 73, 56, 41, 28, 17, 9, 3, 0, 0, 2, 8, 15, 26, 39, 53, 69, 87, 105 } };
Note C5 = { 84, { 127, 136, 146, 155, 164, 173, 182, 191, 199, 206, 213, 220, 226, 232, 237, 242, 245, 249, 251, 253, 254, 254, 254, 253, 251, 249, 246, 242, 238, 233, 227, 221, 214, 207, 200, 192, 183, 175, 166, 157, 147, 138, 128, 119, 109, 100, 91, 82, 73, 65, 56, 49, 41, 35, 28, 23, 17, 13, 9, 6, 3, 1, 0, 0, 0, 1, 2, 5, 8, 11, 15, 20, 26, 32, 39, 46, 53, 61, 69, 78, 87, 96, 105, 115 } };
Note C4 = { 168, { 127, 132, 136, 141, 146, 151, 155, 160, 164, 169, 173, 178, 182, 186, 191, 195, 199, 202, 206, 210, 213, 217, 220, 223, 226, 229, 232, 235, 237, 240, 242, 244, 246, 247, 249, 250, 251, 252, 253, 254, 254, 254, 254, 254, 254, 254, 253, 252, 251, 250, 249, 248, 246, 244, 242, 240, 238, 235, 233, 230, 227, 224, 221, 218, 214, 211, 207, 204, 200, 196, 192, 188, 183, 179, 175, 170, 166, 161, 157, 152, 147, 143, 138, 133, 128, 124, 119, 114, 109, 105, 100, 95, 91, 86, 82, 77, 73, 69, 65, 60, 56, 53, 49, 45, 41, 38, 35, 31, 28, 25, 23, 20, 17, 15, 13, 11, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 5, 6, 8, 9, 11, 13, 15, 18, 20, 23, 26, 29, 32, 35, 39, 42, 46, 49, 53, 57, 61, 65, 69, 74, 78, 83, 87, 92, 96, 101, 105, 110, 115, 120 } };
Note AS4 = { 94, { 127, 135, 144, 152, 160, 169, 176, 184, 192, 199, 206, 212, 218, 224, 229, 234, 238, 242, 246, 248, 251, 253, 254, 254, 254, 254, 253, 251, 249, 247, 243, 240, 235, 231, 226, 220, 214, 208, 201, 194, 186, 179, 171, 163, 155, 146, 138, 130, 121, 113, 104, 96, 88, 80, 72, 65, 57, 50, 44, 38, 32, 26, 21, 17, 13, 9, 6, 4, 2, 1, 0, 0, 0, 1, 2, 4, 7, 10, 13, 17, 22, 27, 32, 38, 44, 51, 58, 65, 73, 81, 89, 97, 105, 113 } };
Note CS5 = { 79, { 127, 137, 147, 157, 167, 176, 185, 194, 202, 210, 218, 224, 231, 236, 241, 245, 249, 251, 253, 254, 254, 254, 253, 251, 248, 244, 240, 235, 229, 223, 216, 208, 200, 192, 183, 174, 164, 155, 145, 135, 125, 115, 105, 95, 85, 76, 67, 58, 50, 42, 35, 28, 22, 17, 12, 8, 5, 2, 1, 0, 0, 0, 2, 4, 7, 11, 15, 20, 26, 33, 40, 47, 55, 64, 73, 82, 92, 101, 111 } };
Note CS4 = { 159, { 127, 132, 137, 142, 147, 152, 157, 162, 167, 171, 176, 181, 185, 190, 194, 198, 202, 206, 210, 214, 218, 221, 224, 228, 231, 233, 236, 239, 241, 243, 245, 247, 249, 250, 251, 252, 253, 254, 254, 254, 254, 254, 254, 253, 253, 252, 251, 249, 248, 246, 244, 242, 240, 238, 235, 232, 229, 226, 223, 219, 216, 212, 208, 205, 200, 196, 192, 188, 183, 179, 174, 169, 164, 160, 155, 150, 145, 140, 135, 130, 125, 120, 115, 110, 105, 100, 95, 90, 85, 81, 76, 71, 67, 62, 58, 54, 50, 46, 42, 38, 35, 31, 28, 25, 22, 19, 17, 14, 12, 10, 8, 6, 5, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 9, 11, 13, 15, 18, 20, 23, 26, 29, 33, 36, 40, 43, 47, 51, 55, 60, 64, 68, 73, 77, 82, 87, 92, 97, 101, 106, 111, 116, 121 } };
Note F3 = { 252, { 127, 130, 133, 137, 140, 143, 146, 149, 152, 155, 158, 161, 165, 168, 171, 173, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 214, 216, 218, 220, 222, 225, 227, 228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 244, 246, 247, 248, 249, 250, 250, 251, 252, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 246, 245, 243, 242, 241, 239, 238, 236, 234, 233, 231, 229, 227, 225, 223, 221, 219, 217, 214, 212, 209, 207, 205, 202, 199, 197, 194, 191, 189, 186, 183, 180, 177, 174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 137, 134, 131, 128, 125, 122, 118, 115, 112, 109, 106, 103, 100, 96, 93, 90, 87, 84, 81, 78, 75, 73, 70, 67, 64, 61, 59, 56, 53, 51, 48, 46, 43, 41, 39, 37, 34, 32, 30, 28, 26, 24, 22, 21, 19, 17, 16, 14, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 16, 17, 19, 21, 23, 24, 26, 28, 30, 32, 35, 37, 39, 41, 44, 46, 49, 51, 54, 56, 59, 62, 65, 67, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 113, 116, 119, 122 } };
Note F4 = { 126, { 127, 133, 140, 146, 152, 158, 165, 171, 176, 182, 188, 193, 199, 204, 209, 214, 218, 222, 227, 230, 234, 237, 240, 243, 246, 248, 250, 251, 252, 253, 254, 254, 254, 254, 254, 253, 251, 250, 248, 246, 243, 241, 238, 234, 231, 227, 223, 219, 214, 209, 205, 199, 194, 189, 183, 177, 171, 165, 159, 153, 147, 141, 134, 128, 122, 115, 109, 103, 96, 90, 84, 78, 73, 67, 61, 56, 51, 46, 41, 37, 32, 28, 24, 21, 17, 14, 11, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 4, 6, 8, 10, 13, 16, 19, 23, 26, 30, 35, 39, 44, 49, 54, 59, 65, 70, 76, 82, 88, 94, 100, 106, 113, 119 } };
Note F5 = { 63, { 127, 140, 152, 165, 176, 188, 199, 209, 218, 227, 234, 240, 246, 250, 252, 254, 254, 254, 251, 248, 243, 238, 231, 223, 214, 205, 194, 183, 171, 159, 147, 134, 122, 109, 96, 84, 73, 61, 51, 41, 32, 24, 17, 11, 7, 3, 1, 0, 0, 1, 4, 8, 13, 19, 26, 35, 44, 54, 65, 76, 88, 100, 113 } };
Note B4 = { 89, { 127, 136, 145, 154, 162, 171, 179, 187, 195, 202, 209, 216, 222, 228, 233, 238, 242, 246, 249, 251, 253, 254, 254, 254, 254, 252, 250, 248, 244, 241, 236, 231, 226, 220, 214, 207, 200, 192, 184, 176, 168, 159, 151, 142, 133, 124, 115, 106, 97, 89, 80, 72, 64, 56, 49, 42, 36, 30, 24, 19, 15, 11, 7, 4, 2, 1, 0, 0, 0, 1, 2, 5, 7, 11, 15, 19, 24, 30, 36, 43, 49, 57, 64, 72, 81, 89, 98, 107, 115 } };
Note B5 = { 44, { 127, 145, 162, 179, 195, 209, 222, 233, 242, 249, 253, 254, 254, 250, 244, 236, 226, 214, 200, 184, 168, 151, 133, 115, 97, 80, 64, 49, 36, 24, 15, 7, 2, 0, 0, 2, 7, 15, 24, 36, 49, 64, 81, 98 } };
Note FS3 = { 238, { 127, 130, 134, 137, 140, 144, 147, 150, 154, 157, 160, 163, 167, 170, 173, 176, 179, 182, 185, 188, 191, 194, 197, 200, 202, 205, 208, 210, 213, 215, 218, 220, 222, 224, 227, 229, 231, 233, 234, 236, 238, 239, 241, 242, 244, 245, 246, 248, 249, 250, 250, 251, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 245, 244, 243, 241, 240, 238, 236, 235, 233, 231, 229, 227, 225, 223, 220, 218, 216, 213, 211, 208, 206, 203, 200, 197, 195, 192, 189, 186, 183, 180, 177, 174, 170, 167, 164, 161, 158, 154, 151, 148, 144, 141, 138, 134, 131, 128, 124, 121, 118, 114, 111, 108, 104, 101, 98, 94, 91, 88, 85, 82, 78, 75, 72, 69, 66, 63, 61, 58, 55, 52, 49, 47, 44, 42, 39, 37, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 14, 16, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 38, 40, 43, 45, 48, 51, 53, 56, 59, 62, 65, 68, 71, 74, 77, 80, 83, 86, 89, 93, 96, 99, 102, 106, 109, 112, 116, 119, 122 } };
Note FS4 = { 119, { 127, 134, 140, 147, 154, 160, 167, 173, 179, 185, 191, 197, 202, 208, 213, 218, 222, 227, 231, 234, 238, 241, 244, 246, 249, 250, 252, 253, 254, 254, 254, 254, 254, 253, 251, 250, 248, 245, 243, 240, 237, 233, 229, 225, 220, 216, 211, 206, 200, 195, 189, 183, 177, 170, 164, 158, 151, 144, 138, 131, 124, 118, 111, 104, 98, 91, 85, 78, 72, 66, 61, 55, 49, 44, 39, 34, 30, 26, 22, 18, 15, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 5, 7, 10, 12, 15, 19, 23, 27, 31, 35, 40, 45, 51, 56, 62, 68, 74, 80, 86, 93, 99, 106, 112, 119 } };
Note FS5 = { 59, { 127, 140, 154, 167, 179, 191, 202, 213, 222, 231, 238, 244, 249, 252, 254, 254, 254, 251, 248, 243, 237, 229, 220, 211, 200, 189, 177, 164, 151, 138, 124, 111, 98, 85, 72, 61, 49, 39, 30, 22, 15, 9, 5, 2, 0, 0, 1, 3, 7, 12, 19, 27, 35, 45, 56, 68, 80, 93, 106 } };
Note B3 = { 178, { 127, 131, 136, 140, 145, 149, 154, 158, 162, 167, 171, 175, 179, 183, 187, 191, 195, 199, 202, 206, 209, 213, 216, 219, 222, 225, 228, 231, 233, 236, 238, 240, 242, 244, 246, 247, 249, 250, 251, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 253, 252, 251, 250, 249, 248, 246, 244, 243, 241, 239, 236, 234, 231, 229, 226, 223, 220, 217, 214, 210, 207, 204, 200, 196, 192, 188, 184, 180, 176, 172, 168, 164, 159, 155, 151, 146, 142, 137, 133, 128, 124, 119, 115, 110, 106, 102, 97, 93, 89, 84, 80, 76, 72, 68, 64, 60, 56, 53, 49, 46, 42, 39, 36, 33, 30, 27, 24, 21, 19, 17, 15, 12, 11, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 5, 6, 7, 9, 11, 13, 15, 17, 19, 22, 24, 27, 30, 33, 36, 39, 43, 46, 49, 53, 57, 61, 64, 68, 72, 76, 81, 85, 89, 93, 98, 102, 107, 111, 115, 120 } };
Note D4 = { 150, { 127, 132, 138, 143, 148, 153, 159, 164, 169, 174, 179, 184, 188, 193, 197, 202, 206, 210, 214, 218, 222, 225, 228, 232, 235, 237, 240, 242, 244, 246, 248, 250, 251, 252, 253, 254, 254, 254, 254, 254, 254, 253, 252, 251, 250, 248, 247, 245, 242, 240, 238, 235, 232, 229, 225, 222, 218, 215, 211, 206, 202, 198, 193, 189, 184, 179, 174, 169, 164, 159, 154, 149, 143, 138, 133, 127, 122, 117, 111, 106, 101, 96, 91, 86, 81, 76, 71, 66, 61, 57, 53, 48, 44, 40, 36, 33, 29, 26, 23, 20, 17, 14, 12, 10, 8, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 9, 11, 14, 16, 19, 22, 25, 28, 32, 35, 39, 43, 47, 51, 56, 60, 65, 70, 74, 79, 84, 89, 94, 100, 105, 110, 115, 121 } };
Note D5 = { 75, { 127, 138, 148, 159, 169, 179, 188, 197, 206, 214, 222, 228, 235, 240, 244, 248, 251, 253, 254, 254, 254, 252, 250, 247, 242, 238, 232, 225, 218, 211, 202, 193, 184, 174, 164, 154, 143, 133, 122, 111, 101, 91, 81, 71, 61, 53, 44, 36, 29, 23, 17, 12, 8, 4, 2, 0, 0, 0, 1, 3, 6, 9, 14, 19, 25, 32, 39, 47, 56, 65, 74, 84, 94, 105, 115 } };
Note D3 = { 300, { 127, 130, 132, 135, 138, 140, 143, 146, 148, 151, 153, 156, 159, 161, 164, 166, 169, 171, 174, 176, 179, 181, 184, 186, 188, 191, 193, 195, 197, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 223, 225, 227, 228, 230, 232, 233, 235, 236, 237, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 252, 252, 251, 251, 250, 249, 248, 248, 247, 246, 245, 244, 242, 241, 240, 239, 238, 236, 235, 233, 232, 230, 229, 227, 225, 224, 222, 220, 218, 216, 215, 213, 211, 209, 206, 204, 202, 200, 198, 196, 193, 191, 189, 186, 184, 182, 179, 177, 174, 172, 169, 167, 164, 162, 159, 157, 154, 151, 149, 146, 143, 141, 138, 135, 133, 130, 127, 125, 122, 119, 117, 114, 111, 109, 106, 104, 101, 98, 96, 93, 91, 88, 86, 83, 81, 78, 76, 73, 71, 68, 66, 64, 61, 59, 57, 55, 53, 50, 48, 46, 44, 42, 40, 38, 36, 34, 33, 31, 29, 27, 26, 24, 23, 21, 20, 18, 17, 16, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 18, 19, 20, 22, 23, 25, 27, 28, 30, 32, 34, 35, 37, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 63, 65, 67, 70, 72, 74, 77, 79, 82, 84, 87, 89, 92, 94, 97, 100, 102, 105, 107, 110, 113, 115, 118, 121, 123 } };

Song THATSNOMOON = { 37, {&D4, &D4, &D4, &G4, &G4, &G4, &G4, &A4, &A4, &A4, &AS4, &C5, &AS4, &AS4, &AS4, &AS4, &D4, &D4, &D4, &D4, &D4, &D4, &G4, &G4, &G4, &G4, &A4, &A4, &AS4, &D4, &AS4, &G4, &D5, &C5, &C5, &C5, &C5} };
Song PEWPEW = { 13, {&D5, &C5, &B4, &A4, &G4, &F4, &E4, &D4, &C4, &B3, &A3, &G3, &F3} };
Song ONEUP = { 18, {&C4, &E4, &G4, &C4, &E4, &G4, &C5, &E5, &G5, &C5, &E5, &G5, &C6, &E6, &G6, &C7, &E7, &G7} };
Song SCOM = { 65, {&G4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &G4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &A4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &A4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &C5, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &C5, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &A5, &D5, &G5, &D5, &A5, &D5, &B5, &D5, &C6, &D5, &B5, &D5, &A5, &D5, &G5, &D5, &G5} };
Song CANON = { 52, {&A5, &FS5, &D5, &A4, &FS4, &D4, &A3, &CS4, &E4, &A4, &CS5, &E5, &FS5, &D5, &B4, &FS4, &D4, &B3, &FS3, &A3, &CS4, &FS4, &A4, &CS5, &D5, &B4, &G4, &D4, &B3, &G3, &D3, &FS3, &A3, &D4, &FS4, &A4, &B4, &G4, &D4, &B3, &G3, &D3, &A3, &CS4, &E4, &A4, &CS5, &E5, &A5, &A5, &A5, &A5} };
Song JUMP = { 8, {&C5, &D5, &E5, &F5, &G5, &A5, &B5, &C6} };
