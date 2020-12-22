#include "cpputf8_test.hpp"

#include <cpputf8.hpp>

int main() {
	ASSERT(cpputf8::decode_first("a").first == CHAR_A);
	ASSERT(cpputf8::decode_first("\xD0\x92").first == CHAR_CYRILIC_B);
	ASSERT(cpputf8::decode_first("\xE2\x91\xA4").first == CHAR_NUMERAL_5);
	ASSERT(cpputf8::decode_first("\xF0\x9F\x98\x80").first == CHAR_EMOJI);

	ASSERT(cpputf8::decode_first("a").second == 1);
	ASSERT(cpputf8::decode_first("\xD0\x92").second == 2);
	ASSERT(cpputf8::decode_first("\xE2\x91\xA4").second == 3);
	ASSERT(cpputf8::decode_first("\xF0\x9F\x98\x80").second == 4);

	return 0;
}
