#include "opencv2/photo.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <iostream>
#include <fstream>
//#include "opencv2/opencv.hpp"


#ifdef _DEBUG
#pragma comment(lib, "opencv_world430d.lib")
#else
#pragma comment(lib, "opencv_world430.lib")
#endif //_DEBUG
using namespace cv;
using namespace std;

void equalizeHist16Bit(const cv::Mat& _src, cv::Mat& _dst)
{
    _dst = _src.clone();

    const int hist_sz = 65536;
    int* hist = new int[hist_sz] {};
    int* lut = new int[hist_sz] {};

    for (int y = 0; y < _src.rows; y++)
        for (int x = 0; x < _src.cols; x++)
            hist[(int)_src.at<unsigned short int>(y, x)]++;

    auto i = 0;
    while (!hist[i]) ++i;

    auto total = (int)_src.total();
    if (hist[i] == total)
    {
        _dst.setTo(i);
        return;
    }

    float scale = (hist_sz - 1.f) / (total - hist[i]);
    auto sum = 0;

    for (lut[i++] = 0; i < hist_sz; ++i)
    {
        sum += hist[i];
        lut[i] = cv::saturate_cast<ushort>(sum * scale);
    }

    for (int y = 0; y < _src.rows; y++)
        for (int x = 0; x < _src.cols; x++)
        {
            _dst.at<unsigned short int>(y, x) = lut[(int)_src.at<unsigned short int>(y, x)];
        }
}

void sharp(const Mat& input, Mat& output) {
    output.create(input.size(), input.type());
    for (int j = 1; j < input.rows - 1; j++) {
        const uchar* prevRow = input.ptr<const uchar>(j - 1); //이전 행
        const uchar* currRow = input.ptr<const uchar>(j); //현재 행
        const uchar* nextRow = input.ptr<const uchar>(j + 1); //다음 행

        uchar* resultRow = output.ptr<uchar>(j); //결과 행
        for (int i = 1; i < input.cols - 1; i++) {
            *resultRow++ = saturate_cast<uchar>(5 * currRow[i] - currRow[i - 1] - currRow[i + 1] - prevRow[i] - nextRow[i]);
        }
    }
    output.row(0).setTo(Scalar(0));
    output.row(output.rows - 1).setTo(Scalar(0));
    output.col(0).setTo(Scalar(0));
    output.col(output.cols - 1).setTo(Scalar(0));
}
int main()
{
    int rows = 3072;
    int cols = 3072;
    vector<ushort> arr1(cols * rows);
    //chest-ap-3_3072x3072_16bit
    //복부-AP_16bit
    //척추-lat-8_16bit
    FILE* file1 = fopen("chest-ap-3_3072x3072_16bit.raw", "rb");
    fread((void*)arr1.data(), 3072 * 3072 * 2, 1, file1);

    Mat before1 = Mat(rows, cols, CV_16UC1, arr1.data());

    rotate(before1, before1, ROTATE_90_COUNTERCLOCKWISE);
    Mat invImg = before1.clone();

    invImg = ~before1;
    Mat equlhistoImg;
    equalizeHist16Bit(invImg, equlhistoImg);

    Mat equlhistoImg8(rows, cols, CV_8UC1);
    cv::normalize(equlhistoImg, equlhistoImg8, 0, 255, NORM_MINMAX);
    equlhistoImg8 += 44;

    equlhistoImg8.convertTo(equlhistoImg8, CV_8UC1);


    Mat image_canny;
    //blur(equlhistoImg8, image_canny, Size(3, 3));
    // double sigmaColor = 10.0;
    // double sigmaSpace = 10.0;
    //bilateralFilter(equlhistoImg8, image_canny, -1, sigmaColor, sigmaSpace);

    //Canny(equlhistoImg8, image_canny, 150, 255, 3);
    //threshold(image_canny, image_canny, 0, 255, THRESH_BINARY_INV);
    //adaptiveThreshold(equlhistoImg8, image_canny,80, ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,3,5);
    //adaptiveThreshold(equlhistoImg8, image_canny, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 10);
    //Mat kernel = cv::Mat::ones(3, 3, CV_32F) / (float)(3 * 3);
    //filter2D(equlhistoImg8, image_canny, -1,kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    sharp(equlhistoImg8, image_canny);

    string savepath = "ap-3_3072x3072_16bit_convert.jpg";
    imwrite(savepath, image_canny);


    return 0;
}










