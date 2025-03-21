#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void setLabel(Mat& image, string str, vector<Point> contour);
Mat centerPutText(Mat& img_color, Mat& image, string str);

int main(int argc, char *argv[])
{
	Mat img_color, img_result, img_hsv;
	if(argc<2)
	{
		cout<<"Usage : "<<argv[0]<<"img_file"<<endl;
		exit(1);
	
	}
	img_color = imread(argv[1],IMREAD_COLOR);
	imshow("img_color",img_color);
	
	Mat red_mask,red_image;
	Scalar red_lower = Scalar(0,100,100);
	Scalar red_upper = Scalar(10,255,255);

	cvtColor(img_color,img_hsv,COLOR_BGR2HSV);
	imshow("img_hsv",img_hsv);
	inRange(img_hsv,red_lower,red_upper,red_mask);
	bitwise_and(img_color,img_color,red_image,red_mask);
	imshow("red_image",red_image);
	imshow("red_mask",red_mask);

	Scalar black_lower = Scalar(0,0,0);
	Scalar black_upper = Scalar(5,5,5);
	Mat black_mask;
	inRange(red_image,black_lower,black_upper,black_mask);
	imshow("black_mask",black_mask);
	red_image.setTo(Scalar(255,255,255),black_mask);
	imshow("red_image1",red_image);

	putText(img_color,"Garam Song",Point(20,40),FONT_HERSHEY_SIMPLEX,1,CV_RGB(0,0,0),3);
	imshow("red_image2",red_image);
	img_result = centerPutText(img_color,img_color,"red");
	imshow("red_image3",img_result);
	
	waitKey(0);
	return 0;
}

void setLabel(Mat& image, string str, vector<Point> contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 1;
	int baseline = 0;
	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2),
		r.y + ((r.height + text.height) / 2));

	rectangle(image, pt + Point(0, baseline), pt + Point(text.width,
		-text.height), CV_RGB(200, 200, 200), FILLED);
	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}
Mat centerPutText(Mat& img_color, Mat& image, string str)
{
	Mat img_gray, img_red,img_green, img_result,img_result1,img_result2,img_result3, img_hsv,red_mask,black_mask,img_blue;

	Scalar red_lower = Scalar(0,100,100);
        Scalar red_upper = Scalar(10,255,255);
	Scalar black_lower = Scalar(0,0,0);
        Scalar black_upper = Scalar(5,5,5);
        Scalar blue_lower = Scalar(90,100,100);
        Scalar blue_upper = Scalar(130,255,255);
	Scalar green_lower = Scalar(35,50,50);
        Scalar green_upper = Scalar(85,255,255);

	

        cvtColor(image,img_hsv,COLOR_BGR2HSV);
        inRange(img_hsv,red_lower,red_upper,red_mask);
	bitwise_and(image,image,img_red,red_mask);

        inRange(img_red,black_lower,black_upper,black_mask);
        img_red.setTo(Scalar(255,255,255),black_mask);
        imshow("red_image1",img_red);




	cvtColor(img_red, img_gray, COLOR_BGR2GRAY);
	imshow("img_gray1",img_gray);
	threshold(img_gray, img_gray, 30, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("img_gray",img_gray);

	vector<vector<Point> > contours;
	findContours(img_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	img_result1 = img_color.clone();

	for (size_t i = 0; i < contours.size(); i++)
	{
                int area = contourArea(contours[i]);
		if(area < 500)
			continue;
		cout<<"contours["<<i<<"] "<<contours[i]<<endl;
		setLabel(img_result1, "red", contours[i]);
	}
	
        inRange(img_hsv,blue_lower,blue_upper,red_mask);
        bitwise_and(image,image,img_blue,red_mask);

        inRange(img_blue,black_lower,black_upper,black_mask);
        img_blue.setTo(Scalar(255,255,255),black_mask);
        imshow("red_image2",img_blue);



        cvtColor(img_blue, img_gray, COLOR_BGR2GRAY);
        imshow("img_gray1",img_gray);
        threshold(img_gray, img_gray, 30, 255, THRESH_BINARY_INV | THRESH_OTSU);
        imshow("img_gray",img_gray);

        findContours(img_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        img_result2 = img_color.clone();

        for (size_t i = 0; i < contours.size(); i++)
        {
                int area = contourArea(contours[i]);
                if(area < 500)
                        continue;
                cout<<"contours["<<i<<"] "<<contours[i]<<endl;
                setLabel(img_result2, "blue", contours[i]);
        }
	


        inRange(img_hsv,green_lower,green_upper,red_mask);
        bitwise_and(image,image,img_green,red_mask);

        inRange(img_green,black_lower,black_upper,black_mask);
        img_green.setTo(Scalar(255,255,255),black_mask);
        imshow("red_image2",img_green);



        cvtColor(img_green, img_gray, COLOR_BGR2GRAY);
        imshow("img_gray1",img_gray);
        threshold(img_gray, img_gray, 30, 255, THRESH_BINARY_INV | THRESH_OTSU);
        imshow("img_gray",img_gray);

        findContours(img_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        img_result3 = img_color.clone();

        for (size_t i = 0; i < contours.size(); i++)
        {
                int area = contourArea(contours[i]);
                if(area < 500)
                        continue;
                cout<<"contours["<<i<<"] "<<contours[i]<<endl;
                setLabel(img_result3, "green", contours[i]);
        }


	
	img_result = img_result1+img_result2+img_result3;
	return img_result;
}	
