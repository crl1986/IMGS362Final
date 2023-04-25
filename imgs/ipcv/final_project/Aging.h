/** Interface file for FILE
 *
 *  \file ipcv/FOLDER/FILENAME.h
 *  \author Anna Mason (axm2129@rit.edu)
 *  \date ## Mon 2023
 */

#pragma once

#include <opencv2/core.hpp>

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
bool cfaKodak(const cv::Mat& src, cv::Mat& dst);
}

