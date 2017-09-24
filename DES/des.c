#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

#define DATA_BLOCK_LENGTH 64
#define SUB_DATA_BLOCK_LENGTH 32
#define INITIAL_KEY_LENGTH 64
#define PERMUTED_KEY_LENGTH 56
#define SUB_KEY_PERMUTED_LENGTH 28
#define NO_OF_SUB_KEYS 16
#define SUB_KEY_LENGTH 48
#define SBOX_INPUT 6
#define SBOX_OUTPUT 6
#define SBOX_ROW_LENGTH 2
#define SBOX_COLUMN_LENGTH 4
#define NO_OF_SBOX_OPERATIONS 16

void DES(int *data,int *key,int cipher[]);
void initial_permutation_key(int key[]);

void displayIntArray(int *array, int size);
void rotate_array(int arr[],int n,int d);
void apply_initial_message_permutation(int data[]);
void apply_final_message_permutation(int data[]);
void encypt_data_with_subkeys(int data[],int cipher[]);
void func(int arr_no,int righ[][SUB_DATA_BLOCK_LENGTH],int sub_key[][SUB_KEY_LENGTH],int result[]);
void XOR(int arr1[], int arr2[][SUB_KEY_LENGTH],int index, int result[]);
void compute_SBOX(int round,int xor_result[],int SBOX_output[], int *SBOX_index,int *SBOX_index2);
void getRow(int data[],int *row);
void getColumn(int data[],int *column);
void getSBOX_value(int round,int row,int column,int *SBOX_value);
void int_to_bin_digit(unsigned int in, int count, int* out,int *index);
void XOR_function(int arr1[], int arr2[][SUB_DATA_BLOCK_LENGTH], int index, int result[][SUB_DATA_BLOCK_LENGTH],int index2);

void DES_decrypt(int *cipher,int *key,int *data);
void initial_permutation_key2(int key[]);

//PC1
int initial_key_permutaion[] = {57, 49,  41, 33,  25,  17,  9,
							 1, 58,  50, 42,  34,  26, 18,
							10,  2,  59, 51,  43,  35, 27,
							19, 11,   3, 60,  52,  44, 36,
							63, 55,  47, 39,  31,  23, 15,
							 7, 62,  54, 46,  38,  30, 22,
							14,  6,  61, 53,  45,  37, 29,
							21, 13,   5, 28,  20,  12,  4};

//PC2
int initial_key_permutaion2[] = {14, 17, 11, 24,   1,   5,
								 3, 28, 15,  6,  21,  10,
								 23,19, 12,  4,  26,   8,
								 16, 7, 27, 20,  13,   2,
								 41,52, 31, 37,  47,  55,
								 30,40, 51, 45,  33,  48,
								 44,49, 39, 56,  34,  53,
								 46,42, 50, 36,  29,  32,
								};


int initial_message_permutation[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
										60, 52, 44, 36, 28, 20, 12, 4,
										62, 54, 46, 38, 30, 22, 14, 6,
										64, 56, 48, 40, 32, 24, 16, 8,
										57, 49, 41, 33, 25, 17,  9, 1,
										59, 51, 43, 35, 27, 19, 11, 3,
										61, 53, 45, 37, 29, 21, 13, 5,
										63, 55, 47, 39, 31, 23, 15, 7};

