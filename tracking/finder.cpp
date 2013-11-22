/*------------------------------------------------------------------------------------------*\
   This file contains material supporting chapter 4 of the cookbook:  
   Computer Vision Programming using the OpenCV Library. 
   by Robert Laganiere, Packt Publishing, 2011.

   This program is free software; permission is hereby granted to use, copy, modify, 
   and distribute this source code, or portions thereof, for any purpose, without fee, 
   subject to the restriction that the copyright notice may not be removed 
   or altered from any source or altered source distribution. 
   The software is released on an as-is basis and without any warranties of any kind. 
   In particular, the software is not guaranteed to be fault-tolerant or free from failure. 
   The author disclaims all warranties with regard to this software, any use, 
   and any consequent failure, is purely the responsibility of the user.
 
   Copyright (C) 2010-2011 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/
#include <QtCore/QCoreApplication>
#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include "objectFinder.h"
#include "colorhistogram.h"

void mouseHandler(int event, int x, int y, int flags, void* param);
cv::Rect ROI;
CvPoint p1, p2;
bool bMoveDown = false;
bool isDrawing = false;
bool bDrawingFinished = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "start tracking..." << endl;
    cout << "Kernel = mean shift" << endl;

    // Read video sequence
    cv::Mat frame, imgBuffer, imgShow;
    cv::VideoCapture capture("tracking_video.avi");
    int delay = (int)(1000 / capture.get(CV_CAP_PROP_FPS));

    cv::namedWindow("capture");
    capture.read(frame);
    imgBuffer = imgShow = frame.clone();
    cv::setMouseCallback("capture", mouseHandler, &imgBuffer);

    while (1) {
        if (isDrawing) {
            cout << "Selecting object" << endl;
            frame.copyTo(imgBuffer);
            rectangle(imgBuffer, p1, p2, CV_RGB(255, 0, 0), 2);
        }
        imgBuffer.copyTo(imgShow);
        imshow("capture", imgShow);
        if (bDrawingFinished || cv::waitKey(delay) == 27) {
            cout << "Selection finished" << endl;
            break;
        }
    }

    if (bDrawingFinished) {
            // define ROI
            ROI.x = p1.x;
            ROI.y = p1.y;
            ROI.width = p2.x - p1.x;
            ROI.height = p2.y - p1.y;

            cv::Mat imageROI= frame(cv::Rect(ROI.x, ROI.y, ROI.width, ROI.height));
            cv::imshow("test", imageROI);

            // Get the Hue histogram
            int minSat=65;

            ColorHistogram hc;
            cv::MatND colorhist = hc.getHueHistogram(imageROI);

            ObjectFinder finder;
            finder.setHistogram(colorhist);
            finder.setThreshold(0.2f);

            // Convert to HSV space
            cv::Mat hsv;
            cv::cvtColor(frame, hsv, CV_BGR2HSV);

            // Split the image
            vector<cv::Mat> v;
            cv::split(hsv,v);

            // Eliminate pixels with low saturation
            cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);

            // Get back-projection of hue histogram
            int ch[1]={0};
            cv::Mat result= finder.find(hsv,0.0f,180.0f,ch,1);
            cv::bitwise_and(result,v[1],result);

            while (1) {
                if(!capture.read(frame))
                        break;
                // tracking
                // Convert to HSV space
                cv::cvtColor(frame, hsv, CV_BGR2HSV);

                // Split the image
                cv::split(hsv,v);

                // Eliminate pixels with low saturation
                cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);

                // Get back-projection of hue histogram
                result= finder.find(hsv,0.0f,180.0f,ch,1);

                // Eliminate low stauration pixels
                cv::bitwise_and(result,v[1],result);

                // Get back-projection of hue histogram
                finder.setThreshold(-1.0f);
                result= finder.find(hsv,0.0f,180.0f,ch,1);

                cv::bitwise_and(result,v[1],result);

                cv::Rect rect(ROI.x, ROI.y, ROI.width, ROI.height);
                cv::rectangle(frame, rect, cv::Scalar(0,0,255));
                cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);
                cout << "meanshift = " << cv::meanShift(result,rect,criteria) << endl;


                cv::rectangle(frame, rect, cv::Scalar(0,255,0));

                cv::imshow("Tracking", frame);
                cv::waitKey(5);
            }
    }
    // Fin of video processing

//	// Read reference image
//    cv::Mat image= cv::imread("/home/niexin/images/baboon1.jpg");
//	if (!image.data)
//		return 0;

//	// Define ROI
//    cv::Mat imageROI= image(cv::Rect(110,260,35,40));
//    cv::rectangle(image, cv::Rect(110,260,35,40),cv::Scalar(0,0,255));

//     // Display image
//    cv::namedWindow("Image");
//    cv::imshow("Image",image);

//    // Get the Hue histogram
//    int minSat=65;

//    ColorHistogram hc;
//    cv::MatND colorhist = hc.getHueHistogram(imageROI);

//    ObjectFinder finder;
//    finder.setHistogram(colorhist);
//    finder.setThreshold(0.2f);

//    // Convert to HSV space
//    cv::Mat hsv;
//    cv::cvtColor(image, hsv, CV_BGR2HSV);

//    // Split the image
//    vector<cv::Mat> v;
//    cv::split(hsv,v);

//    // Eliminate pixels with low saturation
//    cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);
////    cv::namedWindow("Saturation");
////    cv::imshow("Saturation",v[1]);

//    // Get back-projection of hue histogram
//    int ch[1]={0};
//    cv::Mat result= finder.find(hsv,0.0f,180.0f,ch,1);

////    cv::namedWindow("Result Hue");
////    cv::imshow("Result Hue",result);

//    cv::bitwise_and(result,v[1],result);
////    cv::namedWindow("Result Hue and");
////    cv::imshow("Result Hue and",result);

//    // Second image
//    image= cv::imread("/home/niexin/images/baboon3.jpg");

//    // Display image
////    cv::namedWindow("Image 2");
////    cv::imshow("Image 2",image);

//    // Convert to HSV space
//    cv::cvtColor(image, hsv, CV_BGR2HSV);

//    // Split the image
//    cv::split(hsv,v);

//    // Eliminate pixels with low saturation
//    cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);
////    cv::namedWindow("Saturation");
////    cv::imshow("Saturation",v[1]);

//    // Get back-projection of hue histogram
//    result= finder.find(hsv,0.0f,180.0f,ch,1);

////    cv::namedWindow("Result Hue");
////    cv::imshow("Result Hue",result);

//    // Eliminate low stauration pixels
//    cv::bitwise_and(result,v[1],result);
////    cv::namedWindow("Result Hue and");
////    cv::imshow("Result Hue and",result);

//    // Get back-projection of hue histogram
//    finder.setThreshold(-1.0f);
//    result= finder.find(hsv,0.0f,180.0f,ch,1);
//    cv::bitwise_and(result,v[1],result);
////    cv::namedWindow("Result Hue and raw");
////    cv::imshow("Result Hue and raw",result);

//    cv::Rect rect(110,260,35,40);
//    cv::rectangle(image, rect, cv::Scalar(0,0,255));

//    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);
//    cout << "meanshift= " << cv::meanShift(result,rect,criteria) << endl;

//    cv::rectangle(image, rect, cv::Scalar(0,255,0));

//    // Display image
//    cv::namedWindow("Image 2 result");
//    cv::imshow("Image 2 result",image);

	cv::waitKey();

    return a.exec();
}

void mouseHandler(int event, int x, int y, int flags, void* param) {
    cv::Mat img = *((cv::Mat*)param);

    switch (event) {
        case CV_EVENT_MOUSEMOVE:
            if (bMoveDown) {
                p2.x = x;
                p2.y = y;
                isDrawing = true;
            }
            break;
        case CV_EVENT_LBUTTONDOWN:
            if (!isDrawing) {
                bMoveDown = true;
                p1.x = x;
                p1.y = y;
            }
            break;
        case CV_EVENT_LBUTTONUP:
            bMoveDown = false;
            if (isDrawing) {
                bDrawingFinished = true;
                isDrawing = false;
            }
            break;
        case CV_EVENT_RBUTTONDOWN:
            break;
    }
}
