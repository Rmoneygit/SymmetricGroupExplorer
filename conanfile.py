from conan import ConanFile
from conan.tools.cmake import CMakeToolchain
from conan.tools.cmake import cmake_layout
import os

class SymmetricGroupExplorerConan(ConanFile):
    name = "SymmetricGroupExplorer"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    # Specify dependencies here
    requires = (
        "imgui/1.91.8",
        "cpptrace/1.0.4",
        "winflexbison/2.5.25"
    )

    def toolchain(self):
        tc = CMakeToolchain(self)
        winflexbison = self.dependencies["winflexbison"]
        bin_dir = winflexbison.cpp_info.bindirs[0]

        flexJoinedPath = os.path.join(bin_dir, "win_flex.exe")
        print("Setting FLEX_EXECUTABLE=" + flexJoinedPath)
        tc.cache_variables["FLEX_EXECUTABLE"] = flexJoinedPath

        bisonJoinedPath = os.path.join(bin_dir, "win_bison.exe")
        print("Setting FLEX_EXECUTABLE=" + bisonJoinedPath)
        tc.cache_variables["BISON_EXECUTABLE"] = bisonJoinedPath

        return tc

    def layout(self):
        cmake_layout(self)
        #self.folders.generators = "."
        print("Build folder: " + self.folders.build)
        print("Generators folder: " + self.folders.generators)
