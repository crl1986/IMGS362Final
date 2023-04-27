/** Application file for FILL
 *
 *  \file apps/final_project/Aging.cpp
 *  \author Anna Mason (axm2129@rit.edu)
 *  \date 01 May 2023
 */

#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "imgs/ipcv/final_project/Aging.h"

using namespace std;
using namespace cv;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  // Intialization
  bool verbose = false;
  string src_filename = "";
  string dst_filename = "";

  // Boost Program Settings
  po::options_description options("Options");
  options.add_options()("help,h", "display this message")(
      "verbose,v", po::bool_switch(&verbose), "verbose [default is silent]")(
      "source-filename,i", po::value<string>(&src_filename), "source filename")(
      "destination-filename,o", po::value<string>(&dst_filename),
      "destination filename");

  po::positional_options_description positional_options;
  positional_options.add("source-filename", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
                .options(options)
                .positional(positional_options)
                .run(),
            vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << "Usage: " << argv[0] << " [options] source-filename" << endl;
    cout << options << endl;
    return EXIT_SUCCESS;
  }

  if (!boost::filesystem::exists(src_filename)) {
    cerr << "Provided source file does not exists" << endl;
    return EXIT_FAILURE;
  }
  cv::Mat src;
  src = cv::imread(src_filename, cv::IMREAD_UNCHANGED);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  bool status;
  bool resample = false;
  std::string resampled_filename = "resampled_src.mp4";

  if (resample) {
    status = ipcv::Resampler(src_filename, resampled_filename, 4);
    src_filename = resampled_filename;
  }

  clock_t startTime = clock();

  std::vector<cv::Mat> all_frames;
  status = ipcv::Vectorizer(src_filename, all_frames);
  if (status == true) {
    cout << "Vectorization completed successfully" << endl;
    status = false;
  } else {
    return EXIT_FAILURE;
  }

  // Micah's Contribution (Eric didn't do anything. Give him a zero)

  Mat equalized;
  CascadeClassifier cascade;
  cascade.load(
      "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");

  std::vector<cv::Rect> faces;
  cv::Rect rect(1, 1, 2, 2);
  faces.push_back(rect);
  int cols = all_frames[0].cols;
  int rows = all_frames[0].rows;
  Rect boundary((2*cols/5), (2*rows)/5, cols/5, rows/5);
  rectangle(all_frames[0], boundary.tl(), boundary.br(), Scalar(255, 0, 0), 2, LINE_8);
  cout << boundary << endl;

  Point center, tl, br;

  //cv::imshow("Src with Boundary", all_frames[0]);
  //cv::waitKey(0);
  cv::Mat mask(all_frames[0].size(), CV_8UC1, cv::Scalar(0));
  //cv::rectangle(mask, faces[0], cv::Scalar(255), cv::FILLED);

  vector<Mat> good_frames, masks;

  for (int i = 0; i < all_frames.size(); i++) {
    cv::equalizeHist(all_frames[i].clone(), equalized);
    cascade.detectMultiScale(equalized, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE,
                             cv::Size(30, 30));

      tl = faces[0].tl();
      br = faces[0].br();
      center.x = (tl.x + br.x)/2;
      center.y = (tl.y + br.y)/2;
      if(boundary.contains(center)){
      good_frames.push_back(all_frames[i]);
      
      //cv::Mat mask(all_frames[0].size(), CV_8UC1, cv::Scalar(0));
      cv::rectangle(mask, faces[0], cv::Scalar(255), cv::FILLED);
      masks.push_back(mask.clone());
      }
      mask = 0;
     //break;
     }

    cout << good_frames.size() << endl;

    imshow("frame 1",good_frames[0]);
    imshow("frame 2",good_frames[2000]);
    imshow("frame 3",good_frames[4000]);

    imshow("mask 1",masks[0]);
    imshow("mask 2",masks[2000]);
    imshow("mask 3",masks[4000]);
    waitKey(0);

  /*
    status = ipcv::backgroundBlur(src, mask, dst);

    if (status == true) {
      cout << "Background Blur completed successfully" << endl;
    } else {
      return EXIT_FAILURE;
    }
  */
  clock_t endTime = clock();

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  return EXIT_SUCCESS;
}
