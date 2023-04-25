rit_add_executable(final_project
  SOURCES
    aging.cpp
)

target_link_libraries(final_project
  rit::ipcv_final_project
  rit::ipcv_utils
  Boost::filesystem
  Boost::program_options
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)

