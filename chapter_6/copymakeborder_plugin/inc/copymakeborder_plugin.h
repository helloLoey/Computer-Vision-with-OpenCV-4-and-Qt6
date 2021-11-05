#ifndef COPYMAKEBORDER_PLUGIN_H
#define COPYMAKEBORDER_PLUGIN_H

#include "copymakeborder_plugin_global.h"
#include "cvplugininterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class PluginGui;
}
QT_END_NAMESPACE

class COPYMAKEBORDER_PLUGINSHARED_EXPORT CopyMakeBorder_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    CopyMakeBorder_Plugin() {}
    ~CopyMakeBorder_Plugin() {}
    QString title() override;
    QString version() override;
    QString description() override;
    QString help();
    void setupUi(QWidget *t_parent) override;
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination) override;

private:
    Ui::PluginGui *ui;

private slots:
    void on_borderTypeComboBox_currentIndexChanged(int t_index);

signals:
    void updateNeeded();
    void errorMessage(const QString &t_message);
    void infoMessage(const QString &t_message);
};

#endif // COPYMAKEBORDER_PLUGIN_H
