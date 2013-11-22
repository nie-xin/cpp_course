#include "MeanShift.h"

using namespace cv;
using namespace std;

const char* FILENAME = "/home/tracking_video.avi";

void mouseHandler(int event, int x, int y, int flags, void * param);
Rect rect;
CvPoint p1, p2;
bool bMoveDown = false;
bool isDrawing = false;
bool bDrawingFinished = false;

int main() {
    VideoCapture cap(FILENAME);
    Meanshift ms;
    Mat frame, imgBuffer, imgShow;
    int delay = (int)(1000/cap.get(CV_CAP_PROP_FPS));

    if (!cap.isOpened()) {
        cout << "Reading video error" << endl;

        return 1;
    }

    namedWindow(FILENAME);
    cap >> frame;
    imgBuffer = imgShow = frame.clone();
    setMouseCallback(FILENAME, mouseHandler, &imgBuffer);

    while (1) {
        if (isDrawing) {
            frame.copyTo(imgBuffer);
            rectangle(imgBuffer, p1, p2, CV_RGB(255, 0, 0), 2);
        }

        imgBuffer.copyTo(imgShow);
        imshow(FILENAME, imgShow);
        if (bDrawingFinished || waitKey(delay) == 27)
            break;
    }

    namedWindow("BACK");
    Mat imgBackProject;
    if (bDrawingFinished) {
        rect.x = p1.x;
        rect.y = p1.y;
        rect.width = p2.x - p1.x;
        rect.height = p2.y - p1.y;

        while (1) {
            if (!cap.read(frame) || waitKey(delay) == 27)
                break;
        }
    }

    return 0;
}

void mouseHandler(int event, int x, int y, int flags, void *param) {
    Mat img = * ((Mat*)param);

    switch(event) {
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
