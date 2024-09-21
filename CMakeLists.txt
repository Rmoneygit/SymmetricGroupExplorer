cmake_minimum_required(VERSION 3.10)

project(SymmetricGroupExplorer)

find_package(imgui CONFIG REQUIRED)

# Specify where to download backend files (e.g., ${CMAKE_BINARY_DIR}/imgui_backends)
set(IMGUI_BACKENDS_DIR ${CMAKE_BINARY_DIR}/imgui_backends)

# Download Win32 backend
file(DOWNLOAD
    https://raw.githubusercontent.com/ocornut/imgui/master/backends/imgui_impl_win32.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp
)
file(DOWNLOAD
    https://raw.githubusercontent.com/ocornut/imgui/master/backends/imgui_impl_win32.h
    ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.h
)

# Download DirectX 11 backend
file(DOWNLOAD
    https://raw.githubusercontent.com/ocornut/imgui/master/backends/imgui_impl_dx12.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.cpp
)
file(DOWNLOAD
    https://raw.githubusercontent.com/ocornut/imgui/master/backends/imgui_impl_dx12.h
    ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.h
)

# Add the executable, including the backend files
add_executable(SymmetricGroupExplorer "SymmetricGroupExplorer_main.cpp"
                  ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp
                  ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.cpp)

target_link_libraries(SymmetricGroupExplorer PRIVATE imgui::imgui)

# Add include directories for ImGui backends
target_include_directories(SymmetricGroupExplorer PRIVATE
    ${IMGUI_BACKENDS_DIR}
)

# Link necessary Windows and DirectX libraries
target_link_libraries(SymmetricGroupExplorer PRIVATE d3d12 dxgi dxguid)

message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

