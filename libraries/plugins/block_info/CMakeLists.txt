file(GLOB HEADERS "include/surf/plugins/block_info/*.hpp")

add_library( surf_block_info
             ${HEADERS}
             block_info_plugin.cpp
             block_info_api.cpp
           )

target_link_libraries( surf_block_info surf_app surf_chain surf_protocol fc )
target_include_directories( surf_block_info
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
