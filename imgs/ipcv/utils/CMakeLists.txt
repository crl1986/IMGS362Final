rit_add_library(ipcv_utils 
  SOURCES
    ApplyLut.cpp
    DeltaE.cpp
    Dft.cpp
    Dft2.cpp
    DftMagnitude.cpp
    DftMultiply.cpp
    DftShift.cpp
    Dist.cpp
    GammaCorrection.cpp
    GrayworldAwb.cpp
    Histogram.cpp
    HistogramToPdf.cpp
    HistogramToCdf.cpp
    Psnr.cpp
    Rmse.cpp
  HEADERS
    ApplyLut.h
    DeltaE.h
    Dft.h
    Dft2.h
    DftMagnitude.h
    DftMultiply.h
    DftShift.h
    Dist.h
    GammaCorrection.h
    GrayworldAwb.h
    Histogram.h
    HistogramToPdf.h
    HistogramToCdf.h
    Psnr.h
    Rmse.h
    Utils.h
)

target_link_libraries(ipcv_utils
  PUBLIC
    opencv_core
    opencv_imgproc
  PRIVATE
)
