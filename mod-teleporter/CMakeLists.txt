CU_SET_PATH("CMAKE_MOD_TELEPORTER_DIR" "${CMAKE_CURRENT_LIST_DIR}")

AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/npc_teleport.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/sc_npc_teleport.h")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/sc_npc_teleport.cpp")

AC_ADD_SCRIPT_LOADER("Teleporter"      "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

CU_ADD_HOOK(AFTER_WORLDSERVER_CMAKE "${CMAKE_CURRENT_LIST_DIR}/cmake_install.cmake")

message("-- Teleporter CONFIGURED --")
