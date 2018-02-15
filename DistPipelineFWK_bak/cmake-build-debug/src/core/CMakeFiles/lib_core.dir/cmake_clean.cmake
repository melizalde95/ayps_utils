file(REMOVE_RECURSE
  "liblib_core.pdb"
  "liblib_core.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/lib_core.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
