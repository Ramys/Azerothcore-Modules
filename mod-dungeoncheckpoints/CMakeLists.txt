CU_SET_PATH("CMAKE_Dynamic_Resurrection_DIR" "${CMAKE_CURRENT_LIST_DIR}")

AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/DynamicResurrection.cpp")

AC_ADD_SCRIPT_LOADER("SC_Dynamic_Resurrection"      "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

message("-- Dynamic Resurrection CONFIGURED --")
