cmake_minimum_required(VERSION 3.2.3)
project(ruby_wrapper CXX)

#=============================================================================
# All done editing
SET(ruby_wrapper_VERSION "0.0")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
SET(CMAKE_CXX_FLAGS "-O2 -std=c++11")

FIND_PACKAGE(GSL)
FIND_PACKAGE(myclass)

IF(NOT myclass_FOUND)
  MESSAGE(FATAL_ERROR "Please specify correct myclass_ROOT_DIR")
ENDIF()

SET(INCLUDE_DIRS ${GSL_INCLUDE_DIRS} ${lin_INCLUDE_DIRS})
SET(LIBRARIES ${GSL_LIBRARIES} ${lin_LIBRARY})

SET(INCLUDE_FLAGS_STR "")
SET(INCLUDE_FLAGS "")
FOREACH(inc ${INCLUDE_DIRS})
  SET(INCLUDE_FLAGS ${INCLUDE_FLAGS} -I${inc})
  SET(INCLUDE_FLAGS_STR "${INCLUDE_FLAGS_STR} -I${inc}")
ENDFOREACH()

FUNCTION(GENERATE_MAKEFILE dir)
  SET(EXTSTRING "#!/bin/env ruby\nrequire 'mkmf'\n\n$CPPFLAGS += ' ${CMAKE_CXX_FLAGS}${INCLUDE_FLAGS_STR}'\n$libs='")

  SET(RPATHS "")
  FOREACH(lib ${LIBRARIES})
    SET(EXTSTRING "${EXTSTRING} ${lib}")
    GET_FILENAME_COMPONENT(rdir ${lib} DIRECTORY)
    LIST(FIND RPATHS ${rdir} index)
    IF(index EQUAL -1)
      SET(RPATHS ${RPATHS} ${rdir})
    ENDIF()
  ENDFOREACH()
  SET(EXTSTRING "${EXTSTRING} -Wl,-rpath,")
  FOREACH(rpath ${RPATHS})
    SET(EXTSTRING "${EXTSTRING}${rpath}:")
  ENDFOREACH()

  SET(EXTSTRING "${EXTSTRING}'\n\ncreate_makefile('${dir}')\n")
  FILE(WRITE ${dir}/extconf.rb ${EXTSTRING})

  MESSAGE(STATUS "Generating Makefile in ${dir}")
  EXECUTE_PROCESS(COMMAND ruby extconf.rb
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${dir}
    OUTPUT_FILE Makefile)
ENDFUNCTION()

FOREACH(dir Chisq LibLin)
  GENERATE_MAKEFILE(${dir})

  ADD_CUSTOM_TARGET(${dir}_wrapcxx
    COMMAND swig ${INCLUDE_FLAGS} -c++ -ruby ${dir}.i
    #DEPENDS ${CMAKE_SOURCE_DIR}/${dir}/${dir}.cc ${CMAKE_SOURCE_DIR}/${dir}/${dir}.h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${dir}
    SOURCES ${CMAKE_SOURCE_DIR}/${dir}/${dir}.i)

  ADD_CUSTOM_TARGET(${dir}
    COMMAND make
    DEPENDS ${dir}_wrapcxx
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${dir}
    SOURCES ${CMAKE_SOURCE_DIR}/${dir}/${dir}_wrap.cxx)
ENDFOREACH()
