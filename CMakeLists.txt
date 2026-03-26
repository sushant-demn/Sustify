cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Sustify")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    src/bindings.cpp
)

file(GLOB_RECURSE UI_FILES CONFIGURE_DEPENDS "gui/*")

add_executable(Sustify WIN32 "${SOURCE_FILES}" resources.rc "${UI_FILES}")

target_link_libraries(Sustify PRIVATE webview::core)
target_include_directories(Sustify PRIVATE "C:/vcpkg/installed/x64-windows/include")
target_link_libraries(Sustify PRIVATE "C:/vcpkg/installed/x64-windows/lib/tag.lib")
target_include_directories(Sustify PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(Sustify PUBLIC "${PROJECT_SOURCE_DIR}/headers")

# copy everything needed after build
add_custom_command(TARGET Sustify POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/gui"
        "$<TARGET_FILE_DIR:Sustify>/gui"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/vcpkg/installed/x64-windows/bin/tag.dll"
        "$<TARGET_FILE_DIR:Sustify>/tag.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/vcpkg/installed/x64-windows/bin/zlib1.dll"
        "$<TARGET_FILE_DIR:Sustify>/zlib1.dll"
    COMMENT "Copying runtime dependencies..."
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Sustify PROPERTY CXX_STANDARD 20)
endif()