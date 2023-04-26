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

/** Function for blurring the "background" of an image with a person
 *
 *  \param[in] src             source image of CV_32FC1
 *  \param[in] mask            mask cv::Mat of CV_32FC1 (1 is the face, 0 is
 *                             the background)
 *
 *  \param[out] dst            destination cv::Mat of ddepth type
 */
bool backgroundBlur(const cv::Mat& src, cv::Mat& mask, cv::Mat& dst) {
  //***** I don't even have a pla *****//
  cv::Mat new_src;
  src.convertTo(new_src, CV_32FC1);
  cv::Mat new_mask;
  mask.convertTo(new_mask, CV_32FC1);

  // Multiply unblurred with mask
  cv::Mat mask_unblurred;
  cv::multiply(new_src, new_mask, mask_unblurred);

  // Blur src
  cv::Mat blurred_src;
  cv::blur(new_src, blurred_src, cv::Size(5, 5));

  // Multiply blurred src with inverted mask
  cv::Mat inverted_mask;
  inverted_mask = abs(new_mask - 1);
  cv::Mat mask_blurred;
  cv::multiply(inverted_mask, blurred_src, mask_blurred);

  // Combine the two frames >> dst
  dst = mask_unblurred + mask_blurred;

  return true;
}
}  // namespace ipcv
