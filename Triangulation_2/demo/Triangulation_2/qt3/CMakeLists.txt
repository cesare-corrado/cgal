# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( qt3_demo )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

find_package(CGAL QUIET COMPONENTS Core Qt3 )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )
  
  include( CGAL_CreateSingleSourceCGALProgram )

  find_package(Qt3-patched QUIET )
  # FindQt3-patched.cmake is FindQt3.cmake patched by CGAL developers, so
  # that it can be used together with FindQt4: all its variables are prefixed
  # by "QT3_" instead of "QT_".
  
  if(CGAL_Qt3_FOUND AND QT3_FOUND)
  
    include( Qt3Macros-patched )
    qt3_automoc(  constrained.cpp constrained_delaunay_triangulation_2.cpp constrained_delaunay_triangulation_2_toolbar.cpp constrained_delaunay_triangulation_2_toolbar_layers.cpp delaunay_triangulation_2.cpp delaunay_triangulation_2_toolbar.cpp delaunay_triangulation_2_toolbar_layers.cpp regular_triangulation_2.cpp regular_triangulation_2_toolbar.cpp regular_triangulation_2_toolbar_layers.cpp triangulation_2_edit_vertex.cpp )

    # Make sure the compiler can find generated .moc files
    include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
  
    include_directories( ${QT3_INCLUDE_DIR} )

    create_single_source_cgal_program(
      delaunay_triangulation_2.cpp
      triangulation_2_edit_vertex.cpp 
      delaunay_triangulation_2_toolbar.cpp 
      delaunay_triangulation_2_toolbar_layers.cpp)
    

    create_single_source_cgal_program(
      regular_triangulation_2.cpp
      triangulation_2_edit_vertex.cpp
      regular_triangulation_2_toolbar.cpp
      regular_triangulation_2_toolbar_layers.cpp)
    
    create_single_source_cgal_program(
      constrained_delaunay_triangulation_2.cpp 
      constrained_delaunay_triangulation_2_toolbar.cpp 
      constrained_delaunay_triangulation_2_toolbar_layers.cpp)
              
    create_single_source_cgal_program(constrained.cpp)

  else()
  
    message(STATUS "NOTICE: This demo requires Qt3 and the CGAL Qt3 library, and will not be compiled.")
  
  endif()
  
else()
  
    message(STATUS "NOTICE: This demo requires the CGAL library, and will not be compiled.")
  
endif()

