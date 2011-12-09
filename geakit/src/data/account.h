#ifndef GEAKIT_DATA_ACCOUNT
#define GEAKIT_DATA_ACCOUNT

#include <QString>

class GAccount {
  public:
    GAccount (){ m_username = m_password = "";}
    GAccount (QString username, QString password);
    virtual ~GAccount (){}

    QString username () { return m_username;}
    void setUsername (QString username) {m_username = username;}
    QString password () {return m_password;}
    void setPassword (QString password) {m_password = password;}

  private:
    QString m_username;
    QString m_password;
};


#endif /* end of include guard: GEAKIT_DATA_ACCOUNT */
