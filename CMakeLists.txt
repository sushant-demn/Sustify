cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MusicStreamingApp")

include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0)
FetchContent_MakeAvailable(webview)

set(SOURCE_FILES
    src/main.cpp
    src/file_system.cpp
)

# Add source to this project's executable.
add_executable (MusicStreamingApp "${SOURCE_FILES}")
#add_executable (MusicStreamingApp WIN32 "include/window.cpp" )

target_link_libraries(MusicStreamingApp PRIVATE webview::core)
target_include_directories(MusicStreamingApp PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(MusicStreamingApp PUBLIC "${PROJECT_SOURCE_DIR}/headers")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicStreamingApp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
