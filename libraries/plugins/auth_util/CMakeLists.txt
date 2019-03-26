file(GLOB HEADERS "include/surf/plugins/auth_util/*.hpp")

add_library( surf_auth_util
             ${HEADERS}
             auth_util_plugin.cpp
             auth_util_api.cpp
           )

target_link_libraries( surf_auth_util surf_app surf_chain surf_protocol fc )
target_include_directories( surf_auth_util
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
