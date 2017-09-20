#include <stdio.h>
#include <string.h>

//http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

#define DATA_BLOCK_LENGTH 64
#define INITIAL_KEY_LENGTH 64
#define PERMUTED_KEY_LENGTH 56
#define SUB_KEY_PERMUTED_LENGTH 28
#define NO_OF_SUB_KEYS 16
#define SUB_KEY_LENGTH 48

void DES(int *data,int data_length,int *key,int *cipher, int *cipher_length);
void initial_permutation_key(int key[]);

void displayIntArray(int *array, int size);
void rotate_array(int arr[],int n,int d);

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
int sub_key1[SUB_KEY_LENGTH]={0};
int sub_key2[SUB_KEY_LENGTH]={0};
int sub_key3[SUB_KEY_LENGTH]={0};
int sub_key4[SUB_KEY_LENGTH]={0};
int sub_key5[SUB_KEY_LENGTH]={0};
int sub_key6[SUB_KEY_LENGTH]={0};
int sub_key7[SUB_KEY_LENGTH]={0};
int sub_key8[SUB_KEY_LENGTH]={0};
int sub_key9[SUB_KEY_LENGTH]={0};
int sub_key10[SUB_KEY_LENGTH]={0};
int sub_key11[SUB_KEY_LENGTH]={0};
int sub_key12[SUB_KEY_LENGTH]={0};
int sub_key13[SUB_KEY_LENGTH]={0};
int sub_key14[SUB_KEY_LENGTH]={0};
int sub_key15[SUB_KEY_LENGTH]={0};
int sub_key16[SUB_KEY_LENGTH]={0};



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
			sub_key1[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C2,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D2,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key2[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 3 */
	memcpy(temp_subkey,C3,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D3,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key3[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 4 */
	memcpy(temp_subkey,C4,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D4,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key4[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 5 */
	memcpy(temp_subkey,C5,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D5,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key5[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 6 */
	memcpy(temp_subkey,C6,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D6,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key6[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 7 */
	memcpy(temp_subkey,C7,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D7,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key7[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 8 */
	memcpy(temp_subkey,C8,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D8,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key8[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C9,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D9,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key9[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 10 */
	memcpy(temp_subkey,C10,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D10,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key10[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 11 */
	memcpy(temp_subkey,C11,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D11,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key11[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 12 */
	memcpy(temp_subkey,C12,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D12,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key12[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 13 */
	memcpy(temp_subkey,C13,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D13,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key13[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C14,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D14,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key14[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 15 */
	memcpy(temp_subkey,C15,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D15,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key15[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}
	/* subkey 2 */
	memcpy(temp_subkey,C16,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	memcpy(temp_subkey+SUB_KEY_PERMUTED_LENGTH,D16,SUB_KEY_PERMUTED_LENGTH*sizeof(int));
	for(int i=0;i<SUB_KEY_LENGTH;i++)
	{
			sub_key16[i]=temp_subkey[initial_key_permutaion2[i]-1];
	}

	printf("Final 16 Subkeys: \n");
	displayIntArray(sub_key1,SUB_KEY_LENGTH);
	displayIntArray(sub_key2,SUB_KEY_LENGTH);
	displayIntArray(sub_key3,SUB_KEY_LENGTH);
	displayIntArray(sub_key4,SUB_KEY_LENGTH);
	displayIntArray(sub_key5,SUB_KEY_LENGTH);
	displayIntArray(sub_key6,SUB_KEY_LENGTH);
	displayIntArray(sub_key7,SUB_KEY_LENGTH);
	displayIntArray(sub_key8,SUB_KEY_LENGTH);
	displayIntArray(sub_key9,SUB_KEY_LENGTH);
	displayIntArray(sub_key10,SUB_KEY_LENGTH);
	displayIntArray(sub_key11,SUB_KEY_LENGTH);
	displayIntArray(sub_key12,SUB_KEY_LENGTH);
	displayIntArray(sub_key13,SUB_KEY_LENGTH);
	displayIntArray(sub_key14,SUB_KEY_LENGTH);
	displayIntArray(sub_key15,SUB_KEY_LENGTH);
	displayIntArray(sub_key16,SUB_KEY_LENGTH);


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
