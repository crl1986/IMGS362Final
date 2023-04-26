/** Application file for FILL
 *
 *  \file apps/FOLDER/FILENAME.cpp
 *  \author Anna Mason (axm2129@rit.edu)
 *  \date 01 May 2023
 */

#include <ctime>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/final_project/Aging.h"

using namespace std;

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
  src = cv::imread(src_filename, cv::IMREAD_GRAYSCALE);

  if (verbose) {
    cout << "Source filename: " << src_filename << endl;
    cout << "Size: " << src.size() << endl;
    cout << "Channels: " << src.channels() << endl;
    cout << "Destination filename: " << dst_filename << endl;
  }

  cv::Mat dst;
  bool status;
  clock_t startTime = clock();
  if (src.channels() == 1) {
    status = ipcv::cfaKodak(src, dst);
  } else {
    cerr << "Invalid source image, must be a 1 channel bayer pattern src "
            "image. The source image had "
         << src.channels() << " channel(s)." << endl;
    return EXIT_FAILURE;
  }
  clock_t endTime = clock();

  if (status == true) {
    cout << "CFA Kodak completed successfully" << endl;
  } else {
    return EXIT_FAILURE;
  }

  if (verbose) {
    cout << "Elapsed time: "
         << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
         << " [s]" << endl;
  }

  if (dst_filename.empty()) {
    cv::imshow(src_filename, src);
    cv::imshow(src_filename + " [CFA Kodak Interpolated]", dst);
    cv::waitKey(0);
  } else {
    cv::imwrite(dst_filename, dst);
  }

  return EXIT_SUCCESS;
}
