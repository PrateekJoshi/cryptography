#include <stdio.h>
#include <string.h>

//http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

#define DATA_BLOCK_LENGTH 64
#define INITIAL_KEY_LENGTH 64

void DES(int *data,int data_length,int *key,int *cipher, int *cipher_length);
void initial_permutation_key(int key[]);

void displayIntArray(int *array, int size);

int initial_key_permutaion[] = {57, 49,  41, 33,  25,  17,  9,
							 1, 58,  50, 42,  34,  26, 18,
							10,  2,  59, 51,  43,  35, 27,
							19, 11,   3, 60,  52,  44, 36,
							63, 55,  47, 39,  31,  23, 15,
							 7, 62,  54, 46,  38,  30, 22,
							14,  6,  61, 53,  45,  37, 29,
							21, 13,   5, 28,  20,  12,  4};

int initial_message_permutation[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
										60, 52, 44, 36, 28, 20, 12, 4,
										62, 54, 46, 38, 30, 22, 14, 6,
										64, 56, 48, 40, 32, 24, 16, 8,
										57, 49, 41, 33, 25, 17,  9, 1,
										59, 51, 43, 35, 27, 19, 11, 3,
										61, 53, 45, 37, 29, 21, 13, 5,
										63, 55, 47, 39, 31, 23, 15, 7};

int main(int argc, char **argv) {
	int message[64]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};
	int key[64]={0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1};
	int cipher[64];
	int cipher_length=0;
	DES(message,64,key,cipher,&cipher_length);
	return 0;
}

void DES(int *data,int data_length,int *key,int *cipher, int *cipher_length)
{
	/*Step 1: Create 16 subkeys, each of which is 48-bits long.*/
	initial_permutation_key(key);
	displayIntArray(key,56);
}



void displayIntArray(int *array, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d",array[i]);
	}
	printf("\n");
}

void initial_permutation_key(int key[]){
	int temp_key[INITIAL_KEY_LENGTH];
	memcpy(temp_key,key,sizeof(int)*INITIAL_KEY_LENGTH);
	printf("temp array: \n");
	displayIntArray(temp_key,64);
	printf("permuted array: \n");
	for(int i=0;i<56;i++){
		key[initial_key_permutaion[i]-1]=temp_key[i];
	//	printf("%dth becomes %d \n",initial_key_permutaion[i],i+1);
	}
}
