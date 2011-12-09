#ifndef GEAKIT_DATA_LOCPROJECT
#define GEAKIT_DATA_LOCPROJECT

#include "git2.h"

#include <QString>
class GAccount;

class GLocProject
{
  /* 项目类 */
  public:
    explicit GLocProject();
    explicit GLocProject(QString name, git_repository* repo, GAccount* account);
    ~GLocProject(){}

    GAccount* account(){return m_account;}
    const QString name() {return m_name;}
    bool setName(const QString name);
    git_repository* repo() {return m_repo;}
    bool setRepo(git_repository* repo);

  private:
    GAccount* m_account;
    QString m_name;
    git_repository* m_repo;
};

#endif
