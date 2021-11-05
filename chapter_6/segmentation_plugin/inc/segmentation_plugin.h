#ifndef SEGMENTATION_PLUGIN_H
#define SEGMENTATION_PLUGIN_H

#include "segmentation_plugin_global.h"
#include "cvplugininterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class PluginGui;
}
QT_END_NAMESPACE

class SEGMENTATION_PLUGINSHARED_EXPORT Segmentation_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Segmentation_Plugin() {}
    ~Segmentation_Plugin() {}

    QString title() override;
    QString version() override;
    QString description() override;
    QString help() override;
    void setupUi(QWidget *t_parent) override;
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination) override;

signals:
    void updateNeeded();
    void errorMessage(const QString &t_message);
    void infoMessage(const QString &t_message);

private slots:
    void on_threshAdaptiveCheck_toggled(bool t_is_checked);
    void on_threshAdaptiveCombo_currentIndexChanged(int t_index);
    void on_threshTypeCombo_currentIndexChanged(int t_index);
    void on_threshSlider_valueChanged(int t_value);
    void on_threshMaxSlider_valueChanged(int t_value);

private:
    Ui::PluginGui *ui;
};

#endif // SEGMENTATION_PLUGIN_H
