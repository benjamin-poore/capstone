//
// Created by bp on 8/13/21.
//
#ifndef CAPSTONE_OPENCV_H
#define CAPSTONE_OPENCV_H
#include <string>


class OpenCV {
public:
    void runClassifier(std::string filename);
    void setTopConfidence(double x);
    double getTopConfidence();
    int getHotDogCount();

private:
    double top_confidence_{0};
    int hot_dog_count_{0};
};
#endif //CAPSTONE_OPENCV_H
