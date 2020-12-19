from conans import ConanFile, CMake


class CppUtf8Conan(ConanFile):
    name = "cpputf8"
    version = "0.1.0"

    exports_sources = "include/*", "CMakeLists.txt", "cmake/*", "test/*", "build/include/*"
    no_copy_sources = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()

    def package(self):
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="build/include")

    def package_id(self):
        self.info.header_only()
