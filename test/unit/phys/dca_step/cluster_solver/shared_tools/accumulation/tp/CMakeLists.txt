# test/unit/phys/dca_step/cluster_solver/shared_tools/tp

dca_add_gtest(hdf5_g4_file_io_test
  FAST
  GTEST_MAIN
  INCLUDE_DIRS ${DCA_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}
  LIBS     ${DCA_LIBS}
  )

if (DCA_HAVE_ADIOS2)
  dca_add_gtest(adios2_g4_file_io_test
    FAST
    GTEST_MAIN
    INCLUDE_DIRS ${DCA_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}
    LIBS     ${DCA_LIBS}
    )
endif()

dca_add_gtest(tp_accumulator_test
  FAST
  GTEST_MAIN
  INCLUDE_DIRS ${DCA_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}
  LIBS     ${DCA_LIBS}
  )

dca_add_gtest(tp_accumulator_singleband_test
  FAST
  GTEST_MAIN
  INCLUDE_DIRS ${DCA_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}
  LIBS     ${DCA_LIBS}
  )

set(TPACC_PARTICLE_HOLE_LIBS cuda_utils cluster_domains time_and_frequency_domains quantum_domains timer json random
  enumerations dca_algorithms parallel_stdthread parallel_util ${LAPACK_LIBRARIES})

if (DCA_HAVE_ADIOS2)
  set(TPACC_PARTICLE_HOLE_LIBS dca_adios2 ${TPACC_PARTICLE_HOLE_LIBS})
endif()
  
dca_add_gtest(tp_accumulator_particle_hole_test
  FAST
  CUDA
  GTEST_MAIN
  INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${FFTW_INCLUDE_DIR} ${HDF5_INCLUDE_DIR}
  LIBS function ${TPACC_PARTICLE_HOLE_LIBS})

dca_add_gtest(tp_accumulator_gpu_test
  FAST
  CUDA
  GTEST_MAIN
  INCLUDE_DIRS ${DCA_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}
  LIBS     ${DCA_LIBS}
  )

dca_add_gtest(tp_accumulator_singleband_gpu_test
  FAST
  CUDA
  GTEST_MAIN
  INCLUDE_DIRS ${DCA_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}
  LIBS     ${DCA_LIBS}
  )

add_subdirectory(ndft)
