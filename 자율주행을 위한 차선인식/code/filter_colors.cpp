#include "filter_colors.h"

void filter_colors::Filter_colors(Mat _img_bgr, Mat& img_filtered)
{
	// Filter the image to include only yellow and white pixels
	Mat img_bgr;
	_img_bgr.copyTo(img_bgr);
	Mat img_hsv, img_combine;
	Mat white_mask, white_image;
	Mat yellow_mask, yellow_image;


	//Filter white pixels
	inRange(img_bgr, lower_white, upper_white, white_mask);
	bitwise_and(img_bgr, img_bgr, white_image, white_mask);


	//Filter yellow pixels( Hue 30 )
	cvtColor(img_bgr, img_hsv, COLOR_BGR2HSV);


	inRange(img_hsv, lower_yellow, upper_yellow, yellow_mask);
	bitwise_and(img_bgr, img_bgr, yellow_image, yellow_mask);
	


	//Combine the two above images
	addWeighted(white_image, 1.0, yellow_image, 1.0, 0.0, img_combine);


	img_combine.copyTo(img_filtered);
}
