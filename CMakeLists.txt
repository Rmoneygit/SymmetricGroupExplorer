cmake_minimum_required(VERSION 3.31.0)

project(SymmetricGroupExplorer)

set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/share)

find_package(imgui CONFIG REQUIRED)
find_package(cpptrace CONFIG REQUIRED)
find_package(flex REQUIRED)
#find_package(bison REQUIRED)

# Set the specific ImGui version to use
set(IMGUI_VERSION_TAG "v1.91.9")

# Specify where to download backend files (e.g., ${CMAKE_BINARY_DIR}/imgui_backends)
set(IMGUI_BACKENDS_DIR ${CMAKE_BINARY_DIR}/imgui_backends)

file(MAKE_DIRECTORY ${IMGUI_BACKENDS_DIR})

# Helper macro to download if file is missing
macro(download_imgui_backend_file filename)
    set(url "https://raw.githubusercontent.com/ocornut/imgui/${IMGUI_VERSION_TAG}/backends/${filename}")
    set(dest "${IMGUI_BACKENDS_DIR}/${filename}")
    if(NOT EXISTS ${dest})
        message(STATUS "Downloading ImGui backend file: ${filename}")
        file(DOWNLOAD ${url} ${dest} SHOW_PROGRESS STATUS status LOG log)
        list(GET status 0 status_code)
        if(NOT status_code EQUAL 0)
            message(FATAL_ERROR "Failed to download ${filename}: ${log}")
        endif()
    endif()
endmacro()

# Download required backend files
download_imgui_backend_file("imgui_impl_win32.cpp")
download_imgui_backend_file("imgui_impl_win32.h")
download_imgui_backend_file("imgui_impl_dx12.cpp")
download_imgui_backend_file("imgui_impl_dx12.h")

flex_target(MyScanner cycle_notation.l ${CMAKE_CURRENT_BINARY_DIR}/cycle_notation_lexer.cpp)
#bison_target(MyParser parser.y parser.cpp)
#add_flex_bison_dependency(MyScanner MyParser)

# Add the executable, including the backend files
add_executable(SymmetricGroupExplorer "SymmetricGroupExplorer_main.cpp"
                  ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp
                  ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.cpp
                  "Sym_errors.cpp"
                  "Sym_symmetric_group.cpp"
                  "SymUI_input_processing.cpp" 
                  "SymUI_windows.cpp"
                  "SymUI_error_presentation.cpp"
                  #${BISON_MyParser_OUTPUTS} 
                  ${FLEX_MyScanner_OUTPUTS}
              )

target_link_libraries(SymmetricGroupExplorer PRIVATE imgui::imgui cpptrace::cpptrace)

# Add include directories for ImGui backends
target_include_directories(SymmetricGroupExplorer PRIVATE
    ${IMGUI_BACKENDS_DIR}
)

# Link necessary Windows and DirectX libraries
target_link_libraries(SymmetricGroupExplorer PRIVATE d3d12 dxgi dxguid)

message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# Copy the cpptrace.dll on windows to the same directory as the executable for your_target.
# Not required if static linking.
if(WIN32)
  add_custom_command(
    TARGET SymmetricGroupExplorer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:cpptrace::cpptrace>
    $<TARGET_FILE_DIR:SymmetricGroupExplorer>
  )
endif()