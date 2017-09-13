#include <stdio.h>
#include <stdlib.h>

int getSize(char *array);
int hashCode(const char *str,int size);
void convertAsciiToInt(char *ascii, int *data,int *size);

void convertIntToBinaryArray(int num,int *arr,int *index);
void encryptStreamCipher(int key[],int data[],int encypted_data[],int data_size);
void decryptStreamCipher(int key[],int enc_data[],int data_size);

#define MAX_SIZE 100


int main(int argc, char **argv) {
	char array_ascii[MAX_SIZE];
	char ascii_key[MAX_SIZE];
	int data[MAX_SIZE];
	int key[MAX_SIZE];
	int encypted_data[MAX_SIZE];
	int seed;
	int key_int;
	int key_size=0;
	int index=0;
	int data_size=0;
	/* 1. Get sequence of binary chars */
	fprintf(stdout,"Enter data to encrypt: \n");
	fscanf(stdin,"%s",array_ascii);
	/* 2. Convert char binary array to int */
	convertAsciiToInt(array_ascii,data,&data_size);
	/* 3. Read the key string from user */
	fprintf(stdout,"Enter key to encrypt data with: \n");
	fscanf(stdin,"%s",ascii_key);
	/* 4.Get hash code from the key */
	key_size=getSize(ascii_key);
	seed=hashCode(ascii_key,key_size);
	/* 5. Set the key as seed to random number generator to create a key of random bits */
	srand(seed);
	key_int=rand();
	/* 6. Convert key to binary int array */
	convertIntToBinaryArray(key_int,key,&index);
	/* 7. Encrypt : (Binary data) XOR (Binary key) */
	encryptStreamCipher(key,data,encypted_data,data_size);
	/* 8. Display encrypted data */
	printf("Encrypted Data: ");
	for(int i=0;i<data_size;i++){
		printf("%d",encypted_data[i]);
	}
	printf("\n");
	/* 9. Again Decrypt data and verify initial data */
	decryptStreamCipher(key,encypted_data,data_size);
	printf("Decrypted Data: ");
	for (int i = 0; i < data_size; i++) {
		printf("%d", encypted_data[i]);
	}
	printf("\n");
	return 0;
}

int getSize(char *array){
	int size=0;
	int i=0;
	while ( (i!=MAX_SIZE) && (array[i]!='\0') ){
		i++;
		size++;
	}
	return size;
}

void convertAsciiToInt(char *ascii, int *data,int *index){
	*index=0;
	while( ascii[*index]!='\0'){
		data[*index]=((int)ascii[*index]-48);
		(*index)++;
	}
}

int hashCode(const char *str,int size) {
    int hash = 0;
    for (int i = 0; i < size; i++) {
        hash = 31 * hash + str[i];
    }
    return hash;
}

void convertIntToBinaryArray(int num,int *arr,int *index){
	if( num==0 || *index >= MAX_SIZE )
		return;
	convertIntToBinaryArray(num/2,arr,index);
	if (num%2 == 0)
		arr[(*index)++]=0;
	else
		arr[(*index)++]=1;

}

void encryptStreamCipher(int key[],int data[],int encypted_data[],int data_size){
	for(int i=0;i<data_size;i++){
		encypted_data[i]=data[i] ^ key[i];
	}
}

void decryptStreamCipher(int key[],int enc_data[],int data_size){
	for(int i=0;i<data_size;i++){
		enc_data[i]=enc_data[i] ^ key[i];
	}
}

