/** Implementation file for computing the DFT of a vector
 *
 *  \file ipcv/utils/Dft.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 05 November 2020
 */

#include "Dft.h"

namespace ipcv {

cv::Mat Dft(cv::Mat f, const int flag) {
  const std::complex<double> i(0, 1);

  // Create the output cv::Mat (double-precision complex)
  int N = f.rows;
  cv::Mat F(N, 1, CV_64FC2);

  // Determine if the input cv::Mat is already complex (CV_64FC2).
  // If it is, create a shared pointer to the original data so no new
  // memory is required.
  // If it is not, create a local complex version of the input for
  // this computation.
  // In either case, the local version of the data to be transformed
  // will be referred to by the variable f_complex.
  cv::Mat f_complex;

  uchar depth = f.type() & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (f.type() >> CV_CN_SHIFT);
  if (depth == CV_64F && chans == 2) {
    // Create a shared pointer with the original cv::Mat
    f_complex = f;
  } else {
    // Convert the input cv::Mat to CV_64F representing the real part
    auto real = cv::Mat(f.size(), CV_64F);
    f.convertTo(real, CV_64F);

    // Create a CV_64F cv::Mat representing the imagingary part
    auto imag = cv::Mat(f.size(), CV_64F, cv::Scalar(0));

    // Merge the real and imagingary to form a CV_64FC2 cv::Mat
    std::vector<cv::Mat> channels;
    channels.push_back(real);
    channels.push_back(imag);
    cv::merge(channels, f_complex);
  }


  // INSERT YOUR CODE HERE
  // To compute the forward and inverse DFT on a cv::Mat of dimension Nx1


  return F;
}
}
