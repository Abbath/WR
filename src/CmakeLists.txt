 list(APPEND WR_INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/creature.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/wolf.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/defs.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/rabbit.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/cell.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/field.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/coords.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/randomgenerator.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.hpp
 )
  
 list(APPEND WR_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/creature.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/wolf.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/rabbit.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cell.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/field.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/coords.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/randomgenerator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
 )
  
 # run uic to generate source
 COPPERSPICE_RESOURCES(
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
 )
  
 add_executable(WR
    ${WR_SOURCES}
 )
  
 target_include_directories(WR
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
 )
  
 target_link_libraries(WR
    CopperSpice::CsCore
    CopperSpice::CsGui
 )
  
 if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # disable console on windows
    target_link_libraries(WR -lnetapi32 -lmpr -mwindows)
 endif()
  
 install(TARGETS WR DESTINATION .)