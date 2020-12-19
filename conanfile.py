from conans import ConanFile, CMake


class CppUtf8Conan(ConanFile):
    name = "cpputf8"
    version = "0.1.0"

    exports_sources = [
        "include/*",
        "CMakeLists.txt",
        "cmake/*",
        "test/*",
        "build/include/*",
        "scripts/*"
    ]

    no_copy_sources = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
        self.copy("*.hpp", src="build/include", dst="include")

    def package_id(self):
        self.info.header_only()
