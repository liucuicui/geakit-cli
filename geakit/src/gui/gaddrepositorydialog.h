#ifndef GEAKIT_GUI_GADDREPOSITORYDIALOG_H
#define GEAKIT_GUI_GADDREPOSITORYDIALOG_H

#include <QDialog>

class GLocProManager;

namespace Ui
{
  class GAddRepositoryDialog;
}

class GAddRepositoryDialog:public QDialog
{
  Q_OBJECT

  public:
    explicit GAddRepositoryDialog(QWidget* parent = 0);
    ~GAddRepositoryDialog(){}

    void addRepo(GLocProManager* proManager);

  private:
    void cloneRepo();
    void addCopy();
    void createRepo();

    Ui::GAddRepositoryDialog* ui;
    GLocProManager* m_locProManager;

  private slots:
    void cloneBrowseButtonClicked();
    void addBrowseButtonClicked();
    void createBrowseButtonClicked();
  
};

#endif

