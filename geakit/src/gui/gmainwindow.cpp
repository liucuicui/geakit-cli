#include "gmainwindow.h"
#include "ui_gmainwindow.h"
#include "gsettingsdialog.h"
#include "gaddrepositorydialog.h"
#include "data/locpromanager.h"
#include "data/account.h"

#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QCloseEvent>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QStringList>

GMainWindow::GMainWindow(QWidget* parent):QMainWindow(parent), ui(new Ui::GMainWindow)
{
  ui->setupUi(this);
  setupActions();
  setupMenus();
  loadSettings();
  m_locProManager = new GLocProManager;
  loadProjectList();
}

// 点击设置按钮，弹出设置对话框
void GMainWindow::onSettingsActionTriggered()
{
  GSettingsDialog* dlg = new GSettingsDialog(this);
  dlg->accountSetUsername(m_account->username());
  dlg->accountSetPassword(m_account->password());

  if(dlg->exec())//判断是否保存用户信息的修改
  {
    m_account->setUsername(dlg->accountUsername());
    m_account->setPassword(dlg->accountPassword());
  }
  delete dlg;
}

void GMainWindow::onAddRepositoryActionTriggered()
{
  GAddRepositoryDialog* dlg = new GAddRepositoryDialog(this);

  if(dlg->exec())
  {
   dlg->addRepo(m_locProManager); 
  }
  delete dlg;
  loadProjectList();
}

 //创建菜单
void GMainWindow::setupMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(addRepositoryAction);
  editMenu = menuBar()->addMenu(tr("&Edit"));//增加编辑菜单
  editMenu->addAction(settingsAction);
}

// 创建按钮
void GMainWindow::setupActions()
{
  settingsAction = new QAction(tr("Settings"), this);//增加设置按钮
  settingsAction->setIcon(QIcon(":icons/action_settings.png"));
  settingsAction->setShortcut(Qt::CTRL + Qt::Key_Comma);
  settingsAction->setStatusTip(tr("Settings of Geakit Clinet"));
  connect(settingsAction, SIGNAL(triggered()), this, SLOT(onSettingsActionTriggered()));

  addRepositoryAction = new QAction(tr("AddRepository"),this);
  addRepositoryAction->setIcon(QIcon(":icons/action_addRepository.png"));
  addRepositoryAction->setShortcut(Qt::CTRL + Qt::Key_A);
  addRepositoryAction->setStatusTip(tr("AddRespository of Geakit Clinet"));
  connect(addRepositoryAction,SIGNAL(triggered()),this,SLOT(onAddRepositoryActionTriggered()));
}

// 载入用户信息
void GMainWindow::loadSettings(){
  QSettings settings("geakit.com", "Geakit");
  m_account = new GAccount;
  m_account->setUsername(settings.value("account/username", "").toString());
  m_account->setPassword(settings.value("account/password", "").toString());
}

// 保存用户信息
void GMainWindow::saveSettings(){
  QSettings settings("geakit.com", "Geakit");
  settings.beginGroup("account");
  settings.setValue("username", m_account->username());
  settings.setValue("password", m_account->password());
  settings.endGroup();
}

//关闭窗口
void GMainWindow::closeEvent(QCloseEvent* event){
  saveSettings();
  event->accept();
}

//
void GMainWindow::loadProjectList()
{
  QAbstractItemModel* model = new QStringListModel(m_locProManager->nameList());
	ui->projectListView->setModel(model);
}

GMainWindow::~GMainWindow()
{
  delete m_locProManager;
}
