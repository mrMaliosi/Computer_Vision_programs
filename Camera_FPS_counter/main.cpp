#include "opencv2/opencv.hpp"
#include <ctime>
#include <time.h>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
	unsigned __int64 s1, s2, s0;
	double seconds, time = 0, time_to_show = 0, time_to_encode = 0;
	int count = 0;
	double cpu_Hz = 3400000000ULL;
	CvCapture *capture = cvCreateCameraCapture(0);
	if (!capture) return 0;
	s0 = __rdtsc();
	while (1) 
	{
		s1 = __rdtsc();
		IplImage *frame = cvQueryFrame(capture);
		s2 = __rdtsc();
		seconds =(double) (s2 - s1)/cpu_Hz;
		time_to_encode += seconds;
		//cout << "Time to encode frame: " << seconds << endl;
		time += seconds;
		if (!frame) break;
		s1 = __rdtsc();
		cvShowImage("test", frame);
		s2 = __rdtsc();
		seconds = (double)(s2 - s1) / cpu_Hz;
		time_to_show += seconds;
		//cout << "Time to show: " << seconds << endl;
		++count;
		time += seconds;
		

		if (time >= 1)
		{
			cout << "FPS: " << count << endl;
			cout << "Time to encode: " << (time_to_encode / time) * 100 << "%"<< endl;
			cout << "Time to show: " << (time_to_show / time) * 100 << "%" << endl;
			s0 = __rdtsc();
			count = 0;
			time = 0;
			time_to_encode = 0;
			time_to_show = 0;
		}
		char c = cvWaitKey(33);
		if (c == 27) break;

	}
	
}