/* key shift table */
int left_shift_table[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

/* Sub keys */
int sub_key[NO_OF_SUB_KEYS][SUB_KEY_LENGTH]={0};

/* Message expansion table (E BIT-SELECTION TABLE) */
int message_expansion[] =  {32,  1,  2,  3,  4,  5,
							 4,  5,  6,  7,  8,  9,
							 8,  9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32,  1};

/* S boxes */
int S1[][NO_OF_SUB_KEYS]= {{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
			 {0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
			 {4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
			{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}};

int S2[][NO_OF_SUB_KEYS] = {{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
			 {3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
			 {0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
			{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}};

int S3[][NO_OF_SUB_KEYS] = {{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
			{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
			{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
			 {1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}};

int S4[][NO_OF_SUB_KEYS] = { {7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
			{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
			{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
			 {3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}};

int S5[][NO_OF_SUB_KEYS] = { {2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
			{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
			 {4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
			{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}};

int S6[][NO_OF_SUB_KEYS] = {{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
			{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
			 {9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
			 {4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}};

int S7[][NO_OF_SUB_KEYS] = {{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
			{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
			 {1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
			 {6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}};

int S8[][NO_OF_SUB_KEYS] = {{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
			 {1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
			 {7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
			 {2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}};

int right_sub_message_permutation[] =    {16,  7, 20, 21,
									29, 12, 28, 17,
									 1, 15, 23, 26,
									 5, 18, 31, 10,
									 2,  8, 24, 14,
									32, 27,  3,  9,
									19, 13, 30,  6,
									22, 11,  4, 25};

//IP inverse
int final_message_permutation[] =  {40,  8, 48, 16, 56, 24, 64, 32,
									39,  7, 47, 15, 55, 23, 63, 31,
									38,  6, 46, 14, 54, 22, 62, 30,
									37,  5, 45, 13, 53, 21, 61, 29,
									36,  4, 44, 12, 52, 20, 60, 28,
									35,  3, 43, 11, 51, 19, 59, 27,
									34,  2, 42, 10, 50, 18, 58, 26,
									33,  1, 41,  9, 49, 17, 57, 25};


int main(int argc, char **argv) {
	int message[64]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};
	int key[64]={0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1};
	int cipher[64];
	printf("Original message: \n");
	displayIntArray(message,DATA_BLOCK_LENGTH);
	DES(message,key,cipher);
	printf("DES encrypted message: \n");
	displayIntArray(cipher,DATA_BLOCK_LENGTH);

	DES_decrypt(cipher,key,message);
	printf("DES decrypted message: \n");
	displayIntArray(message,DATA_BLOCK_LENGTH);
	return 0;
}

void DES(int *data,int *key,int *cipher)
{
	/*Step 1: Create 16 subkeys, each of which is 48-bits long.*/
	initial_permutation_key(key);

	/*Step 2: Encode each 64-bit block of data.*/
	printf("Initial data block:\n");
	displayIntArray(data,DATA_BLOCK_LENGTH);
	apply_initial_message_permutation(data);
	printf("After applying 1st message permutation on data block:\n");
	displayIntArray(data,DATA_BLOCK_LENGTH);

	/*Step 3:Encrypt the permuted data block in 16 iteration with 16 subkeys*/
	encypt_data_with_subkeys(data,cipher);

	/* Step 4: Apply a final permutation IP inverse */
	apply_final_message_permutation(cipher);

}

void DES_decrypt(int *cipher,int *key,int *data)
{
	/*Step 0: Create 16 subkeys, each of which is 48-bits long.*/
	initial_permutation_key2(key);


	/* Step 1: Apply a final permutation IP inverse */
	apply_initial_message_permutation(cipher);

	/*Step 2:Encrypt the permuted data block in 16 iteration with 16 subkeys*/
	encypt_data_with_subkeys(cipher,data);

	apply_final_message_permutation(data);

}


void displayIntArray(int *array, int size)
{
	for (int i = 0; i < size; i++) {
		if(i%8==0)
			printf(" ");
		printf("%d",array[i]);
	}
	printf("\n");
}

void initial_permutation_key(int key[]){
	int temp_key[INITIAL_KEY_LENGTH];
	int C0[SUB_KEY_PERMUTED_LENGTH]={0};
	int D0[SUB_KEY_PERMUTED_LENGTH]={0};

	int C1[SUB_KEY_PERMUTED_LENGTH]={0};
	int D1[SUB_KEY_PERMUTED_LENGTH]={0};

	int C2[SUB_KEY_PERMUTED_LENGTH]={0};
	int D2[SUB_KEY_PERMUTED_LENGTH]={0};

	int C3[SUB_KEY_PERMUTED_LENGTH]={0};
	int D3[SUB_KEY_PERMUTED_LENGTH]={0};

	int C4[SUB_KEY_PERMUTED_LENGTH]={0};
	int D4[SUB_KEY_PERMUTED_LENGTH]={0};

	int C5[SUB_KEY_PERMUTED_LENGTH]={0};
	int D5[SUB_KEY_PERMUTED_LENGTH]={0};

	int C6[SUB_KEY_PERMUTED_LENGTH]={0};
	int D6[SUB_KEY_PERMUTED_LENGTH]={0};

	int C7[SUB_KEY_PERMUTED_LENGTH]={0};
	int D7[SUB_KEY_PERMUTED_LENGTH]={0};

	int C8[SUB_KEY_PERMUTED_LENGTH]={0};
	int D8[SUB_KEY_PERMUTED_LENGTH]={0};

	int C9[SUB_KEY_PERMUTED_LENGTH]={0};
	int D9[SUB_KEY_PERMUTED_LENGTH]={0};

	int C10[SUB_KEY_PERMUTED_LENGTH]={0};
	int D10[SUB_KEY_PERMUTED_LENGTH]={0};

	int C11[SUB_KEY_PERMUTED_LENGTH]={0};
	int D11[SUB_KEY_PERMUTED_LENGTH]={0};

	int C12[SUB_KEY_PERMUTED_LENGTH]={0};
	int D12[SUB_KEY_PERMUTED_LENGTH]={0};

	int C13[SUB_KEY_PERMUTED_LENGTH]={0};
	int D13[SUB_KEY_PERMUTED_LENGTH]={0};

	int C14[SUB_KEY_PERMUTED_LENGTH]={0};
	int D14[SUB_KEY_PERMUTED_LENGTH]={0};

	int C15[SUB_KEY_PERMUTED_LENGTH]={0};
	int D15[SUB_KEY_PERMUTED_LENGTH]={0};

	int C16[SUB_KEY_PERMUTED_LENGTH]={0};
	int D16[SUB_KEY_PERMUTED_LENGTH]={0};

	memcpy(temp_key,key,sizeof(int)*INITIAL_KEY_LENGTH);
	printf("Original 64 bit key: \n");
	displayIntArray(temp_key,INITIAL_KEY_LENGTH);

	/* Apply the key permutation to create 56 bit key */
	for(int i=0;i<PERMUTED_KEY_LENGTH;i++){
		key[i]=temp_key[initial_key_permutaion[i]-1];
	}

	printf("Permuted Key: \n");
	displayIntArray(key,PERMUTED_KEY_LENGTH);

	/* Get Left and right part of permuted key*/
	memcpy(C0,key,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D0,key+SUB_KEY_PERMUTED_LENGTH,SUB_KEY_PERMUTED_LENGTH*sizeof(int));

	printf("C0: \n");
	displayIntArray(C0,SUB_KEY_PERMUTED_LENGTH);
	printf("D0: \n");
	displayIntArray(D0,SUB_KEY_PERMUTED_LENGTH);

	/* Create 16 sub keys by left shifting prev subkey according to left_shift_table */
	memcpy(C1,C0,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D1,D0,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C1,SUB_KEY_PERMUTED_LENGTH,left_shift_table[0]);
	rotate_array(D1,SUB_KEY_PERMUTED_LENGTH,left_shift_table[0]);

	memcpy(C2,C1,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D2,D1,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C2,SUB_KEY_PERMUTED_LENGTH,left_shift_table[1]);
	rotate_array(D2,SUB_KEY_PERMUTED_LENGTH,left_shift_table[1]);

	memcpy(C3,C2,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D3,D2,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C3,SUB_KEY_PERMUTED_LENGTH,left_shift_table[2]);
	rotate_array(D3,SUB_KEY_PERMUTED_LENGTH,left_shift_table[2]);

	memcpy(C4,C3,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D4,D3,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C4,SUB_KEY_PERMUTED_LENGTH,left_shift_table[3]);
	rotate_array(D4,SUB_KEY_PERMUTED_LENGTH,left_shift_table[3]);

	memcpy(C5,C4,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D5,D4,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C5,SUB_KEY_PERMUTED_LENGTH,left_shift_table[4]);
	rotate_array(D5,SUB_KEY_PERMUTED_LENGTH,left_shift_table[4]);

	memcpy(C6,C5,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D6,D5,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C6,SUB_KEY_PERMUTED_LENGTH,left_shift_table[5]);
	rotate_array(D6,SUB_KEY_PERMUTED_LENGTH,left_shift_table[5]);

	memcpy(C7,C6,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D7,D6,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C7,SUB_KEY_PERMUTED_LENGTH,left_shift_table[6]);
	rotate_array(D7,SUB_KEY_PERMUTED_LENGTH,left_shift_table[6]);

	memcpy(C8,C7,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D8,D7,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C8,SUB_KEY_PERMUTED_LENGTH,left_shift_table[7]);
	rotate_array(D8,SUB_KEY_PERMUTED_LENGTH,left_shift_table[7]);

	memcpy(C9,C8,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D9,D8,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C9,SUB_KEY_PERMUTED_LENGTH,left_shift_table[8]);
	rotate_array(D9,SUB_KEY_PERMUTED_LENGTH,left_shift_table[8]);

	memcpy(C10,C9,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D10,D9,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C10,SUB_KEY_PERMUTED_LENGTH,left_shift_table[9]);
	rotate_array(D10,SUB_KEY_PERMUTED_LENGTH,left_shift_table[9]);

	memcpy(C11,C10,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D11,D10,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C11,SUB_KEY_PERMUTED_LENGTH,left_shift_table[10]);
	rotate_array(D11,SUB_KEY_PERMUTED_LENGTH,left_shift_table[10]);

	memcpy(C12,C11,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D12,D11,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C12,SUB_KEY_PERMUTED_LENGTH,left_shift_table[11]);
	rotate_array(D12,SUB_KEY_PERMUTED_LENGTH,left_shift_table[11]);

	memcpy(C13,C12,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D13,D12,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C13,SUB_KEY_PERMUTED_LENGTH,left_shift_table[12]);
	rotate_array(D13,SUB_KEY_PERMUTED_LENGTH,left_shift_table[12]);

	memcpy(C14,C13,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D14,D13,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C14,SUB_KEY_PERMUTED_LENGTH,left_shift_table[13]);
	rotate_array(D14,SUB_KEY_PERMUTED_LENGTH,left_shift_table[13]);

	memcpy(C15,C14,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D15,D14,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C15,SUB_KEY_PERMUTED_LENGTH,left_shift_table[14]);
	rotate_array(D15,SUB_KEY_PERMUTED_LENGTH,left_shift_table[14]);

	memcpy(C16,C15,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(D16,D15,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	rotate_array(C16,SUB_KEY_PERMUTED_LENGTH,left_shift_table[15]);
	rotate_array(D16,SUB_KEY_PERMUTED_LENGTH,left_shift_table[15]);

	printf("C16: \n");
	displayIntArray(C16,SUB_KEY_PERMUTED_LENGTH);
	printf("D16: \n");
	displayIntArray(D16,SUB_KEY_PERMUTED_LENGTH);

	/* Apply permutation table 2 on each of the CnDn pair of keys to create final 16 subkeys*/
	//create temp array by concatinating Cn and Dn
	int temp_subkey[SUB_KEY_LENGTH]={0};

	/* Apply PC-2 in C1,D1 to generate 48 bit subkey1 */
	memcpy(temp_subkey,C1,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D1,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
		sub_key[0][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C2,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D2,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[1][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 3 */
	memcpy(temp_subkey,C3,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D3,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[2][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 4 */
	memcpy(temp_subkey,C4,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D4,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[3][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 5 */
	memcpy(temp_subkey,C5,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D5,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[4][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 6 */
	memcpy(temp_subkey,C6,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D6,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[5][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 7 */
	memcpy(temp_subkey,C7,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D7,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[6][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 8 */
	memcpy(temp_subkey,C8,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D8,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[7][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C9,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D9,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[8][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 10 */
	memcpy(temp_subkey,C10,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D10,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[9][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 11 */
	memcpy(temp_subkey,C11,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D11,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[10][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 12 */
	memcpy(temp_subkey,C12,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D12,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[11][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 13 */
	memcpy(temp_subkey,C13,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D13,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[12][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C14,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D14,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[13][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 15 */
	memcpy(temp_subkey,C15,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D15,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[14][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C16,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D16,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key[15][i]=temp_subkey[initial_key_permutaion2[i]-1];
	}

	printf("Final 16 Subkeys: \n");
	displayIntArray(sub_key[0],SUB_KEY_LENGTH);
	displayIntArray(sub_key[1],SUB_KEY_LENGTH);
	displayIntArray(sub_key[2],SUB_KEY_LENGTH);
	displayIntArray(sub_key[3],SUB_KEY_LENGTH);
	displayIntArray(sub_key[4],SUB_KEY_LENGTH);
	displayIntArray(sub_key[5],SUB_KEY_LENGTH);
	displayIntArray(sub_key[6],SUB_KEY_LENGTH);
	displayIntArray(sub_key[7],SUB_KEY_LENGTH);
	displayIntArray(sub_key[8],SUB_KEY_LENGTH);
	displayIntArray(sub_key[9],SUB_KEY_LENGTH);
	displayIntArray(sub_key[10],SUB_KEY_LENGTH);
	displayIntArray(sub_key[11],SUB_KEY_LENGTH);
	displayIntArray(sub_key[12],SUB_KEY_LENGTH);
	displayIntArray(sub_key[13],SUB_KEY_LENGTH);
	displayIntArray(sub_key[14],SUB_KEY_LENGTH);
	displayIntArray(sub_key[15],SUB_KEY_LENGTH);


}

void initial_permutation_key2(int key[]){
	int temp_key[48]={0};
	int start=0;
	int end=15;
	while(end >= start ){
		memcpy(temp_key,sub_key[start],SUB_KEY_LENGTH*sizeof(int));
		memcpy(sub_key[start],sub_key[end],SUB_KEY_LENGTH*sizeof(int));
		memcpy(sub_key[end],temp_key,SUB_KEY_LENGTH*sizeof(int));
		start++;
		end--;
	}

	printf("Final 16 Subkeys For Decryption: \n");
		displayIntArray(sub_key[0],SUB_KEY_LENGTH);
		displayIntArray(sub_key[1],SUB_KEY_LENGTH);
		displayIntArray(sub_key[2],SUB_KEY_LENGTH);
		displayIntArray(sub_key[3],SUB_KEY_LENGTH);
		displayIntArray(sub_key[4],SUB_KEY_LENGTH);
		displayIntArray(sub_key[5],SUB_KEY_LENGTH);
		displayIntArray(sub_key[6],SUB_KEY_LENGTH);
		displayIntArray(sub_key[7],SUB_KEY_LENGTH);
		displayIntArray(sub_key[8],SUB_KEY_LENGTH);
		displayIntArray(sub_key[9],SUB_KEY_LENGTH);
		displayIntArray(sub_key[10],SUB_KEY_LENGTH);
		displayIntArray(sub_key[11],SUB_KEY_LENGTH);
		displayIntArray(sub_key[12],SUB_KEY_LENGTH);
		displayIntArray(sub_key[13],SUB_KEY_LENGTH);
		displayIntArray(sub_key[14],SUB_KEY_LENGTH);
		displayIntArray(sub_key[15],SUB_KEY_LENGTH);
}

void rotate_array(int arr[],int n,int d){
	while(d-- > 0){
		int temp=arr[0];
		for(int i=0;i<n-1;i++){
			arr[i]=arr[i+1];
		}
		arr[n-1]=temp;
	}
}

void apply_initial_message_permutation(int data[])
{
	int temp_data[DATA_BLOCK_LENGTH]={0};
	memcpy(temp_data,data,DATA_BLOCK_LENGTH*sizeof(int));
	for(int i=0;i<DATA_BLOCK_LENGTH;i++){
		data[i]=temp_data[initial_message_permutation[i]-1];
	}
}

void apply_final_message_permutation(int data[])
{
	int temp_data[DATA_BLOCK_LENGTH]={0};
	memcpy(temp_data,data,DATA_BLOCK_LENGTH*sizeof(int));
	for(int i=0;i<DATA_BLOCK_LENGTH;i++){
		data[i]=temp_data[final_message_permutation[i]-1];
	}
}

void encypt_data_with_subkeys(int data[],int cipher[])
{
	/*Left data block 2D array */
	int Ln[NO_OF_SBOX_OPERATIONS+1][SUB_DATA_BLOCK_LENGTH]={0};
	/*Right data block 2D array */
	int Rn[NO_OF_SBOX_OPERATIONS+1][SUB_DATA_BLOCK_LENGTH]={0};

	/*Initialize L0 and R0 */
	memcpy(Ln[0],data,SUB_DATA_BLOCK_LENGTH*sizeof(int));
	memcpy(Rn[0],data+SUB_DATA_BLOCK_LENGTH,SUB_DATA_BLOCK_LENGTH*sizeof(int));

	printf("L0 :\n");
	displayIntArray(Ln[0],SUB_DATA_BLOCK_LENGTH);
	printf("R0 :\n");
	displayIntArray(Rn[0],SUB_DATA_BLOCK_LENGTH);

	/*Apply the formula in 16 iterations
	 * Ln = Rn-1
	 * Rn = Ln-1 XOR f(Rn-1,Kn)
	 */
	int counter=1;
	for (int i=1;i<=16;i++){
		/* Ln = Rn-1 */
		int result[SUB_DATA_BLOCK_LENGTH]={0};
		memcpy(Ln[i],Rn[i-1],SUB_DATA_BLOCK_LENGTH*sizeof(int));
		/* f(Rn-1,Kn) */
		func(i,Rn,sub_key,result);
		/* R(n) = L(n-1) XOR f(R(n-1),K(n)) , in our case result= f(R(n-1) , K(n) )*/
		XOR_function(result,Ln,i-1,Rn,i);
	}
	printf("Ln[16]: \n");
	displayIntArray(Ln[16],32);
	printf("Rn[16]: \n");
	displayIntArray(Rn[16],32);

	/* Reverse Swap L16R16 to R16L16 */
	memcpy(cipher,Rn[16],SUB_DATA_BLOCK_LENGTH*sizeof(int));
	memcpy(cipher+SUB_DATA_BLOCK_LENGTH,Ln[16],SUB_DATA_BLOCK_LENGTH*sizeof(int));

}

void func(int index,int right[][SUB_DATA_BLOCK_LENGTH],int sub_key[][SUB_KEY_LENGTH],int result[]){
	int Er[SUB_KEY_LENGTH]={0};
	int xor_result[SUB_KEY_LENGTH]={0};
	//int SBOX_output[SUB_DATA_BLOCK_LENGTH]={0};
	int SBOX_index=0;
	int SBOX_index2=0;
	int temp_result[SUB_DATA_BLOCK_LENGTH]={0};

	//Calculate E(Rn-1)
	for(int i=0;i<SUB_KEY_LENGTH;i++){
		Er[i]=right[index-1][message_expansion[i]-1];
	}

	//[ Kn ] XOR [ E(Rn-1) ]
	XOR(Er,sub_key,index-1,xor_result);

	printf("XOR result: \n");
	displayIntArray(xor_result,48);

	//Calculate S1(B1)S2(B2)S3(B3)S4(B4)S5(B5)S6(B6)S7(B7)S8(B8)
	for(int i=1;i<=8;i++){
		printf("SBOX index: %d \n",SBOX_index);
		compute_SBOX(i,xor_result,result,&SBOX_index,&SBOX_index2);
		SBOX_index2= SBOX_index2+4;
	}
//	printf("SBOX output: \n");
//	displayIntArray(result,32);

	// Do a permutation P of the S-box output to obtain the final value of func
	//f = P(S1(B1)S2(B2)...S8(B8))
	memcpy(temp_result,result,SUB_DATA_BLOCK_LENGTH*sizeof(int));
	for(int i=0;i<SUB_DATA_BLOCK_LENGTH;i++)
	{
			result[i]=temp_result[right_sub_message_permutation[i]-1];
	}

//	printf("After Permutation: \n");
//	displayIntArray(result,32);
}


void XOR(int arr1[], int arr2[][SUB_KEY_LENGTH], int index, int result[])
{
	for(int i=0;i<SUB_KEY_LENGTH;i++){
		result[i]=arr1[i] ^ arr2[index][i];
	}
}


void XOR_function(int arr1[], int arr2[][SUB_DATA_BLOCK_LENGTH], int index, int result[][SUB_DATA_BLOCK_LENGTH],int index2)
{
	for(int i=0;i<SUB_DATA_BLOCK_LENGTH;i++){
		result[index2][i]=arr1[i] ^ arr2[index][i];
	}
}

void compute_SBOX(int round,int xor_result[],int SBOX_output[], int *SBOX_index,int *SBOX_index2){
	int data[SBOX_INPUT]={0};
	int row=0;
	int column=0;
	int SBOX_value=0;
	int index=*SBOX_index;
	// 6 bit input data block
	memcpy(data,xor_result+(*SBOX_index),SBOX_INPUT*sizeof(int));
	printf("Data: \n");
	displayIntArray(data,6);
	// get row
	getRow(data,&row);
	//get column
	getColumn(data,&column);
	printf("Row: %d \n",row);
	printf("Column: %d \n",column);
	//get SBOX value based on row & column
	getSBOX_value(round,row,column,&SBOX_value);
	printf("S BOX value: %d \n",SBOX_value);
	//convert integer SBOX value to 4 bit binary
	int_to_bin_digit(SBOX_value,4, SBOX_output,SBOX_index2);
	printf("SBOX BINARY VALUE: \n");
	displayIntArray(SBOX_output,4);
	*SBOX_index= *SBOX_index + 6;
}

void getRow(int data[],int *row){
	int bin_row[2]={0};
	bin_row[0]=data[0];
	bin_row[1]=data[5];

	for (int i = 0; i <=1; i++ )
		{
		*row = (*row) + (pow(2,1-i) * bin_row[i]);
		}
}

void getColumn(int data[],int *column){
	int bin_col[4]={0};
	bin_col[0]=data[1];
	bin_col[1]=data[2];
	bin_col[2]=data[3];
	bin_col[3]=data[4];

	for (int i = 0; i <=3; i++ )
	{
		 *column = (*column) + (pow(2,3-i) * bin_col[i]);
	}
}

void getSBOX_value(int round,int row,int column,int *SBOX_value){
	switch(round){
		case 1:
			*SBOX_value=S1[row][column];
			break;
		case 2:
			*SBOX_value=S2[row][column];
			break;
		case 3:
			*SBOX_value=S3[row][column];
			break;
		case 4:
			*SBOX_value=S4[row][column];
			break;
		case 5:
			*SBOX_value=S5[row][column];
			break;
		case 6:
			*SBOX_value=S6[row][column];
			break;
		case 7:
			*SBOX_value=S7[row][column];
			break;
		case 8:
			*SBOX_value=S8[row][column];
			break;
		default:
			printf("Invalid SBOX ....\n");
			break;
	}
}

void convertIntToBinaryArray(int num, int *arr, int *index) {
	if (num == 0 || *index >= SUB_DATA_BLOCK_LENGTH)
		return;
	convertIntToBinaryArray(num / 2, arr, index);
	if (num % 2 == 0)
		arr[(*index)++] = 0;
	else
		arr[(*index)++] = 1;

}

void int_to_bin_digit(unsigned int in, int count, int* out,int *index)
{
    /* assert: count <= sizeof(int)*CHAR_BIT */
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = (*index); i < (*index)+count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}


