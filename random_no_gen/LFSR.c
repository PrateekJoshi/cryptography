#include <stdio.h>
#include <stdint.h>

//LFSR are used to get pseudo random numbers of particular number of bits

int main(int argc, char **argv) {
	uint16_t lfsr=0xACE1u;   // 16 bit num: 1001 1100 1110 0001
	unsigned int period=0;
	char rand_str[16+1];   //+1 for '\0' char

	do{
		unsigned lsb= lfsr & 1; //get least significant bit
		lfsr=lfsr>>1; 			//shift register to right
		if(lsb==1)				//only apply toggle mask if lsb is 1
		{
			lfsr=lfsr^0xB400u;
		}
		++period;
		//fill lfsr bits at 15 positions in the rand_str array
		for(int i=0;i<16;i++){
			rand_str[15-i]=(lfsr & (1 << i)) ? '1' : '0' ;
		}
		rand_str[16]='\0';
		printf("%10d : %s\n",period,rand_str);
	} while(lfsr != 0xACE1u);

	return 0;
}
