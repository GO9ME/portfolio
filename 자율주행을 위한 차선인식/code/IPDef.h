#pragma once
#include <iostream>
#include <fstream>
#include <opencv2\opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world430d.lib")
#else
#pragma comment(lib, "opencv_world430.lib")
#endif // _DEBUG

using namespace cv;
using namespace std;