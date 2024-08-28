//https://docs.opencv.org/3.4/da/d6a/tutorial_trackbar.html 
#include "opencv2\opencv.hpp"
#include <stdint.h>
#include <iostream>
#include <fstream>


using namespace cv;
using namespace std;

Mat nti;
Mat HSVnti;
Mat HSVntiBin;
Mat square;

int a1 = 0, a2 = 0, b1 = 0, b2 = 0, check = 0;

int main(void)
{


	nti = imread("test_01.png");
	double angle = 90;
	//imshow("Ho", nti);

	// get rotation matrix for rotating the image around its center in pixel coordinates
	/*Point2f center((nti.cols - 1) / 2.0, (nti.rows - 1) / 2.0);
	Mat rot = getRotationMatrix2D(center, angle, 1.0);
	// determine bounding rectangle, center not relevant
	Rect2f bbox = RotatedRect(Point2f(), nti.size(), angle).boundingRect2f();
	// adjust transformation matrix
	rot.at<double>(0, 2) += bbox.width / 2.0 - nti.cols / 2.0;
	rot.at<double>(1, 2) += bbox.height / 2.0 - nti.rows / 2.0;

	warpAffine(nti, nti, rot, bbox.size());
	imwrite("rotated_im.png", nti);*/

	ofstream file;
	file.open("task2_1.json", ios_base::app);
	file << "{ " << endl;
	file << "\"grid\": " << endl;
	file << "{" << endl;
	file << "\"x\": \"10\", " << endl;
	file << "\"y\": \"10\", " << endl;
	file << "\"z\": \"12\" " << endl;
	file << "}," << endl;
	file << "\"objectsinmm\": [" << endl;
	file.close();

	Next:
	cvtColor(nti, HSVnti, CV_BGR2HSV);
	//imshow("H", HSVnti);
	cvtColor(nti, square, CV_BGR2HSV);
	Mat squar = HSVnti;
	Rect sq(0, 0, (float)squar.cols / 2, (float)squar.rows / 2);
	//Rect sq((float)squar.cols/2, 0, (float)squar.cols/2 - 1, (float)squar.rows / 2);
	//Rect sq(0, (float)squar.rows / 2, (float)squar.cols / 2, (float)squar.rows / 2 - 1);
	//Rect sq((float)squar.cols / 2, (float)squar.rows / 2, (float)squar.cols / 2 - 1, (float)squar.rows / 2 - 1);
	square = squar(sq);

	double app1 = -1, app2 = -1, app3 = -1, app4 = -1;


	
	//inRange(HSVnti, Scalar(0, 0, 118), Scalar(180, 255, 255), HSVntiBin);
	//imshow("HSV", HSVnti);
	imshow("Original", nti);
	//imshow("Bin", HSVntiBin);
	imshow("Square", square);


	vector<Point> app;
	vector<vector<Point> > contours;

	if (-1 > 0)
	{
	pravo:
		Rect sql((float)squar.cols / 2, 0, (float)squar.cols / 2 - 1, (float)squar.rows / 2);
		squar = HSVnti;
		square = squar(sql);
	}

	if (-1 > 0)
	{
	last:
		Rect sqk((float)squar.cols / 2, (float)squar.rows / 2, (float)squar.cols / 2 - 1, (float)squar.rows / 2 - 1);
		squar = HSVnti;
		square = squar(sqk);
	}
	inRange(square, Scalar(80, 41, 28), Scalar(122, 111, 175), square);
	findContours(square, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> mu(contours.size());
	vector<Point2f> mc(contours.size());



	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), app, arcLength(Mat(contours[i]), true)*0.008, true);

		double area = fabs(contourArea((Mat)contours[i]));

		//ќбводим контуры на изображении, удовлетвор€ющие по площади
		//если нижнюю границу area понизить до 300 area > 300, то будут прорисовыватьс€ и буквы внутри знака STOP
		//if (area > 1000 && area < 50000)
		polylines(square, app, true, Scalar(255, 0, 0), 1, 8); //https://docs.opencv.org/3.0-beta/modules/imgproc/doc/..
		/*
		* »гнорировать слишком маленькие и слишком большие объекты, а также незамкнутые контуры
		*/
		if (area < 100) //|| !isContourConvex(app)) //ќтфильтровываем объекты, попадающие в услови€ и учитываем только выпуклые фигуры (Convex)
			continue;

		Rect bounding = boundingRect(app);

		Mat rp = square(bounding);
		rectangle(square, bounding, Scalar(255), 10, 8, 0);


		if ((check == 2) && (app.size() == 16))
		{
			mu[i] = moments(contours[i]);
			a2 = static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5));
			b2 = static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5));

			cout << "a2 " << a2 << endl;
			cout << "b2 " << b2 << endl;

			goto end;
		}

		if (app.size() == 18)
		{
			mu[i] = moments(contours[i]);
			a1 = static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5));
			b1 = static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5));

			cout << "a1 " << a1 << endl;
			cout << "b1 " << b1 << endl;

			Rect sqf((float)squar.cols / 2, (float)squar.rows / 2, (float)squar.cols / 2 - 1, (float)squar.rows / 2 - 1);
			squar = HSVnti;
			square = squar(sqf);
			check = 2;
			goto last;
		}

		if (((app.size() == 16) || (app.size() == 15)) && (check != 1))
		{
			check = 1;
			app1 = -1;
			app2 = -1;
			app3 = -1;
			goto pravo;

		}

		if ((check = 1) && ((app.size() == 16) || (app.size() == 15)))
		{
			double angle = 180;

			// get rotation matrix for rotating the image around its center in pixel coordinates
			Point2f center((nti.cols - 1) / 2.0, (nti.rows - 1) / 2.0);
			Mat rot = getRotationMatrix2D(center, angle, 1.0);
			// determine bounding rectangle, center not relevant
			Rect2f bbox = RotatedRect(Point2f(), nti.size(), angle).boundingRect2f();
			// adjust transformation matrix
			rot.at<double>(0, 2) += bbox.width / 2.0 - nti.cols / 2.0;
			rot.at<double>(1, 2) += bbox.height / 2.0 - nti.rows / 2.0;

			warpAffine(nti, nti, rot, bbox.size());

			goto Next;
		}



		if ((app.size() == 8) || (app.size() == 7) || (app.size() == 9))
		{
			double angle = 90;

			// get rotation matrix for rotating the image around its center in pixel coordinates
			Point2f center((nti.cols - 1) / 2.0, (nti.rows - 1) / 2.0);
			Mat rot = getRotationMatrix2D(center, angle, 1.0);
			// determine bounding rectangle, center not relevant
			Rect2f bbox = RotatedRect(Point2f(), nti.size(), angle).boundingRect2f();
			// adjust transformation matrix
			rot.at<double>(0, 2) += bbox.width / 2.0 - nti.cols / 2.0;
			rot.at<double>(1, 2) += bbox.height / 2.0 - nti.rows / 2.0;

			warpAffine(nti, nti, rot, bbox.size());

			goto Next;
		}

		cout << area << endl;
		cout << app.size() << endl;
		/*cout << "x " << x << endl;
		cout << "y " << y << endl;*/


	}



	app1 = -1;
	app2 = -1;
	app3 = -1;



	end:
	cvtColor(nti, HSVnti, CV_BGR2HSV);
	Rect sqr(a1, b1, a2*2 - a1, b2*2 - b1);
	HSVnti = HSVnti(sqr);
	imshow("Canny", HSVnti);
	inRange(HSVnti, Scalar(0, 101, 0), Scalar(180, 255, 255), HSVntiBin); //inRange(HSVnti, Scalar(10, 0, 50), Scalar(30, 255, 255), HSVntiBin);

	//GaussianBlur(frame, image, cv::Size(0, 0), 11);
	//addWeighted(frame, 1.5, image, -0.5, 0, image);
	//Canny(HSVntiBin, HSVntiBin, 50, 150, 3); //40 и 120

	findContours(HSVntiBin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<Point> approx;

	vector<Moments> m1(contours.size());
	vector<Point2f> m2(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.008, true);

		double area = fabs(contourArea((Mat)contours[i]));

		m1[i] = moments(contours[i]);
		m2[i] = Point2f(static_cast<float>(m1[i].m10 / (m1[i].m00 + 1e-5)), static_cast<float>(m1[i].m01 / (m1[i].m00 + 1e-5)));
		cout << "mc[" << i << "]=" << m2[i] << endl;
		Point c((m1[i].m10 / (m1[i].m00)), (m1[i].m01 / (m1[i].m00)));
		circle(HSVntiBin, Point((m1[i].m10 / (m1[i].m00)), (m1[i].m01 / (m1[i].m00))), 1, Scalar(0, 255, 255), 1, 8);

		//ќбводим контуры на изображении, удовлетвор€ющие по площади
		//если нижнюю границу area понизить до 300 area > 300, то будут прорисовыватьс€ и буквы внутри знака STOP
		//if (area > 1000 && area < 50000)
		polylines(nti, approx, true, Scalar(255, 0, 0), 1, 8); //https://docs.opencv.org/3.0-beta/modules/imgproc/doc/..
		/*
		* »гнорировать слишком маленькие и слишком большие объекты, а также незамкнутые контуры
		*/
		if (area < 500) //|| !isContourConvex(app)) //ќтфильтровываем объекты, попадающие в услови€ и учитываем только выпуклые фигуры (Convex)
			continue;

		Rect boundingarea = boundingRect(approx);

		Mat rp = nti(boundingarea);
		//imshow("rp", rp);
		//float dl = (float)boundingarea.width / (float)boundingarea.height;
		//if (dl > 0.9 && dl < 1.1 ) { //далее дополнить проверку на цветность && app.size() == 8

		/*int mx = (float)boundingarea.width;
		int my = (float)boundingarea.height;
		int x = int(area/mx);
		int y = double( area/ my);

		/*moments(HSVntiBin, 1);
		double mx = moments[m01];
		double my = moments[m10];*/
		rectangle(nti, boundingarea, Scalar(255), 10, 8, 0);

		if ((app1 == -1) || (app1 == approx.size()))
		{
			app1 = approx.size();
		}
		else
		{
			app2 = approx.size();
		}

		if (area > 4990)
		{

		}
		cout << area << endl;
		cout << approx.size() << endl;
		/*cout << "x " << x << endl;
		cout << "y " << y << endl;*/
		//}

	}


	//imshow("original", nti);
	//imshow("search", HSVntiBin);


	waitKey(0);
	return 0;
}
