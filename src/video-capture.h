#ifndef WINNIE_VIDEO_CAPTURE_H
#define WINNIE_VIDEO_CAPTURE_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "colors.h"

using namespace cv;
using namespace cv::ml;
using namespace std;

inline void detectHumans() {

    VideoCapture cap(0);

    if(!cap.isOpened()) {
        cout << "{\"error\": \"Unable to read from WebCam\"}" << endl;
    }

    cap.set(CV_CAP_PROP_FRAME_WIDTH,  640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Point> track;

    for(;;) {

        Mat frame;
        cap >> frame;


        Mat img = frame.clone();
        resize(img,img,Size(img.cols*2, img.rows*2));

        vector<Rect> found;
        vector<double> weights;

        hog.detectMultiScale(img, found, weights);

        for( size_t i = 0; i < found.size(); i++) {

            Rect r = found[i];
            rectangle(img, found[i], cv::Scalar(0,0,255), 3);

            stringstream temp;
            temp << weights[i];

            putText(img, temp.str(),Point(found[i].x,found[i].y+50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255));

            track.push_back(Point(found[i].x+found[i].width/2,found[i].y+found[i].height/2));
        }

        for(size_t i = 1; i < track.size(); i++){
            line(img, track[i-1], track[i], Scalar(255,255,0), 2);
        }

        imshow("Detection", img);

        if(waitKey(27) >= 0) {
            break;
        }

    }

}


#endif //WINNIE_VIDEO_CAPTURE_H
