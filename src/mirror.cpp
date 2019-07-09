#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
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

  // Break down original image to B,G,R three channels
  Mat channel_origin[3];
  split(img, channel_origin);

  int nRows = rows;
  int nCols = cols * 1; //Scalar is number of channels
  //int nStep = img.step;
  int nStep = channel_origin[0].step;

  Mat blank(rows, cols, CV_8UC3, Scalar(0,0,0)); // Three channels image
  //Mat blank(rows, cols, CV_8U, Scalar(0)); // One channel image
  //cout << blank << endl;

  // Three channels of channel_blank save mirror image in B,G,R channels respectively. 
  Mat channel_blank[3];
  split(blank, channel_blank);

  //uchar* srcData = channel_origin[0].data;  //Data is a pointer.Point to first index for each row
  //uchar* dstData = channel_blank[0].data;
  int cnt = 0;

  for (int k = 0; k < 3; k++){
    uchar* srcData = channel_origin[k].data;
    uchar* dstData = channel_blank[k].data;
    for (int i = 0; i < nRows; i++){
      for (int j = 0; j < nCols; j++){
        *(dstData+j) = *(srcData+nStep-1-j);
      }
      srcData += nStep;
      dstData += nStep;
      cnt += 1;
    }
  }
  cout << "count = " << cnt << endl;

  // Merge three channels of channel_blank to image blank.
  merge(channel_blank, 3, blank);

  // Create display window. There are two options to display image: WINDOW_AUTOSIZE and WINDOW_NORMAL.
  namedWindow("Figure",WINDOW_AUTOSIZE);
  namedWindow("Blank",WINDOW_AUTOSIZE);
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

