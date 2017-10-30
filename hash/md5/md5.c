#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* References */
//https://en.wikipedia.org/wiki/MD5
//https://gist.github.com/creationix/4710780
//Compile: gcc md5.c  -lm -o md5.o
//Run: ./md5.o <string>
//leftrotate function definition
#define LEFT_ROTATE(x,c) ( (x << c) | (x) >> (32-c) )
#define ONE_BYTE 1

//global var to store the final hash
uint32_t h0, h1, h2, h3;

void md5(uint8_t *initial_message, size_t initial_len);

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Please provide a string to compute md5. \n");
		return -1;
	}

	//store the string
	char *message = argv[1];
	size_t message_length = strlen(message);

	//compute md5
	md5(message, message_length);

	//display md5
	uint8_t *p;

	// display result
	//MD5:= h0 append h1 append h2 append h3 ,(Output is in little-endian)
	//Little-endian is an order in which least significant value in the sequence is stored first.

	printf("h0: %x\n",h0);
	printf("h1: %x\n",h1);
	printf("h2: %x\n",h2);
	printf("h3: %x\n",h3);

	printf("MD5 of \"%s\" : \n",message);
	p = (uint8_t *) &h0;
	printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);

	p = (uint8_t *) &h1;
	printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);

	p = (uint8_t *) &h2;
	printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);

	p = (uint8_t *) &h3;
	printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);
	puts("");

	return 0;

}

void md5(uint8_t *initial_message, size_t initial_len) {
	//message to prepare which will include padding
	uint8_t *message = NULL;

	//Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
	//shift_table specifies the per-round shift amounts
	uint32_t shift_table[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
			12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
			15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

	//Use binary integer part of the sines of integers (Radians) as constants (pre computed table)
	/* It is computed as */
	//	for i from 0 to 63
	//	    K[i] := floor(232 × abs(sin(i + 1)))
	//	end for
	uint32_t sin_table[] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
			0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
			0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51,
			0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905,
			0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
			0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
			0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
			0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
			0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314,
			0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

	//Initialize variables
	h0 = 0x67452301;
	h1 = 0xefcdab89;
	h2 = 0x98badcfe;
	h3 = 0x10325476;

	// Pre-processing: adding a single 1 bit
	//append "1" bit to message
	//append "0" bit until message length in bit ≡ 448 (mod 512)

	int new_length = initial_len * 8 + 1;
	/* Length of the message(in BITS) should be such that (msg_length)%512 equals 448 */
	while (new_length % 512 != 448) {
		new_length++;
	}
	/* Get new length in BYTES */
	new_length = new_length / 8;

	/* Allocate memory for the new message */
	message = calloc(new_length + 64, ONE_BYTE); // Since we used calloc, message will initialzed to all 0s (not append required)

	/* Copy the initial message */
	memcpy(message, initial_message, initial_len);

	/* Write the "1" bit */
	message[initial_len] = 128;

	uint32_t bits_len = 8 * initial_len; 		// note, we append the length
	memcpy(message + new_length, &bits_len, 4); // in bits at the end of the buffer

	//Process the message in successive 512-bit (64 bytes)chunks:
	for (int offset = 0; offset < new_length; offset = offset + (512 / 8)) {

		/* Break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15 */
		uint32_t *M = (uint32_t *) (message + offset); //pointer to block of 512 bit chunk

		/* Initialize hash value for the chunk */
		uint32_t A = h0;
		uint32_t B = h1;
		uint32_t C = h2;
		uint32_t D = h3;

		/* Main loop to process 512 bit (64 byte) chunk*/
		for (int i = 0; i < 64; i++) {
			uint32_t F, g;
			if (i < 16) {
				/* F := (B and C) or ((not B) and D)*/
				/* g := i*/
				F = (B & C) | ((~B) & D);
				g = i;
			} else if (i < 32) {
				/*  F := (D and B) or ((not D) and C)
				 g := (5×i + 1) mod 16*/
				F = (D & B) | ((~D) & C);
				g = (5 * i + 1) % 16;
			} else if (i < 48) {
				F = B ^ C ^ D;
				g = (3 * i + 5) % 16;
			} else {
				F = C ^ (B | (~D));
				g = (7 * i) % 16;
			}

			//Be wary of the below definitions of a,b,c,d
			F = F + A + sin_table[i] + M[g];
			A = D;
			D = C;
			C = B;
			B = B + LEFT_ROTATE(F, shift_table[i]);
		}
		/* End main loop */

		//Add this 512 bit chunk's hash to result so far
		h0 = h0 + A;
		h1 = h1 + B;
		h2 = h2 + C;
		h3 = h3 + D;
	}
	/* End for loop for 512 bit chunk */

	//clean memory
	free(message);
}

