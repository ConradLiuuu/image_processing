#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  int frame = 5;

  // Read image
  Mat img = imread("/home/liu/catkin_ws/src/image_processing/picture/lenna.jpg",-1);

  int rows, cols;
  rows = img.rows;
  cols = img.cols;
  cout << "rows = " << img.rows << endl;
  cout << "cols = " << img.cols << endl;
  cout << "channels = " << img.channels() << endl; //channels of image
  cout << "type = " << img.type() << endl; //include depth and channels of image; type=16 it's mean CV_8UC3
  cout << "step = " << img.step << endl; //step = column * channel

  int nRows = rows;
  int nCols = cols * 3; //Scalar is number of channels
  int nStep = img.step;
  int n_step = (cols+2*frame) * 3;
  //int nStep = channel[0].step;

  Mat blank(rows+2*frame, cols+2*frame, CV_8UC3, Scalar(0,0,0)); // Three channels image
  //Mat blank(rows, cols, CV_8U, Scalar(0)); // One channel image
  //cout << blank << endl;

  uchar* srcData = img.data;  //Data is a pointer.Point to first index for each row
  uchar* dstData = blank.data;
  int cnt = 0;

  for (int i = 0; i < nRows; i++){
    for (int j = 0; j < nCols; j++){
      // Shift pointer to (frame,frame).
      // In row direction, pointer should shift (frame * #channels) pixels
      // In column direction, pointer should shift (frame * n_step) pixels
      *((dstData+frame*n_step+frame*3)+j) = *(srcData+j);
    }
    srcData += nStep;
    dstData += n_step;
    cnt += 1;
  }
  cout << "count = " << cnt << endl;

  // Create display window. There are two options to display image: WINDOW_AUTOSIZE and WINDOW_NORMAL.
  namedWindow("Figure",WINDOW_NORMAL);
  namedWindow("Blank",WINDOW_NORMAL);
  imshow("Figure",img);
  imshow("Blank", blank);

  // Press any key to close window
  waitKey(0);
  // Press "Esc" to close particular window
  /*if (c == 27){
    destroyWindow("Figure");
    destroyWindow("Blank");
  }*/

  return 0;
}

