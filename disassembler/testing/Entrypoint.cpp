#include "../Common.h"
#include "../Registers.h"
#include "../ModRM.h"
#include "../Prefixes.h"
#include "../Instructions.h"
#include "../decoder.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace Catch;
using namespace Catch::Matchers;

#define INSTRUCTION_TEST(_name, _data, _result) SECTION(_name) { byte data[] = _data; stream.data = data; stream.length = COUNT_OF(data); DecodedInstruction decoded = decoder.decodeNext(stream); std::string str = decoder.decodedInstructionToString(decoded); REQUIRE_THAT(str, Equals(_result)); }
#define INSTRUCTION_DATA(...) {__VA_ARGS__}

TEST_CASE("Instruction Tests") {
	Decoder decoder;
	ByteStream stream;
	zeromem(&stream, sizeof(ByteStream));

	INSTRUCTION_TEST("AAA", INSTRUCTION_DATA(0x37), "AAA");
	INSTRUCTION_TEST("AAD", INSTRUCTION_DATA(0xD5, 0x0A), "AAD 0xA");
	INSTRUCTION_TEST("AAM", INSTRUCTION_DATA(0xD4, 0x0A), "AAM 0xA");
};



/*int main() {
	byte data[] = {
		0x66, 0x41, 0x0f,0x38,0xf6,0xd1,
		0x67, 0xf2, 0x0f, 0x58, 0x10,
		0xf2, 0x0f, 0x58, 0x10,
		0xf2, 0x41, 0x0f, 0x58, 0xd7,
		0x67, 0xf2, 0x0f, 0x58, 0x14, 0x85, 0x01, 0x00, 0x00, 0x00,
		0x67, 0x0f, 0x58, 0x14, 0x85, 0x01, 0x00, 0x00, 0x00,
		0x62, 0xf1, 0xef, 0x88, 0x58, 0xcb,
		0x62, 0xf1, 0xef, 0x8a, 0x58, 0xcb
	};

	ByteStream stream;
	zeromem(&stream, sizeof(ByteStream));
	stream.data = data;
	stream.length = COUNT_OF(data);


	Decoder decoder;

	while (stream.eof != true && stream.pos != stream.length) {
		DecodedInstruction inst = decoder.decodeNext(stream);
		std::cout << decoder.decodedInstructionToString(inst) << std::endl;
	};
};*/