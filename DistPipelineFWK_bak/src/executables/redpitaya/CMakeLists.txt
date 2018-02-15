
file(GLOB REDPITAYA_SRC
        "*.hpp"
        "*.cpp" )

add_executable (redpitaya ${REDPITAYA_SRC})
target_link_libraries(redpitaya ${Boost_LIBRARIES})
target_link_libraries(redpitaya ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(redpitaya ${Boost_SYSTEM_LIBRARY})
target_link_libraries(redpitaya ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(redpitaya ${ALLEGRO_LIBRARIES})
target_link_libraries(redpitaya ${GSL_LIBRARIES})
target_link_libraries(redpitaya lib_dsp lib_core)
set_property(TARGET redpitaya PROPERTY CXX_STANDARD 11)