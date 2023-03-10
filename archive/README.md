# Archive
Uses Huffman's encoding to compress text into a .compressed file

## Bit structure of the file
#### Header
64 bits - strlen of text
8 bits = *mkwsize* - max size of encoded keyword in bits
8 bits = *l* size of an alphabet
#### Alphabet
Letter ( repeats *l* times )
8 bits - ascii character
*n* bits = *m* - size of a keyword (*n* is determined by *mkwsize*
*m* bits - encoded keyword
#### Data
All of the remaining bits are consecutive *l* keywords that can be converted back to the original text using the alphabet
