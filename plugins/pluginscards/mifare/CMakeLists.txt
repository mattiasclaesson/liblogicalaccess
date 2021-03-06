cmake_minimum_required(VERSION 2.6)
project(mifarecards)

if (WIN32)
	SET(VERSION_PRODUCTNAME_VALUE "mifarecards")
	add_definitions(-DVERSION_PRODUCTNAME_VALUE="${VERSION_PRODUCTNAME_VALUE}")
endif()

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE INCLUDE *.hpp)

add_library(
	mifarecards
	SHARED
	${SRCS}
	${INCLUDE}
	${resourcerc}
  )

SET_TARGET_PROPERTIES(mifarecards PROPERTIES VERSION ${LIBLOGICALACCESS_VERSION_STRING})

target_link_libraries(
	mifarecards
	${LIBLOGICALACCESS_LIBRARY}
)

install ( FILES ${INCLUDE} DESTINATION include/logicalaccess/plugins/cards/mifare )
install ( TARGETS mifarecards RUNTIME DESTINATION bin/${LIB_SUFFIX} ARCHIVE DESTINATION lib/${LIB_SUFFIX} LIBRARY DESTINATION lib/${LIB_SUFFIX} )