cmake_minimum_required(VERSION 3.10)

project(SymmetricGroupExplorer)

find_package(imgui CONFIG REQUIRED)

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

# Add the executable, including the backend files
add_executable(SymmetricGroupExplorer "SymmetricGroupExplorer_main.cpp"
                  ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp
                  ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.cpp  
                  "SYMUI_input_processing.cpp" 
                  "SYM_symmetric_group.cpp"
                  "SYMUI_windows.cpp"
              )

target_link_libraries(SymmetricGroupExplorer PRIVATE imgui::imgui)

# Add include directories for ImGui backends
target_include_directories(SymmetricGroupExplorer PRIVATE
    ${IMGUI_BACKENDS_DIR}
)

# Link necessary Windows and DirectX libraries
target_link_libraries(SymmetricGroupExplorer PRIVATE d3d12 dxgi dxguid)

message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

