project(LibDSP)

file(GLOB LIB_DSP_SRC
        "*.hpp"
        "*.cpp" )

#STATIC???
add_library(lib_dsp STATIC ${LIB_DSP_SRC})
target_link_libraries(lib_dsp lib_core)
target_link_libraries(lib_dsp ${GSL_LIBRARIES})
set_property(TARGET lib_dsp PROPERTY CXX_STANDARD 11)