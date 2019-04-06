CollectIncludeDirectories(
  ${CMAKE_MOD_ELUNA_ENGINE_DIR}
  PUBLIC_INCLUDES)

target_include_directories(game-interface
  INTERFACE
    ${PUBLIC_INCLUDES})

add_dependencies(game lualib)

target_link_libraries(game
  PUBLIC
    lualib)

if( WIN32 )
  if ( MSVC )
    add_custom_command(TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/extensions/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_MOD_ELUNA_ENGINE_DIR}/LuaEngine/extensions" "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/lua_scripts/extensions/"
  )
  elseif ( MINGW )
    add_custom_command(TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/lua_scripts/extensions/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_MOD_ELUNA_ENGINE_DIR}/LuaEngine/extensions" "${CMAKE_BINARY_DIR}/bin/lua_scripts/extensions/"
  )
  endif()
endif()

install(DIRECTORY "${CMAKE_MOD_ELUNA_ENGINE_DIR}/LuaEngine/extensions" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/lua_scripts/")
