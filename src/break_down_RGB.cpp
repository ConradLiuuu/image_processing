#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  // Read image
  Mat img = imread("/home/liu/catkin_ws/src/image_processing/picture/RGB.png",-1);

  int rows, cols;
  rows = img.rows;
  cols = img.cols;
  cout << "rows = " << img.rows << endl;
  cout << "cols = " << img.cols << endl;
  cout << "channels = " << img.channels() << endl; //channels of image
  cout << "type = " << img.type() << endl; //include depth and channels of image; type=16 it's mean CV_8UC3
  cout << "step = " << img.step << endl; //step = column * channel

  // Another way to get row and column
  /*
  Size s = img.size();
  rows = s.height;
  cols = s.width;
  cout << "rows = " << rows << endl;
  cout << "cols = " << cols << endl;
  */

  Mat channel[3];
  // Split img into three channels
  split(img,channel);
  imshow("Channel B",channel[0]);
  imshow("Channel G",channel[1]);
  imshow("Channel R",channel[2]);


  int nRows = rows;
  int nCols = cols * 3; //Scalar is number of channels
  int nStep = img.step;
  //int nStep = channel[0].step;

  Mat blank(rows, cols, CV_8UC3, Scalar(0,0,0)); // Three channels image
  //Mat blank(rows, cols, CV_8U, Scalar(0)); // One channel image
  //cout << blank << endl;

  uchar* srcData = img.data;  //Data is a pointer.Point to first index for each row
  //uchar* srcData = channel[2].data;
  uchar* dstData = blank.data;
  int cnt = 0;

  for (int i = 0; i < nRows; i++){
    for (int j = 0; j < nCols; j++){
      *(dstData+j) = *(srcData+j);
    }
    srcData += nStep;
    dstData += nStep;
    cnt += 1;
  }
  cout << "count = " << cnt << endl;

  // Create display window. There are two options to display image: WINDOW_AUTOSIZE and WINDOW_NORMAL.
  namedWindow("Figure",WINDOW_AUTOSIZE);
  namedWindow("Blank",WINDOW_AUTOSIZE);
  imshow("Figure",img);
  imshow("Blank", blank);

  // Press any key to close window
  int c = waitKey(0);
  // Press "Esc" to close particular window
  /*if (c == 27){
    destroyWindow("Figure");
    destroyWindow("Blank");
    //destroyWindow("B");
    //destroyWindow("G");
    //destroyWindow("R");
  }*/

  return 0;
}

