#include "IpDef.h"
#include <gsl/gsl_fit.h>
#include <iostream>  
#include "draw_line.h"
#include "filter_colors.h"
#include "region_of_interest.h"

using namespace cv;
using namespace std;



//Hough Transform 파라미터
float rho = 2; // distance resolution in pixels of the Hough grid
float theta = 1 * CV_PI / 180; // angular resolution in radians of the Hough grid
float hough_threshold = 15;    // minimum number of votes(intersections in Hough grid cell)
float minLineLength = 10; //minimum number of pixels making up a line
float maxLineGap = 20;   //maximum gap in pixels between connectable line segments


//Region - of - interest vertices, 관심 영역 범위 계산시 사용 
//We want a trapezoid shape, with bottom edge at the bottom of the image
float trap_bottom_width = 0.85;  // width of bottom edge of trapezoid, expressed as percentage of image width
float trap_top_width = 0.07;     // ditto for top edge of trapezoid
float trap_height = 0.4;         // height of the trapezoid expressed as percentage of image height

int main(int, char**)
{
	char buf[256];
	Mat img_bgr, img_gray, img_edges, img_hough, img_annotated;


	VideoCapture videoCapture("challenge.mp4");

	if (!videoCapture.isOpened())
	{
		cout << "동영상 파일을 열수 없습니다. \n" << endl;

		char a;
		cin >> a;

		return 1;
	}

	videoCapture.read(img_bgr);
	if (img_bgr.empty()) return -1;

	VideoWriter writer;
	int codec = VideoWriter::fourcc('X', 'V', 'I', 'D');  // select desired codec (must be available at runtime)
	double fps = 25.0;                          // framerate of the created video stream
	string filename = "./live.avi";             // name of the output video file
	writer.open(filename, codec, fps, img_bgr.size(), CV_8UC3);
	// check if we succeeded
	if (!writer.isOpened()) {
	   cerr << "Could not open the output video file for write\n";
	   return -1;
	}



	videoCapture.read(img_bgr);
	int width = img_bgr.size().width;
	int height = img_bgr.size().height;

	int count = 0;

	while (1)
	{

		//1. 원본 영상을 읽어옴 
		videoCapture.read(img_bgr);
		if (img_bgr.empty()) break;


		//2. 미리 정해둔 흰색, 노란색 범위 내에 있는 부분만 차선후보로 따로 저장함 
		Mat img_filtered;

		filter_colors fc;
		fc.Filter_colors(img_bgr, img_filtered);

		//3. 그레이스케일 영상으로 변환하여 에지 성분을 추출
		cvtColor(img_filtered, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(3, 3), 0, 0);
		Canny(img_gray, img_edges, 50, 150);



		int width = img_filtered.cols;
		int height = img_filtered.rows;


		Point points[4];
		points[0] = Point((width * (1 - trap_bottom_width)) / 2, height);
		points[1] = Point((width * (1 - trap_top_width)) / 2, height - height * trap_height);
		points[2] = Point(width - (width * (1 - trap_top_width)) / 2, height - height * trap_height);
		points[3] = Point(width - (width * (1 - trap_bottom_width)) / 2, height);



		//4. 차선 검출할 영역을 제한함(진행방향 바닥에 존재하는 차선으로 한정)
		region_of_interest Roi;
		img_edges = Roi.roi(img_edges, points);


		UMat uImage_edges;
		img_edges.copyTo(uImage_edges);

		//5. 직선 성분을 추출(각 직선의 시작좌표와 끝좌표를 계산함)
		vector<Vec4i> lines;
		HoughLinesP(uImage_edges, lines, rho, theta, hough_threshold, minLineLength, maxLineGap);




		//6. 5번에서 추출한 직선성분으로부터 좌우 차선에 있을 가능성있는 직선들만 따로 뽑아서
		//좌우 각각 하나씩 직선을 계산함 (Linear Least-Squares Fitting)
		Mat img_line = Mat::zeros(img_bgr.rows, img_bgr.cols, CV_8UC3);
		
		draw_line dl;
		dl.draw_carline(img_line, lines);


		//7. 원본 영상에 6번의 직선을 같이 보여줌 
		addWeighted(img_bgr, 0.8, img_line, 1.0, 0.0, img_annotated);


		//8. 결과를 동영상 파일로 기록 
		writer << img_annotated;

		count++;
		if (count == 10) imwrite("img_annota1ted.jpg", img_annotated);

		//9. 결과를 화면에 보여줌 
		Mat img_result;
		resize(img_annotated, img_annotated, Size(width * 0.7, height * 0.7));
		resize(img_edges, img_edges, Size(width * 0.7, height * 0.7));
		cvtColor(img_edges, img_edges, COLOR_GRAY2BGR);
		hconcat(img_edges, img_annotated, img_result);
		imshow("차선 영상", img_result);




		if (waitKey(1) == 27) break; //ESC키 누르면 종료  
	}


	return 0;
}