/** Implementation file for FILL
 *
 *  \file ipcv/folder/FILLNAME.cpp
 *  \author Anna Mason (axm2129@rit.edu)
 *  \date ## MON 2023
 */

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "Aging.h"
#include "imgs/ipcv/utils/Utils.h"

using namespace std;

namespace ipcv {

/** Description
 *
 *  \param[in] src             source cv::Mat of CV_8UC3
 *  \param[out] dst            destination cv::Mat of ddepth type
 *  \param[in] sigma_distance  standard deviation of distance/closeness filter
 *  \param[in] sigma_range     standard deviation of range/similarity filter
 *  \param[in] radius          radius of the bilateral filter (if negative, use
 *                             twice the standard deviation of the distance/
 *                             closeness filter)
 *  \param[in] border_mode     pixel extrapolation method
 *  \param[in] border_value    value to use for constant border mode
 */
bool cfaKodak(const cv::Mat& src, cv::Mat& dst) {
  //***** I don't even have a pla *****//

  cout << "wud up " << endl;

  return true;
}
}  // namespace ipcv
