cmake_minimum_required (VERSION 3.10)

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
    src/window.cpp
    src/audio.cpp
    src/file_system.cpp
    src/queue.cpp
)


add_executable (MusicStreamingApp WIN32 "${SOURCE_FILES}")



target_link_libraries(MusicStreamingApp PRIVATE webview::core)
target_include_directories(MusicStreamingApp PRIVATE "C:/vcpkg/installed/x64-windows/include")
target_link_libraries(MusicStreamingApp PRIVATE "C:/vcpkg/installed/x64-windows/lib/tag.lib")
target_include_directories(MusicStreamingApp PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(MusicStreamingApp PUBLIC "${PROJECT_SOURCE_DIR}/headers")

add_custom_command(TARGET MusicStreamingApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/vcpkg/installed/x64-windows/bin/tag.dll"
    $<TARGET_FILE_DIR:MusicStreamingApp>
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicStreamingApp PROPERTY CXX_STANDARD 20)
endif()


