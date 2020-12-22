#pragma once

#include <cstddef>
#include <optional>

#include "cpputf8/unicode_data.hpp"
#include "cpputf8/codepoint_info.hpp"

namespace cpputf8 {
	static constexpr auto MAX_CHAR_1 = U'\u007F';
	static constexpr auto MAX_CHAR_2 = U'\u07FF';
	static constexpr auto MAX_CHAR_3 = U'\uFFFF';
	static constexpr auto MAX_CHAR_4 = U'\U0010FFFF';

	static constexpr char32_t SURROGATE_MIN = 0xD800;
	static constexpr char32_t SURROGATE_MAX = 0xDFFF;

	static constexpr auto REPLACEMENT_CHARACTER = U'\uFFFD';

	[[nodiscard]] static constexpr inline auto
	is_surrogate(char32_t const character) noexcept {
		return character >= SURROGATE_MIN && character <= SURROGATE_MAX;
	}

	[[nodiscard]] static constexpr inline auto
	is_valid(char32_t const character) noexcept {
		return character <= MAX_CHAR_4 && !is_surrogate(character);
	}

	[[nodiscard]] static constexpr inline std::size_t
	get_encode_width(char32_t const character) noexcept {
		if (!is_valid(character)) {
			return 0;
		}

		if (character <= MAX_CHAR_1) {
			return 1;
		} else if (character > MAX_CHAR_1 && character <= MAX_CHAR_2) {
			return 2;
		} else if (character > MAX_CHAR_2 && character <= MAX_CHAR_3) {
			return 3;
		} else if (character > MAX_CHAR_3 && character <= MAX_CHAR_4) {
			return 4;
		} else {
			return 0;
		}
	}

	[[nodiscard]] static constexpr inline std::optional<CodepointInfo>
	get_info(char32_t const character) noexcept {
		if (!is_valid(character)) {
			return {};
		}

		return UNICODE_DATA[UNICODE_DATA_INDICES[character]];
	}
}
