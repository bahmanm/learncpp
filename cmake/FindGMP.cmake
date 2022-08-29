if(NOT GMP_FIND_VERSION)
  if(NOT GMP_FIND_VERSION_MAJOR)
    set(GMP_FIND_VERSION_MAJOR 6)
  endif()
  if(NOT GMP_FIND_VERSION_MINOR)
    set(GMP_FIND_VERSION_MINOR 2)
  endif()
  if(NOT GMP_FIND_VERSION_PATCH)
    set(GMP_FIND_VERSION_PATCH 0)
  endif()
  set(GMP_FIND_VERSION
    "${GMP_FIND_VERSION_MAJOR}.${GMP_FIND_VERSION_MINOR}.${GMP_FIND_VERSION_PATCH}")
endif()

find_path(GMP_INCLUDE_DIRS
  NAMES gmp.h
  PATHS $ENV{GMPDIR} ${INCLUDE_INSTALL_DIR})

find_library(GMP_LIBRARIES
  gmp
  PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})

find_library(GMPXX_LIBRARIES
  gmpxx
  PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})

if(GMP_INCLUDE_DIRS AND GMP_LIBRARIES AND GMPXX_LIBRARIES)
  file(WRITE ${PROJECT_BINARY_DIR}/gmp-version-check.cpp ""
  "#include <gmpxx.h>\n"
  "\n"
  "#define GMP_FIND_VERSION_MAJOR ${GMP_FIND_VERSION_MAJOR}\n"
  "#define GMP_FIND_VERSION_MINOR ${GMP_FIND_VERSION_MINOR}\n"
  "#define GMP_FIND_VERSION_PATCH ${GMP_FIND_VERSION_PATCH}\n"
  "\n"
  "#if __GNU_MP_VERSION < GMP_FIND_VERSION_MAJOR\n"
  "#error insufficient GMP major version\n"
  "#elif __GNU_MP_VERSION == GMP_FIND_VERSION_MAJOR\n"
  "#if __GNU_MP_VERSION_MINOR < GMP_FIND_VERSION_MINOR\n"
  "#error insufficient GMP minor version\n"
  "#elif __GNU_MP_VERSION_MINOR == GMP_FIND_VERSION_MINOR\n"
  "#if __GNU_MP_VERSION_PATCH < GMP_FIND_VERSION_PATCH\n"
  "#error insufficient GMP patch version\n"
  "#endif\n"
  "#endif\n"
  "#endif\n"
  "\n"
  "int main(int argc, char** argv) { return 0; }\n")

  try_compile(GMP_VERSION_OK
          "${PROJECT_BINARY_DIR}"
          "${PROJECT_BINARY_DIR}/gmp-version-check.cpp"
          CMAKE_FLAGS "-DINCLUDE_DIRECTORIES=${GMP_INCLUDE_DIRS}")
endif()

if(NOT GMP_VERSION_OK)
  message(STATUS "No sufficient GMP version detected")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG
  GMP_INCLUDE_DIRS
  GMP_LIBRARIES
  GMPXX_LIBRARIES
  GMP_VERSION_OK)
mark_as_advanced(
  GMP_INCLUDE_DIRS
  GMP_LIBRARIES
  GMPXX_LIBRARIES)
