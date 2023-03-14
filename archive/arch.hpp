#include <cstdint>
#include <iostream>
#include <map>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>

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
		uint64_t ret = (data[bytesoffset] >> (7-bitsoffset)) & 0x01;
		bitsoffset += 1;
		bytesoffset += bitsoffset / 8;
		bitsoffset %= 8;
		return ret;
	}
	uint64_t getBits(uint8_t len){
		uint64_t ret = 0x00;
		for(uint8_t i= 0; i < len; i++){
			ret <<=1;
			ret |= getBit();
		}
		return ret;
	}
	uint64_t getBitOffset(){
		return bitsoffset;
	}
	uint64_t getByteOffset(){
		return bytesoffset;
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
		byte |= (bit & 0b1) << (7-fill); // fixed as it should be 
		fill += 1;
		if(fill == 8){
			writeByte();
		}
	}
	void writeBits(uint64_t bits, uint8_t len){
		for(uint8_t i = 0; i < len; i++){
			writeBit(bits >> (len - 1 - i));
		}
	}
	void close(){
		if(fill){
			writeByte();
		}
		fst.close();
	}
};

class HuffmansTree{
private:
	HuffmansTree *lc, *rc;
	uint64_t weight=0;
	char ch;
	bool is_ch;
	void constructRecursive(std::map<char,std::pair<uint64_t,uint8_t>> &mp,uint64_t code,uint8_t length) const {
		if(is_ch){
			mp[ch] = std::make_pair(code,length);
		}else{
			if(lc != nullptr){
				lc->constructRecursive(mp, code << 1, length + 1);
			}
			if(rc != nullptr){
				rc->constructRecursive(mp, (code << 1) + 1, length + 1);
			}
		}
	}
public:
	HuffmansTree(char c,uint64_t w){
		ch = c; weight = w; is_ch = true;
	}
	HuffmansTree(HuffmansTree *l, HuffmansTree *r){
		lc = l; rc = r; is_ch = false;
		if(lc != nullptr){
			weight += lc->weight;
		}
		if(rc != nullptr){
			weight += rc->weight;
		}
	}
	~HuffmansTree(){
		if(lc != nullptr){
			delete lc;
		}
		if(rc != nullptr){
			delete rc;
		}
	}
	std::map<char,std::pair<uint64_t,uint8_t>> constructKwordMap() const {
		std::map<char,std::pair<uint64_t,uint8_t>> ret;
		constructRecursive(ret, 0, 0);
		return ret;
	}
	const bool is_char() const{
		return is_ch;
	}
	const uint64_t getWeight() const{
		return weight;
	}
};

inline uint8_t calculate_n(const uint8_t &kwmsize){
	uint8_t n=0;
	for(uint8_t t = kwmsize;t;t >>=1,n++);
	return n;
}

class Archive{
public:
	static char* decompress(const char* filename){
		std::ifstream infile(filename);
		
		uint8_t *buffer;
		//get length of file
		infile.seekg(0, std::ifstream::end);
		size_t length = infile.tellg();
		infile.seekg(0, std::ios::beg);
		
		buffer = new uint8_t[length];

		//read file
		infile.read((char*)buffer, length);
		return decompressRaw(buffer,length);
	}
	static char* decompressRaw(uint8_t* data, std::size_t size) {
		BitReader reader = BitReader(data,size);
		uint64_t letters = 0;
		for(uint8_t i = 0; i < sizeof(uint64_t); i++){
			uint8_t fr = reader.getBits(8);
			((uint8_t *)&letters)[sizeof(uint64_t) - 1 - i] = fr;
		}

		uint8_t kwmsize = reader.getBits(8);
		uint8_t n = calculate_n(kwmsize);
		uint8_t alps = reader.getBits(8);

		char*message = new char[letters+1];

		// decompress an alphabet
		std::map<std::pair<uint64_t,uint8_t>,char> alphabet; // [<Kword,size of kword in bits>] = ascii character
		for(uint8_t i = 0; i < alps; i++){
			char c = reader.getBits(8);
			uint8_t m, kword;
			m = reader.getBits(n);
			kword = reader.getBits(m);
			alphabet[std::make_pair(kword,m)] = c;
		}

		// decompress a message
		for(uint64_t l = 0; l < letters; l++){
			uint64_t kword=0;
			uint8_t m=0;
			do{
				kword <<=1;
				kword |= reader.getBit();
				m+=1;
				if(alphabet.count(std::make_pair(kword, m))){
					break;
				}
				if(m>kwmsize){
					message[l] = '\0';
					// throw an error
					return message;
				}
			}while(true);
			message[l] = alphabet[std::make_pair(kword, m)];
		}

		return message;
	}
	
	static void compress(const char*message,const char*filename){
		//open BitStream for writing
		BitWriter bwa(filename);

		std::map<char, uint64_t> weighted;
		uint64_t stlen = std::strlen(message);
		for(uint i = 0; i < stlen; i++){
			if(weighted.count(message[i])){
				weighted[message[i]] += 1;
			}else{
				weighted[message[i]] = 1;
			}
		}

		std::vector<HuffmansTree *> Huffman;
		for(auto n : weighted){
			Huffman.push_back(new HuffmansTree(n.first, n.second));
		}

		while(Huffman.size() > 1){
			HuffmansTree * min1, *min2;
			if(Huffman[0]->getWeight() < Huffman[1]->getWeight()){
				min1 = Huffman[0]; min2 = Huffman[1];
			}else{
				min1 = Huffman[1]; min2 = Huffman[0];
			}
			for(uint64_t i = 2; i < Huffman.size();i++){
				if(Huffman[i]->getWeight() < min2->getWeight()){
					if(Huffman[i]->getWeight() < min1->getWeight()){
						min2 = min1;
						min1 = Huffman[i];
					}else{
						min2 = Huffman[i];
					}
				}
			}
			Huffman.erase(std::remove(Huffman.begin(), Huffman.end(),min1), Huffman.end());
			Huffman.erase(std::remove(Huffman.begin(), Huffman.end(),min2), Huffman.end());
			Huffman.push_back(new HuffmansTree(min1,min2));
		}
		if(Huffman[0]->is_char()){
			Huffman[0] = new HuffmansTree(Huffman[0],nullptr);
		}

		auto kwmp = Huffman[0]->constructKwordMap();
		uint8_t maxkwsize = (*kwmp.begin()).second.second;
		uint8_t minkwsize = maxkwsize;
		for(auto n : kwmp){
			if(n.second.second > maxkwsize){
				maxkwsize = n.second.second;
			} else if(n.second.second < minkwsize){
				minkwsize = n.second.second;
			}
		}
		uint8_t n = calculate_n(maxkwsize);
		
		// Start writing header
		// write length
		bwa.writeBits(stlen, 64);
		// mkwsize
		bwa.writeBits(maxkwsize,8);
		// alphabet size
		bwa.writeBits(kwmp.size(),8);
		//Alphabet
		for(auto lt = kwmp.begin(); lt != kwmp.end(); ++lt){
			bwa.writeBits((*lt).first, 8);// ascii
			bwa.writeBits((*lt).second.second, n); // kword length in bits
			bwa.writeBits((*lt).second.first, (*lt).second.second); // kword
		}
		// write message
		
		for(uint64_t i = 0; i < stlen; i++){
			char c = message[i];
			uint64_t kw = kwmp[c].first;
			uint8_t sz = kwmp[c].second;
			bwa.writeBits(kw , sz);
		}
		bwa.close();
	}
};
