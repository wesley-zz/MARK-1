AUX_SOURCE_DIRECTORY(. SRC_LIST)

INCLUDE_DIRECTORIES(../include
                    ./module/logger)

ADD_SUBDIRECTORY(module/logger)

ADD_EXECUTABLE(main ${SRC_LIST} module/logger/logger.c)

SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

FIND_PACKAGE(Threads)

TARGET_LINK_LIBRARIES(main ${CMAKE_THREAD_LIBS_INIT})