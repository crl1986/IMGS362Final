/** Implementation file for IPCV final project
 *
 *  \file ipcv/final_project/Aging.cpp
 *  \author Anna Mason (axm2129@rit.edu)
 *  \date 01 May 2023
 */

#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>

#include "Aging.h"
#include "imgs/ipcv/utils/Utils.h"

using namespace std;

namespace ipcv {

// resampling function to reduce resolution
bool Resampler(string raw_filepath, string resampled_filepath,
              const int dimension_divisor) {
  cv::VideoCapture raw_video(raw_filepath);

  int frame_width = raw_video.get(cv::CAP_PROP_FRAME_WIDTH);
  int frame_height = raw_video.get(cv::CAP_PROP_FRAME_HEIGHT);
  int framerate = raw_video.get(cv::CAP_PROP_FPS);  // per second

  int new_frame_width = frame_width / dimension_divisor;
  int new_frame_height = frame_height / dimension_divisor;

  cv::VideoWriter ds_video(
      resampled_filepath, cv::VideoWriter::fourcc('a', 'v', 'c', '1'),
      framerate, cv::Size(new_frame_width, new_frame_height));

  cv::Mat raw_frame;

  while (raw_video.read(raw_frame)) {
    cv::resize(raw_frame, raw_frame,
               cv::Size(new_frame_width, new_frame_height));

    ds_video.write(raw_frame);
  }

  ds_video.release();

  return true;
}

// function that places frames in a vector
bool Vectorizer(string src_filepath, vector<cv::Mat>& all_frames) {
  cv::VideoCapture video(src_filepath);

  int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
  int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);

  cv::Mat single_frame;
  single_frame.create(frame_height, frame_width, CV_8UC3);

  // vectorizing...
  while (video.read(single_frame)) {
    all_frames.push_back(single_frame.clone());
  }

  video.release();

  // grayscaling...
  for (unsigned int i = 0; i < all_frames.size(); i++) {
    cv::cvtColor(all_frames.at(i), all_frames.at(i), cv::COLOR_BGR2GRAY);
  }

  return true;
}

/** Function for blurring the "background" of an image with a person
 *
 *  \param[in] src             source image of CV_8UC1
 *  \param[in] mask            mask cv::Mat of CV_8UC1 (1 is the face, 0 is
 *                             the background)
 *
 *  \param[out] dst            output of CV_8UC1
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
  cv::Mat temp_dst;
  temp_dst = mask_unblurred + mask_blurred;

  // Save result
  temp_dst.convertTo(dst, CV_8UC1);

  return true;
}
}  // namespace ipcv
