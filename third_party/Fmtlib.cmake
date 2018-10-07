FetchContent_Declare(fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG 5.2.1
  GIT_SHALLOW TRUE UPDATE_DISCONNECTED TRUE
)

FetchContent_GetProperties(fmtlib)
if(NOT fmtlib_POPULATED)
  FetchContent_Populate(fmtlib)

  add_library(fmt INTERFACE)
  set_target_properties(fmt PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${fmtlib_SOURCE_DIR}/include
  )

  add_library(Fmt::Fmt ALIAS fmt)
endif()
