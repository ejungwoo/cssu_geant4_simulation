cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PROJECT_G4EJ)

#----------------------------------------------------------------------------

set(useROOT false)
set(G4EJ_SOURCE_DIRECTORIES source)
set(G4EJ_EXECUTABLES g4run)
set(G4EJ_SCRIPTS)# vis.mac sim_par.mac)

#----------------------------------------------------------------------------

option(WITH_GEANT4_UIVIS "Build run with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

if(useROOT)
  list(APPEND G4EJ_SOURCE_DIRECTORIES)
  list(APPEND G4EJ_EXECUTABLES)
endif(useROOT)

set(G4EJ_SOURCES_DIRECTORIES_FULL)
foreach(_directory ${G4EJ_SOURCE_DIRECTORIES})
  list(APPEND G4EJ_SOURCE_DIRECTORIES_FULL ${PROJECT_SOURCE_DIR}/${_directory})
endforeach(_directory)

set(G4EJ_SOURCES)
foreach(_directory ${G4EJ_SOURCE_DIRECTORIES_FULL})
  list(APPEND G4EJ_SOURCES ${_directory}/*.cc)
  list(APPEND G4EJ_SOURCES ${_directory}/*.cpp)
endforeach(_directory)

set(G4EJ_HEADERS)
foreach(_directory ${G4EJ_SOURCE_DIRECTORIES_FULL})
  list(APPEND G4EJ_HEADERS ${_directory}/*.hh)
  list(APPEND G4EJ_HEADERS ${_directory}/*.h)
endforeach(_directory)

include(${Geant4_USE_FILE})
include_directories(${G4EJ_SOURCE_DIRECTORIES_FULL})

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT)

foreach(_source ${G4EJ_SOURCES})
    message(STATUS ${_source})
endforeach(_source)

file(GLOB sources ${G4EJ_SOURCES})
file(GLOB headers ${G4EJ_HEADERS})

foreach(_executable ${G4EJ_EXECUTABLES})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
  add_executable(${_executable} ${_executable}.cc ${sources} ${headers})
if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
endif(useROOT)
  target_link_libraries(${_executable} ${Geant4_LIBRARIES})
endforeach(_executable)

foreach(_script ${G4EJ_SCRIPTS})
  configure_file( ${PROJECT_SOURCE_DIR}/${_script} ${PROJECT_BINARY_DIR}/${_script} COPYONLY)
endforeach(_script)

add_custom_target(PROJECT_G4EJ DEPENDS ${G4EJ_EXECUTABLES})

foreach(_executable ${G4EJ_EXECUTABLES})
  install(TARGETS ${_executable} DESTINATION bin)
endforeach(_executable)
