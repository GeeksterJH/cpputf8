#include "cpputf8_test.hpp"

#include <cpputf8.hpp>

int main() {
	ASSERT(
		cpputf8::get_info(CHAR_A)->category ==
		cpputf8::CodepointCategory::LetterLowercase);
	ASSERT(cpputf8::get_info(CHAR_CYRILIC_B)->value == CHAR_CYRILIC_B);
	ASSERT(cpputf8::get_info(CHAR_NUMERAL_5)->value == CHAR_NUMERAL_5);
	ASSERT(cpputf8::get_info(CHAR_EMOJI)->value == CHAR_EMOJI);

	ASSERT(!cpputf8::get_info(0xD801));

	return 0;
}
