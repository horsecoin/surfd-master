file(GLOB HEADERS "include/surf/blockchain_statistics/*.hpp")

add_library( surf_blockchain_statistics
             blockchain_statistics_plugin.cpp
             blockchain_statistics_api.cpp
           )

target_link_libraries( surf_blockchain_statistics surf_chain surf_protocol surf_app )
target_include_directories( surf_blockchain_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
        surf_blockchain_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)