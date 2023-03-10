#include "arch.hpp"



int main(){
	uint8_t a[]{
		0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // size in letters = 2
		0x02, //max size of keyword
		0x02, // size of alphabet
		//first letter of aplhabet
		0x48, // for H 
		0b10000110,// 10=2 - size of kword, 00 - kword
		0b10011010,// 01101001 - ascii "i", 10=2 - size of kword, 10-keyword
		0b00100000, // 00-H, 01-i, 0000- nothing
	};
	// total size of a message is 4 bits not 16, but there is also 4 of empty bits that have to be there
	// 24 bits of huffman tree and 80 bits of utility data 112 bits in total
	uint8_t s[]{
		0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // size in letters = 10
		0x02, //max size of keyword
		0x03, // size of alphabet
		//first letter of aplhabet
		0x48, // for H 
		0b10000110,// 10=2 - size of kword, 00 - kword
		0b10011010,// 01101001 - ascii "i", 10=2 - size of kword, 10-keyword
		0x21, // for !
		0b10111110, // 10=2 - size of kword, 11 - kword/ message starts 11 - ! 10 - i
		0b00001011, // HHi!
		0b00101111, // Hi!!
	};
	// total size of message is 20 < 80, but in total with all utility data needed to decompress its 136 bits

	Archive::decompress(a,8);
	Archive::decompress(s, 17);
}
