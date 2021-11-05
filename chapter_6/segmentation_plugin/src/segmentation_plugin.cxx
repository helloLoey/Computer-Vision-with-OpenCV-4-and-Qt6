#include "segmentation_plugin.h"

#include "ui_plugin.h"

QString Segmentation_Plugin::title()
{
    return this->metaObject()->className();
}

QString Segmentation_Plugin::version()
{
    return "1.0.0";
}

QString Segmentation_Plugin::description()
{
    return "";
}

QString Segmentation_Plugin::help()
{
    return "";
}

void Segmentation_Plugin::setupUi(QWidget *t_parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(t_parent);

    ui->threshAdaptiveCombo->addItems(
                QStringList()
                << "ADAPTIVE_THRESH_MEAN_C"
                << "ADAPTIVE_THRESH_GAUSSIAN_C");

    ui->threshTypeCombo->addItems(
                QStringList()
                << "THRESH_BINARY"
                << "THRESH_BINARY_INV"
                << "THRESH_TRUNC"
                << "THRESH_TOZERO"
                << "THRESH_TOZERO_INV");
    connect(ui->threshAdaptiveCheck, SIGNAL(toggled(bool)), this, SLOT(on_threshAdaptiveCheck_toggled(bool)));
    connect(ui->threshAdaptiveCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_threshAdaptiveCombo_currentIndexChanged(int)));
    connect(ui->threshTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_threshTypeCombo_currentIndexChanged(int)));
    connect(ui->threshSlider, SIGNAL(valueChanged(int)), this, SLOT(on_threshSlider_valueChanged(int)));
    connect(ui->threshMaxSlider, SIGNAL(valueChanged(int)), this, SLOT(on_threshMaxSlider_valueChanged(int)));

}

void Segmentation_Plugin::processImage(const cv::Mat &t_source, cv::Mat &t_destination)
{
    cv::Mat gray_image;
    cv::cvtColor(t_source, gray_image, cv::COLOR_BGR2GRAY);
    if (ui->threshAdaptiveCheck->isChecked())
        cv::adaptiveThreshold(gray_image, gray_image, ui->threshMaxSlider->value(),
                              ui->threshAdaptiveCombo->currentIndex(), ui->threshTypeCombo->currentIndex(), 7, 0);
    else
        cv::threshold(gray_image,gray_image, ui->threshSlider->value(), ui->threshMaxSlider->value(),
                      ui->threshTypeCombo->currentIndex());
    cv::cvtColor(gray_image, t_destination, cv::COLOR_GRAY2BGR);
}

void Segmentation_Plugin::on_threshAdaptiveCheck_toggled(bool t_is_checked)
{
    Q_UNUSED(t_is_checked);
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshAdaptiveCombo_currentIndexChanged(int t_index)
{
    Q_UNUSED(t_index);
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshTypeCombo_currentIndexChanged(int t_index)
{
    Q_UNUSED(t_index);
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshSlider_valueChanged(int t_value)
{
    emit infoMessage(QString::number(t_value));
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshMaxSlider_valueChanged(int t_value)
{
    emit infoMessage(QString::number(t_value));
    emit updateNeeded();
}
