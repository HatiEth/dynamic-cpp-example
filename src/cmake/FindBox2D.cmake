# default search dirs
SET(_box2d_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include")

# check environment variable
SET(_box2d_ENV_ROOT_DIR "$ENV{BOX2DDIR}")

IF(NOT BOX2D_ROOT_DIR AND _box2d_ENV_ROOT_DIR)
    SET(BOX2D_ROOT_DIR "${_box2d_ENV_ROOT_DIR}")
ENDIF(NOT BOX2D_ROOT_DIR AND _box2d_ENV_ROOT_DIR)

# put user specified location at beginning of search
IF(BOX2D_ROOT_DIR)
    SET(_box2d_HEADER_SEARCH_DIRS "${BOX2D_ROOT_DIR}"
                                  "${BOX2D_ROOT_DIR}/include"
                                   ${_box2d_HEADER_SEARCH_DIRS})
ENDIF(BOX2D_ROOT_DIR)

# locate header
FIND_PATH(BOX2D_INCLUDE_DIR "Box2D/Box2D.h"
    PATHS ${BOX2D_ROOT_DIR})
FIND_LIBRARY(BOX2D_LIBRARY Box2D PATHS ${BOX2D_ROOT_DIR} PATH_SUFFIXES lib lib64)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BOX2D DEFAULT_MSG BOX2D_LIBRARY
    BOX2D_INCLUDE_DIR)

IF(BOX2D_FOUND)
    SET(BOX2D_INCLUDE_DIRS "${BOX2D_INCLUDE_DIR}")

    MESSAGE(STATUS "BOX2D_LIBRARY = ${BOX2D_LIBRARY}")
    MESSAGE(STATUS "BOX2D_INCLUDE_DIR = ${BOX2D_INCLUDE_DIR}")
ENDIF(BOX2D_FOUND)