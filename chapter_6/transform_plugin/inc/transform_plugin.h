#ifndef TRANSFORM_PLUGIN_H
#define TRANSFORM_PLUGIN_H

#include "transform_plugin_global.h"
#include "cvplugininterface.h"
#include <QObject>
#include <QtMath>

namespace Ui {
    class PluginGui;
}

class TRANSFORM_PLUGINSHARED_EXPORT Transform_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Transform_Plugin() {}
    ~Transform_Plugin() {}

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
    void on_resizeHalfRadio_toggled(bool t_is_checked);
    void on_resizeDoubleRadio_toggled(bool t_is_checked);
    void on_remapRadio_toggled(bool t_is_checked);
    void on_affineRadio_toggled(bool t_is_checked);
    void on_perspectiveRadio_toggled(bool t_is_checked);
    void on_borderTypeCombo_currentIndexChanged(int t_index);
    void on_interpolationCombo_currentIndexChanged(int t_index);

private:
    Ui::PluginGui *ui;
};

#endif // TRANSFORM_PLUGIN_H
