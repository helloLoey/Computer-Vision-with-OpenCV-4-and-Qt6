#ifndef COLOR_PLUGIN_H
#define COLOR_PLUGIN_H

#include "color_plugin_global.h"
#include "cvplugininterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class PluginGui;
}
QT_END_NAMESPACE

class COLOR_PLUGINSHARED_EXPORT Color_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Color_Plugin() {}
    ~Color_Plugin() {}

    QString title() override;
    QString version() override;
    QString description() override;
    QString help() override;
    void setupUi(QWidget *t_parent) override;
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination) override;

private:
    Ui::PluginGui *ui;

private slots:
    void on_colorMapCombo_currentIndexChanged(int t_index);

signals:
    void updateNeeded();
    void errorMessage(const QString &t_message);
    void infoMessage(const QString &t_message);
};

#endif // COLOR_PLUGIN_H
