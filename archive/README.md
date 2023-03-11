# Archive
Uses Huffman's encoding to compress text into a .compressed file

## Bit structure of the file
#### Header
64 bits - number of ascii characters in encoded message\
8 bits = __*mkwsize*__ - max size of encoded keyword in bits\
8 bits = __*L*__ size of an alphabet\
#### Alphabet
__Letter__ ( repeats __*L*__ times )\
8 bits - ascii character\
__*N*__ bits = __*M*__ - size of a keyword (__*N*__ is determined by __*mkwsize*__\
__*M*__ bits - encoded keyword\
#### Data
All of the remaining bits are consecutive *l* keywords that can be converted back to the original text using the alphabet
