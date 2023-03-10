#include <cstdint>
#include <iostream>
#include <map>

uint8_t getBit(uint8_t*data,uint64_t bytesoffset,uint8_t bitsoffset){
	return (data[bytesoffset] >> (7-bitsoffset)) & 0x01;
}

uint8_t getBits(uint8_t*data,uint64_t bytesoffset,uint8_t bitsoffset,uint8_t len){
	uint8_t ret = 0x00;
	for(uint8_t i= 0; i < len; i++){
		ret |= getBit(data,bytesoffset + (bitsoffset+i)/8,(bitsoffset+i)%8);
		ret <<=1;
	}
	ret >>= 1;
	return ret;
}

class Archive{
public:
	static char* decompress(uint8_t* data, std::size_t size) {
		uint64_t letters = ((uint64_t*)data)[0];
		std::cout<< "letter = "<<letters<<std::endl;

		uint8_t kwmsize = data[8];
		uint8_t n = 0;
		for(uint8_t t = kwmsize;t;t >>=1,n++);
		uint8_t alps = data[9];

		std::cout<<"max size of kword = "<<uint64_t(kwmsize)<<std::endl << "alphabet len = " << uint64_t(alps) << std::endl;
		std::cout<<"n = " << uint64_t(n) << std::endl;

		uint64_t bytesoffset = 10,bitsoffset = 0;

		char*message = new char[letters+1];

		// decompress an alphabet
		std::map<std::pair<uint8_t,uint8_t>,char> alphabet; // [<Kword,size of kword in bits>] = ascii character
		for(uint8_t i = 0; i < alps; i++){
			char c = getBits(data,bytesoffset,bitsoffset,8);
			bytesoffset += 1;
			uint8_t m, kword;
			m = getBits(data, bytesoffset,bitsoffset,n);
			bitsoffset += n;
			bytesoffset += bitsoffset/8;
			bitsoffset %=8;
			kword = getBits(data, bytesoffset,bitsoffset,m);
			bitsoffset += m;
			bytesoffset += bitsoffset/8;
			bitsoffset %=8;
			alphabet[std::make_pair(kword,m)] = c;
			std::cout<< c << "- size="<<uint64_t(m)<<" kword="<<uint64_t(kword) << std::endl;
		}

		std::cout<<"Message:\n";
		for(uint64_t l = 0; l < letters; l++){
			uint8_t kword=0,m=0;
			do{
				kword <<=1;
				kword |= getBit(data,bytesoffset, bitsoffset);
				bitsoffset += 1;
				bytesoffset += bitsoffset/8;
				bitsoffset %=8;
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
