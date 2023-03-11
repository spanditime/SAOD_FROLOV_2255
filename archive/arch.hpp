#include <cstdint>
#include <iostream>
#include <map>
#include <cstring>
#include <fstream>

class BitReader{
private:
	uint8_t*data;
	std::size_t size;
	uint64_t bytesoffset=0;
	uint64_t bitsoffset=0;
public:
	BitReader(uint8_t*Data,std::size_t Size){
		data = Data;
		size = Size;
	}
	uint64_t getBit(){
		uint64_t ret = (data[bytesoffset] >> (bitsoffset)) & 0x01;
		bitsoffset += 1;
		bytesoffset += bitsoffset / 8;
		bitsoffset %= 8;
		return ret;
	}
	uint64_t getBits(uint8_t len){
		uint64_t ret = 0x00;
		for(uint8_t i= 0; i < len; i++){
			ret |= (getBit() << i);
		}
		return ret;
	}
	void moveBytes(uint64_t bytes){
		bytesoffset += bytes;
	}
	void moveBits(uint8_t bits){
		bytesoffset += bits / 8;
		bitsoffset += bits % 8;
		bytesoffset += bitsoffset / 8;
		bitsoffset %= 8;
	}
};

class BitWriter{
private:
	std::ofstream fst;
	uint8_t byte=0;
	uint8_t fill=0;
	void writeByte(){
		fst.write((char*)&byte, 1);
		fill = 0;
		byte = 0;
	}
public:
	BitWriter(const char*filename){
		fst = std::ofstream(filename, std::ios::binary);
	}
	void writeBit(uint8_t bit){
		byte >>=1;
		fill += 1;
		byte |= (bit & 1) << 7;
		if(fill == 8){
			writeByte();
		}
	}
	void writeBits(uint64_t bits, uint8_t len){
		for(uint8_t i = 0; i < len; i++){
			writeBit(bits);
			bits >>=1;
		}
	}
	void close(){
		if(fill){
			byte >>= 8-fill;
			writeByte();
		}
		fst.close();
	}
};

class Archive{
public:
	static char* decompress(uint8_t* data, std::size_t size) {
		uint64_t letters = ((uint64_t*)data)[0];
		std::cout<< "letter = "<<letters<<std::endl;

		uint8_t kwmsize = data[8];
		uint8_t n = 0;
		for(uint8_t t = kwmsize;t;t >>=1,n++);
		uint8_t alps = data[9];
		BitReader reader = BitReader(data,size);
		reader.moveBytes(10);

		std::cout<<"max size of kword = "<<uint64_t(kwmsize)<<std::endl << "alphabet len = " << uint64_t(alps) << std::endl;
		std::cout<<"n = " << uint64_t(n) << std::endl;


		char*message = new char[letters+1];

		// decompress an alphabet
		std::map<std::pair<uint8_t,uint8_t>,char> alphabet; // [<Kword,size of kword in bits>] = ascii character
		for(uint8_t i = 0; i < alps; i++){
			char c = reader.getBits(8);
			uint8_t m, kword;
			m = reader.getBits(n);
			kword = reader.getBits(m);
			alphabet[std::make_pair(kword,m)] = c;
			std::cout<< c << "- size="<<uint64_t(m)<<" kword="<<uint64_t(kword) << std::endl;
		}

		std::cout<<"Message:\n";
		for(uint64_t l = 0; l < letters; l++){
			uint8_t kword=0,m=0;
			do{
				kword |= reader.getBit() << m;
				m+=1;
				if(alphabet.count(std::make_pair(kword, m))){
					break;
				}
				if(m>kwmsize){
					std::cout<<"EERRRROORR\n";
					return NULL;
				}
			}while(true);
			message[l] = alphabet[std::make_pair(kword, m)];
		}
		message[letters] = '\0';

		std::cout<< message << std::endl;
		return message;
	}
};
