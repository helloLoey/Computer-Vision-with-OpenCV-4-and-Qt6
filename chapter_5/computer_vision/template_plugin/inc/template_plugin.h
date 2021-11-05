#ifndef TEMPLATE_PLUGIN_H
#define TEMPLATE_PLUGIN_H

#include "template_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class TEMPLATE_PLUGINSHARED_EXPORT Template_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Template_Plugin();
    ~Template_Plugin();

    QString title() override;
    QString version() override;
    QString description() override;
    QString help();
    void setupUi(QWidget *t_parent);
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination);

signals:
    void updateNeeded();
    void errorMessage(const QString &t_message);
    void infoMessage(const QString &t_message);

private:
    Ui::PluginGui *ui;

};

#endif // TEMPLATE_PLUGIN_H
