set ("${PROJECT}_VERSION_MAJ" 0)
set ("${PROJECT}_VERSION_MIN" 1)
set ("${PROJECT}_VERSION_A" 1)
set ("${PROJECT}_VERSION_B" 1)
set ("${PROJECT}_VERSION" ${${PROJECT}_VERSION_MAJ}0${${PROJECT}_VERSION_MIN}0${${PROJECT}_VERSION_A}0${${PROJECT}_VERSION_B})

message(STATUS ${${PROJECT}_VERSION})

# основной файл программы
set (MAIN_SOURCES source.cpp )

# непубличные пары исходников
set (PRIVATE_CLASSES core )

# файлы только заголовочные, у которых нет пары-исходника
SET (HEADERS_ONLY types common )

# публичные исходники
set (PUBLIC_CLASSES)

# используемые в программе библиотеки
set (ADDITIONAL_LIBRARIES stdc++ pthread )

set (PUBLIC_HEADERS)
set (SOURCES)

if ( CMAKE_COMPILER_IS_GNUCXX )
		message ( STATUS "GNU compuler")
    set(MY_CXX_FLAGS  "-Wall -fmessage-length=0 -v")
    set(CMAKE_CXX_FLAGS "-O0 -std=c++11 ${MY_CXX_FLAGS}")
    # я отключил настройку разных флагов для релиза и отладки. Пока что не нужно.
    #set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else ()
    message (FATAL_ERROR ${ERR_NO_UNIX})
endif ()


foreach (class ${PRIVATE_CLASSES})
    LIST (APPEND SOURCES ${class}.cpp)
    LIST (APPEND HEADERS ${class}.hpp)
endforeach ()

foreach (class ${HEADERS_ONLY})
    LIST (APPEND HEADERS ${class}.hpp)
endforeach ()
    
foreach (class ${PUBLIC_CLASSES})
    LIST (APPEND SOURCES ${class}.cpp)
    LIST (APPEND HEADERS ../include/${PROJECT}/${class}.hpp)
    LIST (APPEND PUBLIC_HEADERS ../include/${PROJECT}/${class}.hpp)
endforeach ()

add_executable (${PROJECT} ${MAIN_SOURCES} ${SOURCES} )

target_link_libraries (${PROJECT} ${ADDITIONAL_LIBRARIES})

set_target_properties(${PROJECT} PROPERTIES VERSION "${${PROJECT}_VERSION}" SOVERSION "0")

INSTALL (
    TARGETS
    ${PROJECT}
    DESTINATION
    lib${LIB_SUFFIX}
)

INSTALL (
    FILES
    ${PUBLIC_HEADERS}
    DESTINATION
    include/${PROJECT}
)

