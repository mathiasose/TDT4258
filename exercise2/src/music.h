typedef struct Note {
	uint8_t num;
	uint8_t samples[];
} Note;

Note G5 = { 56, { 127, 141, 155, 169, 182, 195, 206, 217, 226, 235, 242, 247, 251, 254, 254, 254, 252, 248, 242, 236, 227, 218, 208, 196, 184, 171, 157, 143, 129, 115, 100, 87, 74, 61, 49, 38, 29, 20, 13, 7, 3, 1, 0, 0, 2, 6, 11, 17, 25, 35, 45, 56, 69, 82, 95, 109 } };
Note G4 = { 112, { 127, 134, 141, 148, 155, 162, 169, 176, 182, 188, 195, 200, 206, 212, 217, 222, 226, 231, 235, 238, 242, 245, 247, 249, 251, 253, 254, 254, 254, 254, 254, 253, 252, 250, 248, 245, 242, 239, 236, 232, 227, 223, 218, 213, 208, 202, 196, 190, 184, 177, 171, 164, 157, 150, 143, 136, 129, 122, 115, 107, 100, 94, 87, 80, 74, 67, 61, 55, 49, 44, 38, 33, 29, 24, 20, 17, 13, 10, 7, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 4, 6, 8, 11, 14, 17, 21, 25, 30, 35, 40, 45, 51, 56, 62, 69, 75, 82, 88, 95, 102, 109, 116 } };
Note B5 = { 44, { 127, 145, 162, 179, 195, 209, 222, 233, 242, 249, 253, 254, 254, 250, 244, 236, 226, 214, 200, 184, 168, 151, 133, 115, 97, 80, 64, 49, 36, 24, 15, 7, 2, 0, 0, 2, 7, 15, 24, 36, 49, 64, 81, 98 } };
Note A5 = { 50, { 127, 143, 159, 174, 188, 202, 214, 225, 234, 242, 248, 252, 254, 254, 252, 248, 243, 235, 226, 215, 203, 189, 175, 160, 144, 128, 112, 96, 81, 67, 53, 41, 30, 20, 12, 6, 2, 0, 0, 2, 5, 11, 19, 28, 39, 51, 64, 78, 94, 109 } };
Note A4 = { 100, { 127, 135, 143, 151, 159, 166, 174, 181, 188, 195, 202, 208, 214, 220, 225, 230, 234, 239, 242, 245, 248, 250, 252, 253, 254, 254, 254, 254, 252, 251, 248, 246, 243, 239, 235, 231, 226, 220, 215, 209, 203, 196, 189, 182, 175, 167, 160, 152, 144, 136, 128, 120, 112, 104, 96, 89, 81, 74, 67, 60, 53, 47, 41, 35, 30, 25, 20, 16, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 2, 3, 5, 8, 11, 15, 19, 23, 28, 33, 39, 44, 51, 57, 64, 71, 78, 86, 94, 101, 109, 117 } };
Note D5 = { 75, { 127, 138, 148, 159, 169, 179, 188, 197, 206, 214, 222, 228, 235, 240, 244, 248, 251, 253, 254, 254, 254, 252, 250, 247, 242, 238, 232, 225, 218, 211, 202, 193, 184, 174, 164, 154, 143, 133, 122, 111, 101, 91, 81, 71, 61, 53, 44, 36, 29, 23, 17, 12, 8, 4, 2, 0, 0, 0, 1, 3, 6, 9, 14, 19, 25, 32, 39, 47, 56, 65, 74, 84, 94, 105, 115 } };
Note C6 = { 42, { 127, 146, 164, 182, 199, 213, 226, 237, 245, 251, 254, 254, 251, 246, 238, 227, 214, 200, 183, 166, 147, 128, 109, 91, 73, 56, 41, 28, 17, 9, 3, 0, 0, 2, 8, 15, 26, 39, 53, 69, 87, 105 } };
Note C5 = { 84, { 127, 136, 146, 155, 164, 173, 182, 191, 199, 206, 213, 220, 226, 232, 237, 242, 245, 249, 251, 253, 254, 254, 254, 253, 251, 249, 246, 242, 238, 233, 227, 221, 214, 207, 200, 192, 183, 175, 166, 157, 147, 138, 128, 119, 109, 100, 91, 82, 73, 65, 56, 49, 41, 35, 28, 23, 17, 13, 9, 6, 3, 1, 0, 0, 0, 1, 2, 5, 8, 11, 15, 20, 26, 32, 39, 46, 53, 61, 69, 78, 87, 96, 105, 115 } };

static Note *SCOM[] = { &G4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &G4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &A4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &A4, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &C5, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &C5, &G5, &D5, &C5, &C6, &D5, &B5, &D5, &A5, &D5, &G5, &D5, &A5, &D5, &B5, &D5, &C6, &D5, &B5, &D5, &A5, &D5, &G5, &D5, &G5 };
static uint8_t SCOM_LEN = 65;