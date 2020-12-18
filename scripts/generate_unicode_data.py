import sys
import os
from typing import List

CMAKE_BINARY_DIR = sys.argv[1]
UNICODE_DATA_PATH = f"{CMAKE_BINARY_DIR}/assets/UnicodeData.txt"
OUTPUT_PATH = f"{CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp"

CATEGORIES = {
    "Lu": "LetterUppercase",
    "Ll": "LetterLowercase",
    "Lt": "LetterTitlecase",
    "Lm": "LetterModifier",
    "Lo": "LetterOther",

    "Mn": "MarkNonSpacing",
    "Mc": "MarkSpacingCombining",
    "Me": "MarkEnclosing",

    "Nd": "NumberDecimalDigit",
    "Nl": "NumberLetter",
    "No": "NumberOther",

    "Zs": "SeparatorSpace",
    "Zl": "SeparatorLine",
    "Zp": "SeparatorParagraph",

    "Cc": "OtherControl",
    "Cf": "OtherFormat",
    "Cs": "OtherSurrogate",
    "Co": "OtherPrivateUse",
    "Cn": "OtherNotAssigned",

    "Pc": "PunctuationConnector",
    "Pd": "PunctuationDash",
    "Ps": "PunctuationOpen",
    "Pe": "PunctuationClose",
    "Pi": "PunctuationInitialQuote",
    "Pf": "PunctuationFinalQuote",
    "Po": "PunctuationOther",

    "Sm": "SymbolMath",
    "Sc": "SymbolCurrency",
    "Sk": "SymbolModifier",
    "So": "SymbolOther",
}


class CodepointInfo:
    value: str
    name: str
    category: str

    def __init__(self, value: str, name: str, category: str):
        self.value = value
        self.name = name
        self.category = CATEGORIES[category]

    def __str__(self) -> str:
        return f"CodepointInfo{{0x{self.value}, \"{self.name}\", CodepointCategory::{self.category}}}"

    def numeric_value(self) -> int:
        return int(self.value, 16)


def read_codepoints() -> List[CodepointInfo]:
    result: List[CodepointInfo] = []

    with open(UNICODE_DATA_PATH, "r") as unicode_data_file:
        unicode_data = unicode_data_file.readlines()

        for line in unicode_data:
            parts = line.split(";")

            value = parts[0]
            name = parts[1]
            category = parts[2]

            result.append(CodepointInfo(value, name, category))

    return result


def generate_file():
    codepoints = read_codepoints()
    biggest_codepoint = 0

    for codepoint in codepoints:
        if codepoint.numeric_value() > biggest_codepoint:
            biggest_codepoint = codepoint.numeric_value()

    codepoint_indices = [0] * (biggest_codepoint + 1)

    index = 0
    for codepoint in codepoints:
        codepoint_indices[codepoint.numeric_value()] = index
        index += 1

    if not os.path.exists(f"{CMAKE_BINARY_DIR}/include"):
        os.mkdir(f"{CMAKE_BINARY_DIR}/include")

    if not os.path.exists(f"{CMAKE_BINARY_DIR}/include/cpputf8"):
        os.mkdir(f"{CMAKE_BINARY_DIR}/include/cpputf8")

    with open(OUTPUT_PATH, "w") as output_file:
        output_file.write("#pragma once\n")
        output_file.write("\n")
        output_file.write("#include \"cpputf8/codepoint_info.hpp\"\n")
        output_file.write("\n")
        output_file.write("namespace cpputf8 {\n")
        output_file.write(
            f"\tstatic constexpr CodepointInfo UNICODE_DATA[{len(codepoints)}] = {{\n")

        for codepoint in codepoints:
            output_file.write(f"\t\t{str(codepoint)},\n")

        output_file.write("\t};\n")
        output_file.write("\n")
        output_file.write(
            f"\tstatic constexpr uint32_t UNICODE_DATA_INDICES[{len(codepoint_indices)}] = {{\n")

        for index in codepoint_indices:
            output_file.write(f"\t\t{index},\n")

        output_file.write("\t};\n")
        output_file.write("}\n")


generate_file()
