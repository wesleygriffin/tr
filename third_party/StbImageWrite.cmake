if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/stb_image_write.h)
  file(DOWNLOAD https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
    ${CMAKE_CURRENT_BINARY_DIR}/stb_image_write.h)

  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/stb_image_write.c "#define STB_IMAGE_WRITE_IMPLEMENTATION
#include \"stb_image_write.h\"")
endif()

add_library(stb_image_write STATIC ${CMAKE_CURRENT_BINARY_DIR}/stb_image_write.c)
target_include_directories(stb_image_write PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(Stb::ImageWrite ALIAS stb_image_write)
