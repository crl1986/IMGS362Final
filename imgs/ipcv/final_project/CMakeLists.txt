rit_add_library(ipcv_final_project
  SOURCES
    Aging.cpp
  HEADERS
    Aging.h
)

target_link_libraries(ipcv_final_project
  PUBLIC
    opencv_core
  PRIVATE
    rit::ipcv_utils
)

