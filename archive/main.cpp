#include "arch.hpp"



int main(){
	BitWriter bwa("a.compressed");
	bwa.writeBits(2, 64); // size in letters = 2
	bwa.writeBits(2,8); // max size of keyword
	bwa.writeBits(2,8); // size of alphabet
	bwa.writeBits('H',8);
	bwa.writeBits(0b10,2); // size of kword
	bwa.writeBits(0b00,0b10); // kword
	bwa.writeBits('i', 8); 
	bwa.writeBits(0b10, 2); // size of kword
	bwa.writeBits(0b10, 0b10); // kword
	bwa.writeBits(0b00,2); // kword for H
	bwa.writeBits(0b10,2); // kword for i
	bwa.close();

	// total size of a message is 4 bits not 16, but there is also 4 of empty bits that have to be there
	// 24 bits of huffman tree and 80 bits of utility data 112 bits in total
	uint8_t s[]{
		0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // size in letters = 10
		0x02, //max size of keyword
		0x03, // size of alphabet
		//first letter of aplhabet
		0x48, // for H 
		0b10010010,// 10=2 - size of kword, 00 - kword
		0b10100110,// 01101001 - ascii "i", 10=2 - size of kword, 10-keyword
		0x21, // for !
		0b10111110, // 10=2 - size of kword, 11 - kword/ message starts 11 - ! 10 - i
		0b11100000, // HHi!
		0b11111000, // Hi!!
	};
	// total size of message is 20 < 80, but in total with all utility data needed to decompress its 136 bits

	Archive::decompress("a.compressed");
	Archive::decompressRaw(s, 17);
}
