add_executable( surfd main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling surfd with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( SURF_STATIC_BUILD )
   target_link_libraries( surfd PRIVATE
      "-static-libstdc++ -static-libgcc"
      surf_plugins
      surf_mf_plugins
      surf_app
      surf_witness
      surf_account_history
      surf_chain
      surf_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
else( SURF_STATIC_BUILD )
   target_link_libraries( surfd PRIVATE
      surf_plugins
      surf_mf_plugins
      surf_app
      surf_witness
      surf_account_history
      surf_chain
      surf_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( SURF_STATIC_BUILD )

install( TARGETS
        surfd

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
