file(GLOB HEADERS "include/surf/plugins/raw_block/*.hpp")

add_library( surf_raw_block
             ${HEADERS}
             raw_block_plugin.cpp
             raw_block_api.cpp
           )

target_link_libraries( surf_raw_block surf_app surf_chain surf_protocol fc )
target_include_directories( surf_raw_block
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
