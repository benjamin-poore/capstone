//
// Created by bp on 8/13/21.
//
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include "opencv.h"

    using namespace std;
    using namespace cv;
    using namespace dnn;

    void OpenCV::runClassifier(std::string filename){
        std::vector<std::string> class_names;
        ifstream ifs(string("../input/object_detection_classes_coco.txt").c_str());
        string line;
        while (getline(ifs, line))
        {
            class_names.push_back(line);
        }

        // load the neural network model
        auto model = readNet("../input/frozen_inference_graph.pb",
                             "../input/ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt",
                             "TensorFlow");

//        read the image from disk that was loaded from the user in mainwindow
        Mat image = imread(filename);
        //create blob from image
        Mat blob = blobFromImage(image, 1, Size(320, 320), Scalar(127.5, 127.5, 127.5),
                                 true, false);
        model.setInput(blob);
        //forward pass detection
        Mat output = model.forward();

        Mat detectionMat(output.size[2], output.size[3], CV_32F, output.ptr<float>());

        // for loop control structure
        for (int i = 0; i < detectionMat.rows; i++){
            int class_id = detectionMat.at<float>(i, 1);
            float confidence = detectionMat.at<float>(i, 2);

            // Check if object detected a hot dog and that it has good confidence
            if (confidence > 0.4 && class_names[class_id-1] == "hot dog"){
                hot_dog_count_++;
                if(confidence > top_confidence_){
                    setTopConfidence(confidence);
                }
                int box_x = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
                int box_y = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
                int box_width = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols - box_x);
                int box_height = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows - box_y);
                rectangle(image, Point(box_x, box_y), Point(box_x+box_width, box_y+box_height), Scalar(255,0,0), 2);
                putText(image, class_names[class_id-1].c_str(), Point(box_x, box_y-5), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0), 2);
            }
        }
        // write file to output file showing box around image
        imwrite("../output/processed_image.jpeg", image);
    }

    void OpenCV::setTopConfidence(double confidence){
        top_confidence_ = confidence;
    }
    double OpenCV::getTopConfidence(){
     return top_confidence_;
    }
    int OpenCV::getHotDogCount(){
        return hot_dog_count_;
    }