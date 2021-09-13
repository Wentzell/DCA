################################################################################
# Author: Urs R. Haehner (haehneru@itp.phys.ethz.ch)
#
# Checks for external libraries and creates a global lists of them and the corresponding include
# paths.
# We explicitely search for static libraries because compute nodes cannot load shared libraries from
# e.g. the project directory.

set(DCA_EXTERNAL_LIBS "" CACHE INTERNAL "")
set(DCA_EXTERNAL_INCLUDE_DIRS "" CACHE INTERNAL "")

## Make sure FindXXX.cmake modules are found in current dir
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Lapack
if (NOT DCA_HAVE_LAPACK)
  find_package(LAPACK REQUIRED)
endif()

mark_as_advanced(LAPACK_LIBRARIES)
list(APPEND DCA_EXTERNAL_LIBS ${LAPACK_LIBRARIES})

################################################################################
# HDF5
find_package(HDF5 REQUIRED COMPONENTS C CXX)
list(APPEND DCA_EXTERNAL_LIBS HDF5::HDF5)

################################################################################
# FFTW
find_package(FFTW REQUIRED)
list(APPEND DCA_EXTERNAL_LIBS fftw)

################################################################################
# Simplex GM Rule
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/simplex_gm_rule)
# list(APPEND DCA_EXTERNAL_LIBS ${SIMPLEX_GM_RULE_LIBRARY})
# list(APPEND DCA_EXTERNAL_INCLUDE_DIRS ${SIMPLEX_GM_RULE_INCLUDE_DIR})

################################################################################
# Gnuplot
list(APPEND DCA_EXTERNAL_LIBS ${GNUPLOT_INTERFACE_LIBRARY})
list(APPEND DCA_EXTERNAL_INCLUDE_DIRS ${GNUPLOT_INTERFACE_INCLUDE_DIR})

# message("DCA_EXTERNAL_LIBS = ${DCA_EXTERNAL_LIBS}")
# message("DCA_EXTERNAL_INCLUDE_DIRS = ${DCA_EXTERNAL_INCLUDE_DIRS}")
