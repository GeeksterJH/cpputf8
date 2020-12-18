#pragma once

#include <string_view>

namespace cpputf8 {
	enum class CodepointCategory {
		LetterUppercase,
		LetterLowercase,
		LetterTitlecase,
		LetterModifier,
		LetterOther,

		MarkNonSpacing,
		MarkSpacingCombining,
		MarkEnclosing,

		NumberDecimalDigit,
		NumberLetter,
		NumberOther,

		SeparatorSpace,
		SeparatorLine,
		SeparatorParagraph,

		OtherControl,
		OtherFormat,
		OtherSurrogate,
		OtherPrivateUse,
		OtherNotAssigned,

		PunctuationConnector,
		PunctuationDash,
		PunctuationOpen,
		PunctuationClose,
		PunctuationInitialQuote,
		PunctuationFinalQuote,
		PunctuationOther,

		SymbolMath,
		SymbolCurrency,
		SymbolModifier,
		SymbolOther,
	};

	struct CodepointInfo {
		char32_t value;
		std::string_view name;
		CodepointCategory category;
	};
}
