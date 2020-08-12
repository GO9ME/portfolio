#pragma once
#include <iostream>  
#include "IpDef.h"

class region_of_interest
{
public:
	region_of_interest() {}
	~region_of_interest() {}
	Mat roi(Mat img_edges, Point* points);
private:

};

