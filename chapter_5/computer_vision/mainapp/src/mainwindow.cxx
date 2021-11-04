#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QLibrary>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *t_parent) :
    QMainWindow(t_parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
    populatePluginsMenu();
    populateLanguagesMenu();
    populateThemesMenu();
    ui->graphicsView->setScene(&m_scene);
    m_scene.addItem(&m_original_pixmap);
    m_scene.addItem(&m_processed_pixmap);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete m_current_plugin;
    delete ui;
}

void MainWindow::loadSettings()
{
    QSettings settings("Packt", "Computer_Vision", this);
    m_current_theme_file = settings.value("currentThemeFile", "").toString();
    m_current_language_file = settings.value("currentLanguageFile", "").toString();
    m_current_plugin_file = settings.value("currentPluginFile", "").toString();
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt", "Computer_Vision", this);
    settings.setValue("currentThemeFile", m_current_theme_file);
    settings.setValue("currentLanguageFile", m_current_language_file);
    settings.setValue("currentPluginFile", m_current_plugin_file);
}

void MainWindow::changeEvent(QEvent *t_event)
{
    if(t_event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    else
        QMainWindow::changeEvent(t_event);
}

void MainWindow::closeEvent(QCloseEvent *t_event)
{
    int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to exit?"), QMessageBox::Yes, QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        saveSettings();
        t_event->accept();
    }
    else
    {
        t_event->ignore();
    }
}

void MainWindow::populatePluginsMenu()
{
    QDir plugins_dir(qApp->applicationDirPath() + PLUGINS_SUBFOLDER);
    QFileInfoList plugin_files = plugins_dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo plugin_file, plugin_files)
    {
        if(QLibrary::isLibrary(plugin_file.absoluteFilePath()))
        {
            QPluginLoader plugin_loader(plugin_file.absoluteFilePath(), this);
            if(CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(plugin_loader.instance()))
            {
                QAction *plugin_action = ui->menu_Plugins->addAction(plugin->title());
                plugin_action->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, plugin_file.absoluteFilePath());
                connect(plugin_action, SIGNAL(triggered(bool)), this, SLOT(onPluginActionTriggered(bool)));
                if(m_current_plugin_file == plugin_file.absoluteFilePath())
                    plugin_action->trigger();
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString(tr("Make sure %1 is a correct plugin for this application<br>"
                                                "and it's not in use by some other application!")).arg(plugin_file.fileName()));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),
                                 QString(tr("Make sure only plugins exist in %1 folder.<br>"
                                            "%2 is not a plugin."))
                                 .arg(PLUGINS_SUBFOLDER)
                                 .arg(plugin_file.fileName()));
        }
    }

    if(ui->menu_Plugins->actions().count() <= 0)
    {
        QMessageBox::critical(this, tr("No Plugins"), QString(tr("This application cannot work without plugins!"
                                                                 "<br>Make sure that %1 folder exists "
                                                                 "in the same folder as the application<br>and that "
                                                                 "there are some filter plugins inside it")).arg(PLUGINS_SUBFOLDER));
        this->setEnabled(false);
    }
}

void MainWindow::populateLanguagesMenu()
{
    QMenu *languages_menu = new QMenu(this);
    QAction *default_language_action = languages_menu->addAction("English - US");
    default_language_action->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
    connect(default_language_action, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));
    QDir languages_dir(qApp->applicationDirPath() + LANGUAGES_SUBFOLDER);
    QFileInfoList language_files = languages_dir.entryInfoList(QStringList() << "*.qm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo language_file, language_files)
    {
        QAction *language_action = languages_menu->addAction(language_file.baseName());
        language_action->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, language_file.absoluteFilePath());
        connect(language_action, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));
        if(m_current_language_file == language_file.absoluteFilePath())
            language_action->trigger();
    }
    ui->actionLanguage->setMenu(languages_menu);
}

