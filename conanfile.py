from conans import ConanFile, CMake


class CppUtf8Conan(ConanFile):
    name = "cpputf8"
    version = "0.1.0"
    url = "https://github.com/GeeksterJH/cpputf8"
    description = "A C++17 library for working with UTF-8 encoded text"

    no_copy_sources = True
    exports_sources = [
        "include/*",
        "CMakeLists.txt",
        "cmake/*",
        "build/include/*",
        "scripts/*"
    ]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
        self.copy("*.hpp", src="build/include", dst="include")

    def package_id(self):
        self.info.header_only()
