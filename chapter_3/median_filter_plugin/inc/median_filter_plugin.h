#ifndef MEDIAN_FILTER_PLUGIN_H
#define MEDIAN_FILTER_PLUGIN_H

#include "median_filter_plugin_global.h"

#include "cvplugininterface.h"

class MEDIAN_FILTER_PLUGIN_EXPORT MedianFilterPlugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.amin.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)

public:
    MedianFilterPlugin() {}
    ~MedianFilterPlugin() {}
    QString description();
    void processImage(const cv::Mat &t_source, cv::Mat &t_destination);
};

#endif // MEDIAN_FILTER_PLUGIN_H
