#include "color_plugin.h"
#include "ui_plugin.h"

QString Color_Plugin::title()
{
    return this->metaObject()->className();
}

QString Color_Plugin::version()
{
    return "1.0.0";
}

QString Color_Plugin::description()
{
    return "";
}

QString Color_Plugin::help()
{
    return "";
}

void Color_Plugin::setupUi(QWidget *t_parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(t_parent);

    ui->colorMapCombo->addItems(QStringList()
                                << "COLORMAP_AUTUMN"
                                << "COLORMAP_BONE"
                                << "COLORMAP_JET"
                                << "COLORMAP_WINTER"
                                << "COLORMAP_RAINBOW"
                                << "COLORMAP_OCEAN"
                                << "COLORMAP_SUMMER"
                                << "COLORMAP_SPRING"
                                << "COLORMAP_COOL"
                                << "COLORMAP_HSV"
                                << "COLORMAP_PINK"
                                << "COLORMAP_HOT"
                                << "COLORMAP_PARULA");

    connect(ui->colorMapCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_colorMapCombo_currentIndexChanged(int)));
}

void Color_Plugin::processImage(const cv::Mat &t_source, cv::Mat &t_destination)
{
    using namespace cv;
    applyColorMap(t_source, t_destination, ui->colorMapCombo->currentIndex());
}

void Color_Plugin::on_colorMapCombo_currentIndexChanged(int t_index)
{
    Q_UNUSED(t_index);
    emit updateNeeded();
}
