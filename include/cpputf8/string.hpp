#pragma once

#include <tuple>
#include <string_view>

namespace cpputf8 {
	[[nodiscard]] static constexpr inline std::pair<char32_t, std::size_t>
	decode_first(std::string_view const string) noexcept {
		constexpr std::pair ERROR_RESULT = {
			REPLACEMENT_CHARACTER,
			get_encode_width(REPLACEMENT_CHARACTER),
		};

		if (string.empty()) {
			return {U'\0', 1};
		}

		auto const first_byte = string[0];
		std::size_t width = 1;

		constexpr uint8_t WIDTH_INDICATOR_MASK_2 = 0b1110'0000;
		constexpr uint8_t WIDTH_INDICATOR_MASK_3 = 0b1111'0000;
		constexpr uint8_t WIDTH_INDICATOR_MASK_4 = 0b1111'1000;
		constexpr uint8_t CONTINUATION_MASK = 0b0011'1111;

		uint8_t mask = 0;

		if ((first_byte & 0b1000'0000) == 0) {
			return {first_byte, width};
		} else if ((first_byte & WIDTH_INDICATOR_MASK_2) == 0b1100'0000) {
			mask = WIDTH_INDICATOR_MASK_2;
			width = 2;
		} else if ((first_byte & WIDTH_INDICATOR_MASK_3) == 0b1110'0000) {
			mask = WIDTH_INDICATOR_MASK_3;
			width = 3;
		} else if ((first_byte & WIDTH_INDICATOR_MASK_4) == 0b1111'0000) {
			mask = WIDTH_INDICATOR_MASK_4;
			width = 4;
		} else {
			return ERROR_RESULT;
		}

		if (string.length() < width) {
			return ERROR_RESULT;
		}

		auto result = U'\0';
		int shift_amount = 0;

		for (auto byte_index = width - 1; byte_index > 0; --byte_index) {
			auto const byte = string[byte_index];
			result |= static_cast<char32_t>(
				(byte & CONTINUATION_MASK) << shift_amount);

			shift_amount += 6;
		}

		result |= static_cast<char32_t>(
			(first_byte & static_cast<uint8_t>(~mask)) << shift_amount);

		if (!is_valid(result)) {
			return ERROR_RESULT;
		}

		return {result, width};
	}

	[[nodiscard]] static constexpr inline std::size_t
	length(std::string_view const string) noexcept {
		std::size_t result = 0;

		auto it = string.begin();
		auto width = decode_first(string).second;

		while (it != string.end()) {
			++result;
			it += width;

			if (it != string.end()) {
				width = decode_first(&(*it)).second;
			}
		}

		return result;
	}
}
