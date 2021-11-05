#ifndef FILTER_PLUGIN_H
#define FILTER_PLUGIN_H

#include "filter_plugin_global.h"
#include "cvplugininterface.h"
#include <QObject>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui {
    class PluginGui;
}
QT_END_NAMESPACE

class FILTER_PLUGINSHARED_EXPORT Filter_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Filter_Plugin() {}
    ~Filter_Plugin() {}

    QString title();
    QString version();
    QString description();
    QString help();
    void setupUi(QWidget *t_parent);
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination);

private:
    Ui::PluginGui *ui;
    enum {
        BILATERAL_FILTER_PAGE,
        BLUR_FILTER_PAGE,
        BOX_FILTER_PAGE,
        GAUSSIAN_FILTER_PAGE,
        MEDIAN_FILTER_PAGE,
        FILTER2D_PAGE,
        DERIVATIVES_PAGE};

private slots:
    void on_bilateralDiaSpin_valueChanged(int arg1);
    void on_bilateralSigmaColorSpin_valueChanged(double arg1);
    void on_bilateralSigmaSpaceSpin_valueChanged(double arg1);
    void on_blurKernelSizeSpinBox_valueChanged(int arg1);
    void on_blurAnchoXSpin_valueChanged(int arg1);
    void on_blurAnchoYSpin_valueChanged(int arg1);
    void on_boxKernelSizeSpinBox_valueChanged(int arg1);
    void on_boxDepthSpin_valueChanged(int arg1);
    void on_boxAnchoXSpin_valueChanged(int arg1);
    void on_boxAnchoYSpin_valueChanged(int arg1);
    void on_boxNormalCheck_toggled(bool checked);
    void on_gaussKernelSizeSpinBox_valueChanged(int arg1);
    void on_gaussSigmaXSpin_valueChanged(double arg1);
    void on_gaussSigmaYSpin_valueChanged(double arg1);
    void on_medianApertureSpin_valueChanged(int arg1);
    void on_mainTabs_currentChanged(int index);
    void on_derivSobelRadio_toggled(bool checked);
    void on_derivScharrRadio_toggled(bool checked);
    void on_derivLaplacRadio_toggled(bool checked);
    void on_derivScaleSpin_valueChanged(double arg1);
    void on_derivDeltaSpin_valueChanged(double arg1);
    void on_morphErodeRadio_toggled(bool checked);
    void on_morphDilateRadio_toggled(bool checked);
    void on_morphMorphRadio_toggled(bool checked);
    void on_morphIterSpin_valueChanged(int arg1);
    void on_morphTypesCombo_currentIndexChanged(int index);
    void on_morphShapesCombo_currentIndexChanged(int index);

signals:
    void updateNeeded();
    void errorMessage(const QString &t_message);
    void infoMessage(const QString &t_message);
};

#endif // FILTER_PLUGIN_H
