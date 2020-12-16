#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database {
   public:
    Database(const QString& path);

    bool addTag(const QString& tag);
    bool removeTag(int id);

   private:
    QSqlDatabase m_db;
};

#endif