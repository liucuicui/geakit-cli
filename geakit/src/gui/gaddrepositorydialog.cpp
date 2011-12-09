#include "ui_gaddrepositorydialog.h"

#include "gaddrepositorydialog.h"

#include "git2.h"

#include <QUrl>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include "data/locpromanager.h"

GAddRepositoryDialog::GAddRepositoryDialog(QWidget* parent):QDialog(parent),ui(new Ui::GAddRepositoryDialog)
{
  ui->setupUi(this);
  connect(ui->cloneBrowseButton, SIGNAL(clicked()), this, SLOT(cloneBrowseButtonClicked()));
  connect(ui->addBrowseButton,SIGNAL(clicked()),this,SLOT(addBrowseButtonClicked()));
  connect(ui->createBrowseButton,SIGNAL(clicked()),this,SLOT(createBrowseButtonClicked()));
}

void GAddRepositoryDialog::addRepo(GLocProManager* proManager)
{
  m_locProManager = proManager;
  switch (ui->tabWidget->currentIndex())
  {
    case 0:
      cloneRepo();
      break;
    case 1:
      addCopy();
      break;
    case 2:
      createRepo();
      break;
    default:
      //TODO do something error
      break;
  }
}

void GAddRepositoryDialog::cloneRepo()
{
  //TODO
}

void GAddRepositoryDialog::addCopy()
{
  QString path = ui->addPathEdit->text();
  QString repo_path = path + "/.git";
  if(QDir(path).exists())
  {
    if(QDir(repo_path).exists())
    {
      git_repository* repo;
      int error = git_repository_open(&repo, repo_path.toAscii());
      if (error==GIT_SUCCESS)
      {
        m_locProManager->addProject(ui->addNameEdit->text(), repo);
        QMessageBox::critical(this, tr("Add Repository Success"), tr("The repository you specified has been added successfully!"), QMessageBox::Ok);
      }
      else
      {
        repo = NULL;
        //TODO 解析错误码，提示相应信息
        QMessageBox::critical(this, tr("Add Repository Error"), tr("Errors occured"), QMessageBox::Ok);
      }
    }
  }
  else
  {
    QMessageBox::critical(this, tr("Add Repository Error"), tr("The directory you specified does not exist!"), QMessageBox::Ok);
  }
}

void GAddRepositoryDialog::createRepo()
{
  QString path = ui->createPathEdit->text();
  QString name = ui->createNameEdit->text();
  QString repo_path = path+"/"+name;
  if(QDir(repo_path).exists() && QDir(repo_path+"/.git").exists())
  {
    QMessageBox::critical(this,tr("Create Repository Error"), tr("The directory already existed and is a git repository, you can change your directory or give another name. \n if you want to manage your existing repository, just use add copy."), QMessageBox::Ok);
  }
  else
  {
    git_repository* repo;
    int error = git_repository_init(&repo, repo_path.toAscii(), false);
    if (error == GIT_SUCCESS)
    {
		m_locProManager->addProject(name, repo);
		QMessageBox::critical(this,tr("Create Repository Success"),tr("Create repository successfully!"), QMessageBox::Ok);
	}
	else
	{
		repo = NULL;
		//TODO 解析错误码，提示相应信息
	}
  }
}

void GAddRepositoryDialog::cloneBrowseButtonClicked()
{
    ui->clonePathEdit->setText(QFileDialog::getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks));
}

void GAddRepositoryDialog::addBrowseButtonClicked()
{
    ui->addPathEdit->setText(QFileDialog::getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks));
}

void GAddRepositoryDialog::createBrowseButtonClicked()
{
    ui->createPathEdit->setText(QFileDialog::getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks));
}
