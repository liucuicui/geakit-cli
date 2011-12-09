#include "locproject.h"

GLocProject::GLocProject()
{
	m_account = NULL;
	m_name = "";
	m_repo = NULL;
}

GLocProject::GLocProject(QString name, git_repository* repo, GAccount* account)
{
	m_name = name;
	m_repo = repo;
	m_account = account;
}

bool GLocProject::setName(const QString name)
{
	m_name = name;
	return true;
}

bool GLocProject::setRepo(git_repository* repo)
{
	m_repo = repo;
	return true;
}