void MainWindow::populateThemesMenu()
{
    QMenu *themes_menu = new QMenu(this);
    QAction *default_theme_action = themes_menu->addAction("Default");
    default_theme_action->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
    connect(default_theme_action, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));
    QDir themes_dir(qApp->applicationDirPath() + THEMES_SUBFOLDER);
    QFileInfoList theme_files = themes_dir.entryInfoList(QStringList() << "*.thm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo theme_file, theme_files)
    {
        QAction *theme_action = themes_menu->addAction(theme_file.baseName());
        theme_action->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, theme_file.absoluteFilePath());
        connect(theme_action, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));
        if(m_current_theme_file == theme_file.absoluteFilePath())
            theme_action->trigger();
    }
    ui->actionTheme->setMenu(themes_menu);
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::onPluginActionTriggered(bool)
{
    if(!m_current_plugin.isNull())
    {
        delete m_current_plugin;
        delete m_current_plugin_gui;
    }
    m_current_plugin_file = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    m_current_plugin = new QPluginLoader(m_current_plugin_file, this);
    m_current_plugin_gui = new QWidget(this);
    ui->pluginLayout->addWidget(m_current_plugin_gui);
    CvPluginInterface *current_plugin_instance = dynamic_cast<CvPluginInterface*>(m_current_plugin->instance());
    if(current_plugin_instance)
    {
        current_plugin_instance->setupUi(m_current_plugin_gui);
        connect(m_current_plugin->instance(), SIGNAL(updateNeeded()), this, SLOT(onCurrentPluginUpdateNeeded()));
        connect(m_current_plugin->instance(), SIGNAL(infoMessage(QString)), this, SLOT(onCurrentPluginInfoMessage(QString)));
        connect(m_current_plugin->instance(), SIGNAL(errorMessage(QString)), this, SLOT(onCurrentPluginErrorMessage(QString)));
    }
}

void MainWindow::onLanguageActionTriggered(bool)
{
    m_current_language_file = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    qApp->removeTranslator(&m_translator);
    if(!m_current_language_file.isEmpty())
    {
        bool ok = m_translator.load(m_current_language_file);
        qDebug() << "Translator is loaded = " << ok;
        qApp->installTranslator(&m_translator);
        ui->retranslateUi(this);
    }
}

void MainWindow::onThemeActionTriggered(bool)
{
    m_current_theme_file = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    QFile theme_file(m_current_theme_file);
    if(m_current_theme_file.isEmpty())
    {
        qApp->setStyleSheet("");
    }
    else
    {
        theme_file.open(QFile::ReadOnly | QFile::Text);
        QString style_sheet = theme_file.readAll();
        qApp->setStyleSheet(style_sheet);
        theme_file.close();
    }
}

void MainWindow::on_actionOpenImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Input Image"),
                                                    QDir::currentPath(),
                                                    tr("Images") + " (*.jpg *.png *.bmp)");
    m_original_mat = cv::imread(filename.toStdString());
    if (!m_original_mat.empty())
        onCurrentPluginUpdateNeeded();
    else if(!filename.trimmed().isEmpty())
        QMessageBox::critical(this, tr("Error"), tr("Make sure the image file exists and it is accessible!"));
}

void MainWindow::on_viewOriginalCheck_toggled(bool t_is_checked)
{
    m_original_pixmap.setVisible(t_is_checked);
    m_processed_pixmap.setVisible(!t_is_checked);
}

void MainWindow::onCurrentPluginUpdateNeeded()
{
    if (!m_original_mat.empty())
    {
        if (!m_current_plugin.isNull())
        {
            CvPluginInterface *current_plugin_instance = dynamic_cast<CvPluginInterface*>(m_current_plugin->instance());
            if (current_plugin_instance)
            {
                cv::TickMeter meter;
                meter.start();
                current_plugin_instance->processImage(m_original_mat, m_processed_mat);
                meter.stop();
                qDebug() << "The process took " << meter.getTimeMilli() << "milliseconds";
            }
        }
        else
        {
            m_processed_mat = m_original_mat.clone();
        }
        m_original_image = QImage(m_original_mat.data, m_original_mat.cols, m_original_mat.rows, m_original_mat.step, QImage::Format_RGB888);
        m_original_pixmap.setPixmap(QPixmap::fromImage(m_original_image.rgbSwapped()));
        m_processed_image = QImage(m_processed_mat.data, m_processed_mat.cols, m_processed_mat.rows, m_processed_mat.step, QImage::Format_RGB888);
        m_processed_pixmap.setPixmap(QPixmap::fromImage(m_processed_image.rgbSwapped()));
    }
}

void MainWindow::on_actionSaveImage_triggered()
{
    if (!ui->viewOriginalCheck->isChecked() && !m_processed_mat.empty())
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
        if(!filename.isEmpty())
            cv::imwrite(filename.toStdString(), m_processed_mat);
    }
    else if (ui->viewOriginalCheck->isChecked() && !m_original_mat.empty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
        if (!fileName.isEmpty())
            cv::imwrite(fileName.toStdString(), m_original_mat);
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("There is nothing to be saved!"));
    }
}

void MainWindow::onCurrentPluginErrorMessage(const QString &t_message)
{
    qDebug() << "Plugin Error Message : " << t_message;
}

void MainWindow::onCurrentPluginInfoMessage(const QString &t_message)
{
    qDebug() << "Plugin Info Message : " << t_message;
}

void MainWindow::on_action_Camera_triggered()
{

}
