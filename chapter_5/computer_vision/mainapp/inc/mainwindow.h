#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPluginLoader>
#include <QTranslator>
#include <QGraphicsPixmapItem>
#include "cvplugininterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *t_parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *t_event) override;
    void changeEvent(QEvent *t_event) override;

private:
    Ui::MainWindow *ui;
    QString m_current_theme_file;
    QString m_current_language_file;
    QString m_current_plugin_file;
    QPointer<QPluginLoader> m_current_plugin;
    QPointer<QWidget> m_current_plugin_gui;
    QGraphicsScene m_scene;
    QTranslator m_translator;
    QGraphicsPixmapItem m_original_pixmap;
    QGraphicsPixmapItem m_processed_pixmap;
    cv::Mat m_original_mat;
    cv::Mat m_processed_mat;
    QImage m_original_image;
    QImage m_processed_image;
    const char* PLUGINS_SUBFOLDER = "/cvplugins/";
    const char* LANGUAGES_SUBFOLDER = "/languages/";
    const char* THEMES_SUBFOLDER = "/themes/";
    const char* FILE_ON_DISK_DYNAMIC_PROPERTY = "absolute_file_path";

    void loadSettings();
    void saveSettings();
    void populatePluginsMenu();
    void populateLanguagesMenu();
    void populateThemesMenu();

private slots:
    void onPluginActionTriggered(bool);
    void onLanguageActionTriggered(bool);
    void onThemeActionTriggered(bool);
    void onCurrentPluginUpdateNeeded();
    void onCurrentPluginErrorMessage(const QString &t_message);
    void onCurrentPluginInfoMessage(const QString &t_message);
    void on_actionAboutQt_triggered();
    void on_actionExit_triggered();
    void on_actionOpenImage_triggered();
    void on_viewOriginalCheck_toggled(bool t_is_checked);
    void on_actionSaveImage_triggered();
    void on_action_Camera_triggered();
};

#endif // MAINWINDOW_H
