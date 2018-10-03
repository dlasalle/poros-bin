
# binary
add_executable(dolos_bin dolos_bin.c)
set_target_properties(dolos_bin PROPERTIES OUTPUT_NAME dolos)
target_link_libraries(dolos_bin wildriver dolos m)
if (NOT WIN32)
  install(TARGETS dolos_bin
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()

if (NOT WIN32)
  install(TARGETS dolos_bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif()


