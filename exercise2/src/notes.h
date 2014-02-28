typedef struct Note{
	uint8_t num;
	uint8_t samples[];
} Note;

Note A =  { 100, { 127, 135, 143, 151, 159, 166, 174, 181, 188, 195, 202, 208, 214, 220, 225, 230, 234, 239, 242, 245, 248, 250, 252, 253, 254, 254, 254, 254, 252, 251, 248, 246, 243, 239, 235, 231, 226, 220, 215, 209, 203, 196, 189, 182, 175, 167, 160, 152, 144, 136, 128, 120, 112, 104, 96, 89, 81, 74, 67, 60, 53, 47, 41, 35, 30, 25, 20, 16, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 2, 3, 5, 8, 11, 15, 19, 23, 28, 33, 39, 44, 51, 57, 64, 71, 78, 86, 94, 101, 109, 117 } };

Note C =  { 100, { 127, 135, 143, 151, 159, 166, 174, 181, 188, 195, 202, 208, 214, 220, 225, 230, 234, 239, 242, 245, 248, 250, 252, 253, 254, 254, 254, 254, 252, 251, 248, 246, 243, 239, 235, 231, 226, 220, 215, 209, 203, 196, 189, 182, 175, 167, 160, 152, 144, 136, 128, 120, 112, 104, 96, 89, 81, 74, 67, 60, 53, 47, 41, 35, 30, 25, 20, 16, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 2, 3, 5, 8, 11, 15, 19, 23, 28, 33, 39, 44, 51, 57, 64, 71, 78, 86, 94, 101, 109, 117 } };

Note E =  { 133, { 127, 133, 139, 145, 151, 157, 162, 168, 174, 179, 185, 190, 195, 200, 205, 210, 214, 218, 222, 226, 230, 233, 237, 239, 242, 245, 247, 249, 250, 252, 253, 254, 254, 254, 254, 254, 254, 253, 252, 250, 249, 247, 244, 242, 239, 236, 233, 230, 226, 222, 218, 214, 209, 204, 200, 195, 189, 184, 179, 173, 168, 162, 156, 150, 144, 138, 132, 126, 120, 114, 108, 103, 97, 91, 85, 80, 74, 69, 63, 58, 53, 49, 44, 39, 35, 31, 27, 24, 20, 17, 14, 12, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 3, 4, 6, 8, 10, 12, 15, 18, 21, 25, 29, 32, 37, 41, 45, 50, 55, 60, 65, 70, 76, 81, 87, 93, 99, 104, 110, 116 } };

Note D =  { 150, { 127, 132, 138, 143, 148, 153, 159, 164, 169, 174, 179, 184, 188, 193, 197, 202, 206, 210, 214, 218, 222, 225, 228, 232, 235, 237, 240, 242, 244, 246, 248, 250, 251, 252, 253, 254, 254, 254, 254, 254, 254, 253, 252, 251, 250, 248, 247, 245, 242, 240, 238, 235, 232, 229, 225, 222, 218, 215, 211, 206, 202, 198, 193, 189, 184, 179, 174, 169, 164, 159, 154, 149, 143, 138, 133, 127, 122, 117, 111, 106, 101, 96, 91, 86, 81, 76, 71, 66, 61, 57, 53, 48, 44, 40, 36, 33, 29, 26, 23, 20, 17, 14, 12, 10, 8, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 9, 11, 14, 16, 19, 22, 25, 28, 32, 35, 39, 43, 47, 51, 56, 60, 65, 70, 74, 79, 84, 89, 94, 100, 105, 110, 115, 121 } };

Note G =  { 112, { 127, 134, 141, 148, 155, 162, 169, 176, 182, 188, 195, 200, 206, 212, 217, 222, 226, 231, 235, 238, 242, 245, 247, 249, 251, 253, 254, 254, 254, 254, 254, 253, 252, 250, 248, 245, 242, 239, 236, 232, 227, 223, 218, 213, 208, 202, 196, 190, 184, 177, 171, 164, 157, 150, 143, 136, 129, 122, 115, 107, 100, 94, 87, 80, 74, 67, 61, 55, 49, 44, 38, 33, 29, 24, 20, 17, 13, 10, 7, 5, 3, 2, 1, 0, 0, 0, 0, 1, 2, 4, 6, 8, 11, 14, 17, 21, 25, 30, 35, 40, 45, 51, 56, 62, 69, 75, 82, 88, 95, 102, 109, 116 } };

Note F =  { 126, { 127, 133, 140, 146, 152, 158, 165, 171, 176, 182, 188, 193, 199, 204, 209, 214, 218, 222, 227, 230, 234, 237, 240, 243, 246, 248, 250, 251, 252, 253, 254, 254, 254, 254, 254, 253, 251, 250, 248, 246, 243, 241, 238, 234, 231, 227, 223, 219, 214, 209, 205, 199, 194, 189, 183, 177, 171, 165, 159, 153, 147, 141, 134, 128, 122, 115, 109, 103, 96, 90, 84, 78, 73, 67, 61, 56, 51, 46, 41, 37, 32, 28, 24, 21, 17, 14, 11, 9, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 4, 6, 8, 10, 13, 16, 19, 23, 26, 30, 35, 39, 44, 49, 54, 59, 65, 70, 76, 82, 88, 94, 100, 106, 113, 119 } };

Note C1 =  { 84, { 127, 136, 146, 155, 164, 173, 182, 191, 199, 206, 213, 220, 226, 232, 237, 242, 245, 249, 251, 253, 254, 254, 254, 253, 251, 249, 246, 242, 238, 233, 227, 221, 214, 207, 200, 192, 183, 175, 166, 157, 147, 138, 128, 119, 109, 100, 91, 82, 73, 65, 56, 49, 41, 35, 28, 23, 17, 13, 9, 6, 3, 1, 0, 0, 0, 1, 2, 5, 8, 11, 15, 20, 26, 32, 39, 46, 53, 61, 69, 78, 87, 96, 105, 115 } };

Note B1 =  { 89, { 127, 136, 145, 154, 162, 171, 179, 187, 195, 202, 209, 216, 222, 228, 233, 238, 242, 246, 249, 251, 253, 254, 254, 254, 254, 252, 250, 248, 244, 241, 236, 231, 226, 220, 214, 207, 200, 192, 184, 176, 168, 159, 151, 142, 133, 124, 115, 106, 97, 89, 80, 72, 64, 56, 49, 42, 36, 30, 24, 19, 15, 11, 7, 4, 2, 1, 0, 0, 0, 1, 2, 5, 7, 11, 15, 19, 24, 30, 36, 43, 49, 57, 64, 72, 81, 89, 98, 107, 115 } };

