#ifndef FOURIER_PLUGIN_H
#define FOURIER_PLUGIN_H

#include "fourier_plugin_global.h"
#include "cvplugininterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class PluginGui;
}
QT_END_NAMESPACE

class FOURIER_PLUGINSHARED_EXPORT Fourier_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Fourier_Plugin() {}
    ~Fourier_Plugin() {}

    QString title() override;
    QString version() override;
    QString description() override;
    QString help() override;
    void setupUi(QWidget *t_parent) override;
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination) override;

private:
    Ui::PluginGui *ui;

signals:
    void updateNeeded();
    void errorMessage(const QString &t_message);
    void infoMessage(const QString t_message);
};

#endif // FOURIER_PLUGIN_H
