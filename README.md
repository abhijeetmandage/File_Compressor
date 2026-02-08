#Project Overview

This project implements lossless data compression and decompression using the Huffman Coding algorithm in C++.
It compresses a text file into a binary encoded file and reconstructs the exact original text during decompression.

#compresion steps
Read the complete text from input.txt.

Calculate frequency of each character.

Build the Huffman tree using a min-priority queue.

Generate Huffman binary codes for all characters.

Encode the original text into a bit string.

Save encoded bit string to compreseddatafile.txt.

Pack bits into bytes and store in compresedbinary_file.bin.

Store character-to-code mapping in codeinfo.txt.

#Decompresion steps
Load Huffman code mapping from codeinfo.txt.

Create reverse mapping (binary code → character).

Open compresedbinary_file.bin.

Read total number of valid bits from file header.

Extract bits byte-by-byte using bit operations.

Match bit patterns with reverse Huffman map.

Write decoded characters to decoded_outputfile.txt.

Reconstruct the exact original text.
