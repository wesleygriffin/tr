find_package(TBB REQUIRED)

add_executable(tr tr.cc)
target_compile_definitions(tr PRIVATE FMT_HEADER_ONLY)
target_include_directories(tr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tr Fmt::Fmt Stb::ImageWrite TBB::tbb)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

target_compile_options(tr
  PRIVATE
    -Wall -Werror -Wnon-virtual-dtor -Wsuggest-final-types
    -mavx2
    $<$<CONFIG:Debug>:-g -Og>
    $<$<CONFIG:Release>:-O2>
)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

# /wd4201: nameless struct/union

target_compile_definitions(tr
  PRIVATE
    _USE_MATH_DEFINES
    _CRT_SECURE_NO_WARNINGS
    _ENABLE_EXTENDED_ALIGNED_STORAGE
    _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING 
)

target_compile_options(tr
  PRIVATE
    /W4 /WX /wd4201
    /arch:AVX2
    $<$<CONFIG:Debug>:/ZI /Od /Gm>
    $<$<CONFIG:Release>:/O2 /GL /Gw>
)

file(GLOB _tbb_dlls ${TBB_BINARY_DIR}/*.dll)
foreach(dll ${_tbb_dlls})
  add_custom_command(TARGET tr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${dll} $<TARGET_FILE_DIR:tr>)
endforeach()

endif()
