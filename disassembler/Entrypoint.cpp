#include "Common.h"
#include "Registers.h"
#include "ModRM.h"
#include "Prefixes.h"
#include "Instructions.h"
#include "decoder.h"

int main() {
	byte data[] = {
		0x00,0x00,0x00,0x00,0x00,0x00
		//0x66,0x41,0x0f,0x38,0xf6,0xd1
	};

	ByteStream stream;
	zeromem(&stream, sizeof(ByteStream));
	stream.data = data;
	stream.length = 6;


	Decoder decoder;

	while (stream.eof != true && stream.pos != stream.length) {
		DecodedInstruction inst = decoder.decodeNext(stream);
		std::cout << decoder.decodedInstructionToString(inst) << std::endl;
	};
};