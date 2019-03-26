file(GLOB HEADERS "include/surf/witness/*.hpp")

add_library( surf_witness
             witness_plugin.cpp
             witness_evaluators.cpp
             witness_operations.cpp
           )

target_link_libraries( surf_witness surf_chain surf_protocol surf_app )
target_include_directories( surf_witness
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
        surf_witness

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
