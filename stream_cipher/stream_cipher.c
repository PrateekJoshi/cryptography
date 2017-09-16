#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function declarations */
int getSize(char *array);
int hashCode(const char *str, int size);
void convertIntToBinaryArray(int num, int *arr, int *index);
void encryptStreamCipher(int key[], int data[], int encypted_data[],int data_size);
void decryptStreamCipher(int key[], int enc_data[], int data_size);
void convertCharToBinary(char c,int *binary_arr,int *index);
void convertStringToBinary(char *str,int *binary_arr, int *size);
void convertBinaryToString(int *data,char *array_string,int *index);
char convertBinaryToChar(char *str);
void displayIntArray(int *array, int size);
void displayCharArray(char *array, int size);
#define MAX_SIZE 10000


int main(int argc, char **argv) {
	char array_string[MAX_SIZE];
	char ascii_key[MAX_SIZE];
	int data[MAX_SIZE];
	int key[MAX_SIZE];
	int encypted_data[MAX_SIZE];
	int seed;
	int key_int;
	int key_size = 0;
	int index;
	int data_size = 0;
	/* 1. Enter the data to encrypt (Do not use space in between)*/
	fprintf(stdout, "Enter data to encrypt: \n");
	fscanf(stdin, "%s", array_string);

	/* 2. Convert the string to binary data */
	convertStringToBinary(array_string,data,&data_size);
	printf("Data in binary: \n");
	displayIntArray(data,data_size);

	/* 3. Read the key string from user */
	fprintf(stdout, "Enter key to encrypt data with: \n");
	fscanf(stdin, "%s", ascii_key);

	/* 4.Get hash code from the key */
	key_size = getSize(ascii_key);
	seed = hashCode(ascii_key, key_size);

	/* 5. Set the key as seed to random number generator to create a key of random bits */
	srand(seed);
	key_int = rand();

	/* 6. Convert key to binary int array */
	convertIntToBinaryArray(key_int, key, &index);
	printf("Key in binary: \n");
	displayIntArray(key,index);

	/* 7. Encrypt : (Binary data) XOR (Binary key) */
	encryptStreamCipher(key, data, encypted_data, data_size);

	/* 8. Display encrypted data */
	printf("encrypted Data: \n");
	displayIntArray(encypted_data,data_size);

	/* 9.Now, Decrypt data and verify initial data */
	decryptStreamCipher(key, encypted_data, data_size);
	printf("Decrypted binary data: \n");
	displayIntArray(encypted_data,data_size);

	/* 10. Convert decrypted data in binary to string */
	memset(array_string,0,sizeof(array_string));
	convertBinaryToString(encypted_data,array_string,&data_size);

	/* 11.Display teh original message in string */
	printf("Decrypted Data in String: \n");
	displayCharArray(array_string,data_size);

	return 0;
}

int getSize(char *array) {
	int size = 0;
	int i = 0;
	while ((i != MAX_SIZE) && (array[i] != '\0')) {
		i++;
		size++;
	}
	return size;
}

int hashCode(const char *str, int size) {
	int hash = 0;
	for (int i = 0; i < size; i++) {
		hash = 31 * hash + str[i];
	}
	return hash;
}

void convertIntToBinaryArray(int num, int *arr, int *index) {
	if (num == 0 || *index >= MAX_SIZE)
		return;
	convertIntToBinaryArray(num / 2, arr, index);
	if (num % 2 == 0)
		arr[(*index)++] = 0;
	else
		arr[(*index)++] = 1;

}

void encryptStreamCipher(int key[], int data[], int encypted_data[],
		int data_size) {
	for (int i = 0; i < data_size; i++) {
		encypted_data[i] = data[i] ^ key[i];
	}
}

void decryptStreamCipher(int key[], int enc_data[], int data_size) {
	for (int i = 0; i < data_size; i++) {
		enc_data[i] = enc_data[i] ^ key[i];
	}
}

void convertStringToBinary(char *str,int *binary_arr,int *index) {
	*index=0;
	for (int i = 0; i<strlen(str); i++) {
		convertCharToBinary(str[i],binary_arr,index);
	}
}

void convertCharToBinary(char c,int *binary_arr,int *index) {
	for (int i = 7; i >= 0; --i) {
		binary_arr[*index]=((c & (1 << i)) ? 1 : 0);
		(*index)++;
	}
}

void convertBinaryToString(int *data,char *array_string,int *index){
	int data_size=*index;
	char char_array[data_size];
	*index=0;

	for(int i=0;i<data_size;i++){
		char_array[i]=(data[i] == 1?'1':'0');
	}

	for(int i=0;i<data_size;i=i+8){
		char sub_str[8];
		memcpy(sub_str,char_array+i,8);
		array_string[(*index)++]=convertBinaryToChar(sub_str);
	}
}

char convertBinaryToChar(char *str){
	char c=strtol(str,0,2);
	return c;
}

void displayIntArray(int *array, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d",array[i]);
	}
	printf("\n");
}

void displayCharArray(char *array, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%c",array[i]);
	}
	printf("\n");
}
