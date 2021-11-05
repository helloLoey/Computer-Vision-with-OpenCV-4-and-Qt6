#include "fourier_plugin.h"
#include "ui_plugin.h"

QString Fourier_Plugin::title()
{
    return this->metaObject()->className();
}

QString Fourier_Plugin::version()
{
    return "1.0.0";
}

QString Fourier_Plugin::description()
{
    return "A <b>Template</b> plugin";
}

QString Fourier_Plugin::help()
{
    return "This is a <b>Template</b> plugin. Clone and use it to create new plugins.";
}

void Fourier_Plugin::setupUi(QWidget *t_parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(t_parent);
}

void Fourier_Plugin::processImage(const cv::Mat &t_source, cv::Mat &t_destination)
{
    cv::Mat gray_image;
    cv::cvtColor(t_source, gray_image, cv::COLOR_BGR2GRAY);
    int optimal_height = cv::getOptimalDFTSize(gray_image.rows);
    int optimal_width = cv::getOptimalDFTSize(gray_image.cols);
    cv::Mat padded;
    cv::copyMakeBorder(gray_image, padded, 0, optimal_height - gray_image.rows, 0, optimal_width - gray_image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::Mat channels[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat complex;
    cv::merge(channels, 2, complex);
    cv::dft(complex, complex);
    cv::split(complex, channels);
    cv::Mat magnitude;
    cv::magnitude(channels[0], channels[1], magnitude);
    magnitude += cv::Scalar::all(1);
    cv::log(magnitude, magnitude);
    magnitude = magnitude(cv::Rect(0, 0, magnitude.cols & -2, magnitude.rows & -2));
    int cx = magnitude.cols / 2;
    int cy = magnitude.rows / 2;
    cv::Mat q0(magnitude, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(magnitude, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(magnitude, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(magnitude, cv::Rect(cx, cy, cx, cy));
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    cv::normalize(magnitude, magnitude, 0, 255, cv::NORM_MINMAX);
    cv::Mat_<uchar> magI8bit(magnitude);
    cv::cvtColor(magI8bit, t_destination, cv::COLOR_GRAY2BGR);
}
