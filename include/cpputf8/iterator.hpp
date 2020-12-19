#pragma once

#include <string_view>
#include <tuple>

#include "cpputf8/codepoint.hpp"

namespace cpputf8 {
	class Iterator {
	private:
		std::string_view string;
		std::string_view::const_iterator string_iterator;

		std::pair<char32_t, std::size_t> codepoint = decode_first(c_str());

	public:
		constexpr Iterator(
			std::string_view const full_string,
			std::string_view::const_iterator iterator) noexcept
			: string{full_string}
			, string_iterator{iterator} {
		}

		[[nodiscard]] constexpr inline char const *c_str() const noexcept {
			if (string_iterator >= string.end()) {
				return "";
			} else {
				return &(*string_iterator);
			}
		}

		constexpr inline Iterator operator++() noexcept {
			if (string_iterator < string.end()) {
				string_iterator += codepoint.second;
				codepoint = decode_first(c_str());
			}

			return *this;
		}

		constexpr inline Iterator operator++(int const) noexcept {
			auto const result = *this;
			++(*this);

			return result;
		}

		constexpr inline Iterator
		operator+=(std::size_t const amount) noexcept {
			for (std::size_t i = 0; i < amount; ++i) {
				++(*this);
			}

			return *this;
		}

		constexpr inline Iterator operator--() noexcept {
			if (string_iterator > string.begin()) {
				string_iterator -= codepoint.second;
				codepoint = decode_first(c_str());
			}

			return *this;
		}

		constexpr inline Iterator operator--(int const) noexcept {
			auto const result = *this;
			--(*this);

			return result;
		}

		constexpr inline Iterator
		operator-=(std::size_t const amount) noexcept {
			for (std::size_t i = 0; i < amount; ++i) {
				--(*this);
			}

			return *this;
		}

		[[nodiscard]] constexpr inline auto const &operator*() const noexcept {
			return codepoint;
		}

		[[nodiscard]] constexpr inline auto const *operator->() const noexcept {
			return &codepoint;
		}

		[[nodiscard]] constexpr inline auto
		operator==(Iterator const &other) const noexcept {
			return string_iterator == other.string_iterator;
		}

		[[nodiscard]] constexpr inline auto
		operator!=(Iterator const &other) const noexcept {
			return !(*this == other);
		}
	};

	[[nodiscard]] static constexpr inline Iterator
	begin(std::string_view const string) noexcept {
		return Iterator{string, string.begin()};
	}

	[[nodiscard]] static constexpr inline Iterator
	end(std::string_view const string) noexcept {
		return Iterator{string, string.end()};
	}

	[[nodiscard]] static constexpr inline Iterator
	operator+(Iterator const &iterator, std::size_t const amount) noexcept {
		auto result = iterator;
		result += amount;

		return result;
	}

	[[nodiscard]] static constexpr inline Iterator
	operator-(Iterator const &iterator, std::size_t const amount) noexcept {
		auto result = iterator;
		result -= amount;

		return result;
	}
}
