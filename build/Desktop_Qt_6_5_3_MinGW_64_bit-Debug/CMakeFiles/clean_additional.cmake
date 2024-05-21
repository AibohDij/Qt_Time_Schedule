# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PKUToDo_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PKUToDo_autogen.dir\\ParseCache.txt"
  "PKUToDo_autogen"
  )
endif()
