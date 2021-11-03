#include "median_filter_plugin.h"

QString MedianFilterPlugin::description()
{
    return "This plugin applies median blur filters to any image."
           " This plugin's goal is to make us more familiar with the"
           " concept of plugins in general.";
}

void MedianFilterPlugin::processImage(const cv::Mat &t_source, cv::Mat &t_destination)
{
    cv::medianBlur(t_source, t_destination, 5);
}
