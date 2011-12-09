#ifndef GEAKIT_GUI_GMAINWINDOW_H
#define GEAKIT_GUI_GMAINWINDOW_H

#include <QMainWindow>

class QMenu;
class QAction;
class QCloseEvent;
class GAccount;
class GLocProManager;

namespace Ui
{
  class GMainWindow;
}

class GMainWindow :public QMainWindow
{
  Q_OBJECT
  public:
    explicit GMainWindow(QWidget* parent = 0);
    ~GMainWindow();

  protected:
    void closeEvent (QCloseEvent * event);

  private:
    Ui::GMainWindow* ui;
    QMenu* fileMenu;
    QMenu* editMenu;
    QAction* settingsAction;
    QAction* addRepositoryAction;

    GAccount* m_account;
    GLocProManager* m_locProManager;
  
  private slots:
    void onSettingsActionTriggered();
    void onAddRepositoryActionTriggered();

  private:
    void setupMenus();
    void setupActions();
    void loadSettings();
    void saveSettings();
	void loadProjectList();
};

#endif
