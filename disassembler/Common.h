#pragma once

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <optional>
#include <functional>

typedef unsigned char byte;
typedef const char* cstring_t;



class ByteStream {
public:
	byte* data;
	unsigned __int32 length;
	unsigned __int32 pos;
	bool eof;

	byte peekByte() {
		if (pos >= length) return 0;
		return data[pos];
	};
	byte peekByte(unsigned int ahead) {
		if (pos + ahead >= length) return 0;
		return data[pos + ahead];
	};
	byte consumeByte() {
		if (pos >= length) {
			eof = true;
			return 0;
		};
		return data[pos++];
	};
	uint16_t consumeWord() {
		if (pos+1 >= length) {
			eof = true;
			return 0;
		};
		pos += 2;
		//return (data[pos - 2] << 8) | data[pos - 1];
		return *((uint16_t*)(&(data[pos - 2])));
	};
	uint32_t consumeDWord() {
		if (pos + 3 >= length) {
			eof = true;
			return 0;
		};
		pos += 4;
		//return (data[pos - 4] << 24) | (data[pos - 3] << 16) | (data[pos - 2] << 8) | data[pos - 1];
		return *((uint32_t*)(&(data[pos - 4])));
	};
	uint64_t consumeQWord() {
		if (pos + 7 >= length) {
			eof = true;
			return 0;
		};
		pos += 8;
		//return (data[pos - 8] << 56) | (data[pos - 7] << 48) | (data[pos - 6] << 40) | (data[pos - 5] << 32) | (data[pos - 4] << 24) | (data[pos - 3] << 16) | (data[pos - 2] << 8) | data[pos - 1];
		return *((uint32_t*)(&(data[pos - 8])));
	};

	unsigned __int64 currentLocation() { return pos; };
};


#define zeromem(dest, size) memset(dest, 0, size)

//from chromium project
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))