#include "cpputf8_test.hpp"

#include <cpputf8.hpp>

int main() {
	ASSERT(cpputf8::get_encode_width(CHAR_A) == 1);
	ASSERT(cpputf8::get_encode_width(CHAR_CYRILIC_B) == 2);
	ASSERT(cpputf8::get_encode_width(CHAR_NUMERAL_5) == 3);
	ASSERT(cpputf8::get_encode_width(CHAR_EMOJI) == 4);
	ASSERT(cpputf8::get_encode_width(CHAR_INVALID) == 0);

	return 0;
}
