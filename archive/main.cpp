#include "arch.hpp"



int main(){
	// Archive::decompress("a.compressed");
	// Archive::decompressRaw(s, 17);
	Archive::compress("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer sed ante in elit blandit ultricies. Vivamus efficitur sapien non lacus accumsan, vitae iaculis sem porttitor. Curabitur eu neque at quam sollicitudin faucibus quis convallis eros. In pharetra ligula ut tortor mollis tempor. Phasellus lectus orci, egestas in nulla at, feugiat posuere leo. Mauris sagittis, odio vitae pellentesque tristique, enim massa gravida arcu, quis tincidunt augue mauris vel tortor. Nullam bibendum lectus vitae erat egestas finibus. Nunc in auctor sapien. Vestibulum ultricies, tellus nec tempor luctus, purus lectus ornare metus, sed dignissim augue velit consectetur metus.","b.compressed");
	std::cout<< "decompressed message:\n" << Archive::decompress("b.compressed")<<std::endl;
}
