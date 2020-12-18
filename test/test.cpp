#include <cpputf8.hpp>

#define ASSERT(condition) \
	{ \
		if (!(condition)) { \
			return -1; \
		} \
	}

int main() {
	static constexpr auto CHAR_A = U'a';
	static constexpr auto CHAR_CYRILIC_B = U'\u0412';
	static constexpr auto CHAR_NUMERAL_5 = U'\u2464';
	static constexpr auto CHAR_EMOJI = U'\U0001F600';
	static constexpr char32_t CHAR_INVALID = 0xD801;

	ASSERT(cpputf8::is_valid(CHAR_A));
	ASSERT(cpputf8::is_valid(CHAR_CYRILIC_B));
	ASSERT(cpputf8::is_valid(CHAR_NUMERAL_5));
	ASSERT(cpputf8::is_valid(CHAR_EMOJI));
	ASSERT(!cpputf8::is_valid(CHAR_INVALID));

	ASSERT(cpputf8::get_encode_width(CHAR_A) == 1);
	ASSERT(cpputf8::get_encode_width(CHAR_CYRILIC_B) == 2);
	ASSERT(cpputf8::get_encode_width(CHAR_NUMERAL_5) == 3);
	ASSERT(cpputf8::get_encode_width(CHAR_EMOJI) == 4);
	ASSERT(cpputf8::get_encode_width(CHAR_INVALID) == 0);

	return 0;
}
