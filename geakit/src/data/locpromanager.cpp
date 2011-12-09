#include "locpromanager.h"
#include "locproject.h"

GLocProManager::GLocProManager()
{
}

QList<GLocProject*> GLocProManager::projectList()
{
	return m_projectList;
}

QStringList GLocProManager::nameList()
{
	QStringList out;
	for(int i=0; i<m_projectList.size(); i++)
	{
		out.append(m_projectList.at(i)->name());
	}
	m_nameList = out;
	return out;
}

bool GLocProManager::addProject(GLocProject* project)
{
	m_projectList.append(project);
	return true;
}

bool GLocProManager::addProject(QString name, git_repository* repo)
{
	GLocProject* project = new GLocProject;
	project->setName(name);
	project->setRepo(repo);
	this->addProject(project);
	return true;
}

bool GLocProManager::delProject(GLocProject* project)
{
	return m_projectList.removeOne(project);
}

bool GLocProManager::delProject(QString name)
{
	if(m_nameList.contains(name))
	{
		m_projectList.removeAt(m_nameList.indexOf(name));
    return true;
	}
	return false;
}

git_repository* GLocProManager::get_repo_from_name(QString name)
{
	if(m_nameList.contains(name))
	{
		return m_projectList.at(m_nameList.indexOf(name))->repo();
	}
	return NULL;
}
