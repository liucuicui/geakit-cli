#ifndef GEAKIT_DATA_LOCPROMANAGER
#define GEAKIT_DATA_LOCPROMANAGER

#include <QString>
#include <QList>
#include <QStringList>

#include "git2.h"

class GLocProject;

class GLocProManager
{
  /* 实现对本地项目列表的管理 */
  public:
    explicit GLocProManager();
    ~GLocProManager(){}

    /* 返回项目列表 */
    QList<GLocProject*> projectList();
	QStringList nameList();

    /* 添加特定项目 */
    bool addProject(GLocProject* project);
    bool addProject(QString name, git_repository* repo);
    /* 删除特定项目 */
    bool delProject(GLocProject* project);
    bool delProject(QString name);

	/* 通过项目名获取仓库 */
	git_repository* get_repo_from_name(QString name);

  private:
    QList<GLocProject*> m_projectList;
	QStringList m_nameList;
};

#endif
