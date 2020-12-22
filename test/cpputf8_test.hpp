#pragma once

#define ASSERT(condition) \
	{ \
		if (!(condition)) { \
			return -1; \
		} \
	}

static constexpr auto CHAR_A = U'a';
static constexpr auto CHAR_CYRILIC_B = U'\u0412';
static constexpr auto CHAR_NUMERAL_5 = U'\u2464';
static constexpr auto CHAR_EMOJI = U'\U0001F600';
static constexpr char32_t CHAR_INVALID = 0xD801;
