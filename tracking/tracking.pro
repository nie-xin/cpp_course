#-------------------------------------------------
#
# Project created by QtCreator 2013-11-21T15:54:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tracking
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    finder.cpp

INCLUDEPATH += /usr/include/opencv2
LIBS += -L/usr/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann\

OTHER_FILES += \
    TP_image.pro.user \
    ImageTest.pro.user \
    Image.1 \
    tracking.pro.user \
    README.txt

HEADERS += \
    TF.h \
    SobelContours.h \
    Rotation.h \
    Projection.h \
    IntroductionUsingOpenCV.h \
    Hough.h \
    GaussienFilter.h \
    DrawObject.h \
    ConnectedComponents.h \
    Compare.h \
    CannyContours.h \
    MeanShift.h \
    objectFinder.h \
    imageComparator.h \
    histogram.h \
    colorhistogram.h
