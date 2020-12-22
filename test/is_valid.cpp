#include "cpputf8_test.hpp"

#include <cpputf8.hpp>

int main() {
	ASSERT(cpputf8::is_valid(CHAR_A));
	ASSERT(cpputf8::is_valid(CHAR_CYRILIC_B));
	ASSERT(cpputf8::is_valid(CHAR_NUMERAL_5));
	ASSERT(cpputf8::is_valid(CHAR_EMOJI));
	ASSERT(!cpputf8::is_valid(CHAR_INVALID));

	return 0;
}
