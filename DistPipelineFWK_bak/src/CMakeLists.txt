
# order matters here, because for example LibDSP uses LibCore, etc.
add_subdirectory(core)
include_directories(${LibCore_SOURCE_DIR})

add_subdirectory(dsp)
include_directories(${LibDSP_SOURCE_DIR})

add_subdirectory(signal_sources)
include_directories(${LibSources_SOURCE_DIR})

add_subdirectory(executables)
add_subdirectory(executables/clases)




add_executable (test_concept "test_concept.cpp")
target_link_libraries(test_concept ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_concept ${Boost_LIBRARIES})
target_link_libraries(test_concept ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(test_concept ${Boost_SYSTEM_LIBRARY})
target_link_libraries(test_concept ${Boost_THREAD_LIBRARY})
target_link_libraries(test_concept ${ALLEGRO_LIBRARIES})
target_link_libraries(test_concept ${GSL_LIBRARIES})
target_link_libraries(test_concept lib_dsp lib_core)
set_property(TARGET test_concept PROPERTY CXX_STANDARD 11)