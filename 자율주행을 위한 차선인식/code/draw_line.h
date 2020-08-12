#pragma once
#include <iostream>  
#include "IpDef.h"
#include <gsl/gsl_fit.h>

class draw_line
{
public:
	draw_line() {}
	~draw_line() {}
	void draw_carline(Mat& img_line, vector<Vec4i> lines);
	Point lineLineIntersection(Point A, Point B, Point C, Point D);
private:
	//Region - of - interest vertices, 관심 영역 범위 계산시 사용 
	//We want a trapezoid shape, with bottom edge at the bottom of the image
	float trap_bottom_width = 0.85;  // width of bottom edge of trapezoid, expressed as percentage of image width
	float trap_top_width = 0.07;     // ditto for top edge of trapezoid
	float trap_height = 0.4;         // height of the trapezoid expressed as percentage of image height
	Point ptVanish;

};

