project( Algebraic_kernel_d_Examples )

cmake_minimum_required(VERSION 3.1)


find_package(CGAL QUIET COMPONENTS Core)

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  find_package(MPFI QUIET)
endif()

if( CGAL_FOUND AND MPFI_FOUND)

  include( ${MPFI_USE_FILE} )
  include( CGAL_CreateSingleSourceCGALProgram )
  include( CGAL_VersionUtils )

  create_single_source_cgal_program( "Compare_1.cpp" )
  create_single_source_cgal_program( "Construct_algebraic_real_1.cpp" )
  create_single_source_cgal_program( "Isolate_1.cpp" )
  create_single_source_cgal_program( "Sign_at_1.cpp" )
  create_single_source_cgal_program( "Solve_1.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library and MPFI, and will not be compiled.")
  
endif()
