
# binary
add_executable(poros_bin poros_bin.c)
set_target_properties(poros_bin PROPERTIES OUTPUT_NAME poros)
target_link_libraries(poros_bin wildriver poros m)
if (NOT WIN32)
  install(TARGETS poros_bin
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()

if (NOT WIN32)
  install(TARGETS poros_bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif()


