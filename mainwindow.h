//
// Created by bp on 8/13/21.
//
#ifndef CAPSTONE_MAINWINDOW_H
#define CAPSTONE_MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <memory>

#include "mainwindow.h"
#include "opencv.h"

class MainWindow: public QWidget
        {
    Q_OBJECT
        public:
            explicit MainWindow(QWidget *parent = 0);
    signals:
            public slots:
            void uploadHandleButton();
        private:
            void setImage();
            void setImageLabel();
            void setFoundLabel(OpenCV &cv);
            QLabel *image_label_{new QLabel("No File Selected")};
            OpenCV cv_;
            QPushButton *image_button_{new QPushButton("Select Image")};
            QLabel *found_label_{new QLabel("")};
            QLabel *image_{new QLabel("Upload an image to check if image has a hot dog")};
            QString file_name_;
};
#endif //CAPSTONE_MAINWINDOW_H
