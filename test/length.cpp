#include "cpputf8_test.hpp"

#include <cpputf8.hpp>

int main() {
	ASSERT(cpputf8::length("Hello") == 5);
	ASSERT(cpputf8::length("\xD0\x92Hello") == 6);
	ASSERT(cpputf8::length("\xE2\x91\xA4Hello") == 6);
	ASSERT(cpputf8::length("\xF0\x9F\x98\x80Hello") == 6);

	return 0;
}
