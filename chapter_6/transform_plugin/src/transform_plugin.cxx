#include "transform_plugin.h"
#include "ui_plugin.h"

QString Transform_Plugin::title()
{
    return this->metaObject()->className();
}

QString Transform_Plugin::version()
{
    return "1.0.0";
}

QString Transform_Plugin::description()
{
    return "Performs different transformations available in OpenCV";
}

QString Transform_Plugin::help()
{
    return "This is a plugin that performs different filters available in OpenCV";
}

void Transform_Plugin::setupUi(QWidget *t_parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(t_parent);

    ui->borderTypeCombo->addItems(
                QStringList()
                << "BORDER_CONSTANT"
                << "BORDER_REPLICATE"
                << "BORDER_REFLECT"
                << "BORDER_WRAP"
                << "BORDER_REFLECT_101");

    ui->interpolationCombo->addItems(
                QStringList()
                << "INTER_NEAREST"
                << "INTER_CUBIC"
                << "INTER_AREA"
                << "INTER_LANCZOS4");

    connect(ui->resizeHalfRadio, SIGNAL(toggled(bool)), this, SLOT(on_resizeHalfRadio_toggled(bool)));
    connect(ui->resizeDoubleRadio, SIGNAL(toggled(bool)), this, SLOT(on_resizeDoubleRadio_toggled(bool)));
    connect(ui->remapRadio, SIGNAL(toggled(bool)), this, SLOT(on_remapRadio_toggled(bool)));
    connect(ui->affineRadio, SIGNAL(toggled(bool)), this, SLOT(on_affineRadio_toggled(bool)));
    connect(ui->perspectiveRadio, SIGNAL(toggled(bool)), this, SLOT(on_perspectiveRadio_toggled(bool)));
    connect(ui->borderTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_borderTypeCombo_currentIndexChanged(int)));
    connect(ui->interpolationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_interpolationCombo_currentIndexChanged(int)));
}

void Transform_Plugin::processImage(const cv::Mat &t_source, cv::Mat &t_destination)
{
    using namespace cv;
    if(ui->resizeHalfRadio->isChecked())
    {
        resize(t_source,
               t_destination,
               Size(),
               0.5,
               0.5,
               ui->interpolationCombo->currentIndex());
    }
    else if(ui->resizeDoubleRadio->isChecked())
    {
        resize(t_source,
               t_destination,
               Size(),
               2.0,
               2.0,
               ui->interpolationCombo->currentIndex());
    }
    else if(ui->affineRadio->isChecked())
    {
        Point2f triangleA[3];
        Point2f triangleB[3];

        triangleA[0] = Point2f(0, 0);
        triangleA[1] = Point2f(t_source.cols - 1, 0);
        triangleA[2] = Point2f(0, t_source.rows - 1);

        triangleB[0] = Point2f(t_source.cols*0.0, t_source.rows*0.33);
        triangleB[1] = Point2f(t_source.cols*0.85, t_source.rows*0.25);
        triangleB[2] = Point2f(t_source.cols*0.15, t_source.rows*0.7);

        Mat affineMat = getAffineTransform( triangleA, triangleB );

        warpAffine( t_source,
                    t_destination,
                    affineMat,
                    t_source.size(),
                    ui->interpolationCombo->currentIndex(),
                    ui->borderTypeCombo->currentIndex());
    }
    else if(ui->perspectiveRadio->isChecked())
    {
        std::vector<Point2f> cornersA(4);
        std::vector<Point2f> cornersB(4);

        cornersA[0] = Point2f(0, 0);
        cornersA[1] = Point2f(t_source.cols, 0);
        cornersA[2] = Point2f(t_source.cols, t_source.rows);
        cornersA[3] = Point2f(0, t_source.rows);

        cornersB[0] = Point2f(t_source.cols*0.25, 0);
        cornersB[1] = Point2f(t_source.cols * 0.90, 0);
        cornersB[2] = Point2f(t_source.cols, t_source.rows);
        cornersB[3] = Point2f(0, t_source.rows * 0.80);

        Mat homo = findHomography(cornersA, cornersB, RANSAC);
        warpPerspective(t_source,
                        t_destination,
                        homo,
                        t_source.size(),
                        ui->interpolationCombo->currentIndex(),
                        ui->borderTypeCombo->currentIndex()); // do perspective transformation
    }
    else if(ui->remapRadio->isChecked())
    {
        cvtColor(t_source, t_destination, CV_32FC(1));;
        Mat mapX, mapY;
        mapX.create(t_source.size(), CV_32FC(1));
        mapY.create(t_source.size(), CV_32FC(1));

        Point2f center(t_source.cols/2,
                       t_source.rows/2);

        for(int i=0; i<t_source.rows; i++)
            for(int j=0; j<t_source.cols; j++)
            {
                double x = j - center.x;
                double y = i - center.y;

                x = x*x/500;
                /* y = y; */

                mapX.at<float>(i,j) = x + center.x;
                mapY.at<float>(i,j) = y + center.y;
            }

        remap(t_source,
              t_destination,
              mapX,
              mapY,
              INTER_LANCZOS4,
              BORDER_CONSTANT);

    }
}

void Transform_Plugin::on_resizeHalfRadio_toggled(bool t_is_checked)
{
    Q_UNUSED(t_is_checked);
    emit updateNeeded();
}

void Transform_Plugin::on_resizeDoubleRadio_toggled(bool t_is_checked)
{
    Q_UNUSED(t_is_checked);
    emit updateNeeded();
}

void Transform_Plugin::on_remapRadio_toggled(bool t_is_checked)
{
    Q_UNUSED(t_is_checked);
    emit updateNeeded();
}

void Transform_Plugin::on_affineRadio_toggled(bool t_is_checked)
{
    Q_UNUSED(t_is_checked);
    emit updateNeeded();
}

void Transform_Plugin::on_perspectiveRadio_toggled(bool t_is_checked)
{
    Q_UNUSED(t_is_checked);
    emit updateNeeded();
}

void Transform_Plugin::on_borderTypeCombo_currentIndexChanged(int t_index)
{
    Q_UNUSED(t_index);
    emit updateNeeded();
}

void Transform_Plugin::on_interpolationCombo_currentIndexChanged(int t_index)
{
    Q_UNUSED(t_index);
    emit updateNeeded();
}
