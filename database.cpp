#include "database.h"

Database::Database(const QString& path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }

    QSqlQuery query;

    // Enable FK
    query.exec("PRAGMA foreign_keys = ON;");
}

bool Database::addTag(const QString& tag) {
    QSqlQuery query;

    query.prepare("INSERT INTO `tags` (name) VALUES (:name)");
    query.bindValue(":name", tag);

    bool success = query.exec();
    if (!success) {
        qDebug() << query.lastError();
    }
    return success;
}

bool Database::removeTag(int id) {
    QSqlQuery query;

    query.prepare("DELETE FROM `tags` WHERE id=:id");
    query.bindValue(":id", id);

    bool success = query.exec();
    if (!success) {
        qDebug() << query.lastError();
    }
    return success;
}