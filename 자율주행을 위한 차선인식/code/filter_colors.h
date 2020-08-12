#pragma once
#include <iostream>  
#include "IpDef.h"

class filter_colors
{
public:
	filter_colors() {}
	~filter_colors() {}
	void Filter_colors(Mat _img_bgr, Mat& img_filtered);

private:
	//���� ���� ���� 
	Scalar lower_white = Scalar(200, 200, 200); //��� ���� (RGB)
	Scalar upper_white = Scalar(255, 255, 255);
	Scalar lower_yellow = Scalar(10, 100, 100); //����� ���� (HSV)
	Scalar upper_yellow = Scalar(40, 255, 255);
};


