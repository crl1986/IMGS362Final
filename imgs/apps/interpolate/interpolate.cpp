#include <cmath>
#include <iostream>

#include "imgs/numerical/interpolation/interpolation.h"

using namespace std;

int main() {
  Eigen::VectorXd x(11);
  x << 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
  Eigen::VectorXd y(11);
  for (std::size_t idx = 0; idx < static_cast<std::size_t>(x.size()); idx++) {
    y[idx] = pow(x[idx], 2);
  }

  Eigen::VectorXd xhat(6);
  xhat << 0, 1.7, 4, 6.2, 7.8, 10;

  Eigen::VectorXd yhat = numerical::Interp1(xhat, x, y);

  cout << "Original data:" << endl;
  for (std::size_t idx = 0; idx < static_cast<std::size_t>(x.size()); idx++) {
    cout << x[idx] << ", " << y[idx] << endl;
  }
  cout << endl;

  cout << "Interpolated data:" << endl;
  for (std::size_t idx = 0; idx < static_cast<std::size_t>(xhat.size());
       idx++) {
    cout << xhat[idx] << ", " << yhat[idx] << endl;
  }
  cout << endl;
}
