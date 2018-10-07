if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  get_filename_component(bindir ${CMAKE_CXX_COMPILER} DIRECTORY)
  get_filename_component(libdir ${bindir}/../lib REALPATH)

  set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,-rpath,${libdir} -lc++")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  string(REGEX REPLACE "/W[0-4]+" "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
  string(REGEX REPLACE "/Zi" "" CMAKE_CXX_FLAGS_DEBUG_INIT "${CMAKE_CXX_FLAGS_DEBUG_INIT}")
endif()
