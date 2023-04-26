/** Interface file for FILE
 *
 *  \file ipcv/FOLDER/FILENAME.h
 *  \author Anna Mason (axm2129@rit.edu)
 *  \date ## Mon 2023
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Function for blurring the "background" of an image with a person
 *
 *  \param[in] src             source image of CV_32FC1
 *  \param[in] mask            mask cv::Mat of CV_32FC1 (1 is the face, 0 is
 *                             the background)
 *
 *  \param[out] dst            destination cv::Mat of ddepth type
 */
bool backgroundBlur(const cv::Mat& src, cv::Mat& mask, cv::Mat& dst);
}

