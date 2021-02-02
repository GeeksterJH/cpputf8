function(download_unicode_data)
	set(UNICODE_DATA_PATH "${CMAKE_BINARY_DIR}/assets/UnicodeData.txt")

	if(NOT EXISTS "${UNICODE_DATA_PATH}")
		message("Downloading UnicodeData.txt...")

		file(
			DOWNLOAD
			"https://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt"
			"${UNICODE_DATA_PATH}")
	endif()
endfunction()
