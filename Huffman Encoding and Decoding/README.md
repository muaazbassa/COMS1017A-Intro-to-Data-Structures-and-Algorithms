# Huffman Encoding and Decoding

I have coded a program that encodes and decodes messages using the Huffman technique.

* The program takes in input via the terminal 

## Encoder
The first program should accept a string from stdin. It should then calculate the frequency of each letter and
build the binary tree necessary to perform Huffman encoding. When calculating the priority of a leaf, it should
be done by the frequency, ties should then be broken in increasing order of the relevant ASCII/UTF-8 code.
When the frequencies have been calculated, print the priority queue characters, separated by spaces. On the
next line, print the frequencies. Print them in increasing order of priority. On the next line, you should print
out the encoded string. Following that, print out the number of bits used if characters are represented in 8-bit
UTF-8 (compatible with ASCII). The next line should contain the number of bits used in the encoded string.
The input string will only ever contain lower case letters and a spaces. No other ASCII characters will be
given.

### Sample Input:
```
she sells sea shells by the sea shore
```
### Sample Output:
```
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
```
## Decoder
The second program should read the first two lines of text from the first programs output. It first reads a line
with all the characters in increasing order or priority. The next line has the respective frequencies for these
characters. Once these lines have been read, the Huffman Tree can be reconstructed by using the exact
same process from the encoder. Next your program should read the line containing the encoded string. Your
program needs to decode the string by using the Huffman tree and output the decoded text followed by a new
line. The program can ignore all other input.
### Sample Input:
```
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
```
### Sample Output:
```
she sells sea shells by the sea shore
```

## Acknowledgement
Dr Richard Klein gave us what the program should accept as input and what it should do, he also gave the sample input and sample output
