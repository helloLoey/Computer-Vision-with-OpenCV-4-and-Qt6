#include "copymakeborder_plugin.h"

#include "ui_plugin.h"

QString CopyMakeBorder_Plugin::title()
{
    return this->metaObject()->className();
}

QString CopyMakeBorder_Plugin::version()
{
    return "1.0.0";
}

QString CopyMakeBorder_Plugin::description()
{
    return "";
}

QString CopyMakeBorder_Plugin::help()
{
    return "";
}

void CopyMakeBorder_Plugin::setupUi(QWidget *t_parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(t_parent);
    QStringList items;
    items.append("BORDER_CONSTANT");
    items.append("BORDER_REPLICATE");
    items.append("BORDER_REFLECT");
    items.append("BORDER_WRAP");
    items.append("BORDER_REFLECT_101");
    ui->borderTypeComboBox->addItems(items);
    connect(ui->borderTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_borderTypeComboBox_currentIndexChanged(int)));
}

void CopyMakeBorder_Plugin::processImage(const cv::Mat &t_source, cv::Mat &t_destination)
{
    int top, bot, left, right;
    top = bot = t_source.rows/2;
    left = right = t_source.cols/2;
    cv::copyMakeBorder(t_source, t_destination, top, bot, left, right, ui->borderTypeComboBox->currentIndex());
}

void CopyMakeBorder_Plugin::on_borderTypeComboBox_currentIndexChanged(int t_index)
{
    Q_UNUSED(t_index);
    emit updateNeeded();
}
