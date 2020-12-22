function(download_unicode_data)
	set(UNICODE_DATA_PATH "${CMAKE_BINARY_DIR}/assets/UnicodeData.txt")

	if(NOT EXISTS "${UNICODE_DATA_PATH}")
		message("Downloading UnicodeData.txt...")

		file(
			DOWNLOAD
			"https://www.unicode.org/Public/14.0.0/ucd/UnicodeData-14.0.0d3.txt"
			"${UNICODE_DATA_PATH}")
	endif()
endfunction()
