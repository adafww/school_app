#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("470211");

    QSqlDatabase tempDb = QSqlDatabase::addDatabase("QMYSQL", "temp_connection");
    tempDb.setHostName("127.0.0.1");
    tempDb.setPort(3306);
    tempDb.setUserName("root");
    tempDb.setPassword("470211");

    if (!tempDb.open()) {
        qDebug() << "Ошибка подключения к MariaDB:" << tempDb.lastError().text();
        return;
    }

    QSqlQuery query(tempDb);
    query.exec("CREATE DATABASE IF NOT EXISTS school1_db;");
    tempDb.close();
    
    db.setDatabaseName("school1_db");
    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе school1_db:" << db.lastError().text();
        return;
    }

    qDebug() << "Подключение к MariaDB успешно!";
    createTables();
    insertTestData();
}

void DatabaseManager::createTables() {
    QSqlQuery query;

    // Создаем таблицу студентов
    if (!query.exec("CREATE TABLE IF NOT EXISTS students ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "name VARCHAR(255), "
                    "age INT, "
                    "class VARCHAR(50))")) {
        qDebug() << "Ошибка при создании таблицы students:" << query.lastError().text();
    }

    // Создаем таблицу учителей
    if (!query.exec("CREATE TABLE IF NOT EXISTS teachers ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "name VARCHAR(255))")) {
        qDebug() << "Ошибка при создании таблицы teachers:" << query.lastError().text();
    }

    // Создаем таблицу классов
    if (!query.exec("CREATE TABLE IF NOT EXISTS classes ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "name VARCHAR(50), "
                    "teacher_id INT, "
                    "FOREIGN KEY (teacher_id) REFERENCES teachers(id) ON DELETE SET NULL)")) {
        qDebug() << "Ошибка при создании таблицы classes:" << query.lastError().text();
    }

    // Создаем таблицу предметов
    if (!query.exec("CREATE TABLE IF NOT EXISTS subjects ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "name VARCHAR(255), "
                    "teacher_id INT, "
                    "FOREIGN KEY (teacher_id) REFERENCES teachers(id) ON DELETE SET NULL)")) {
        qDebug() << "Ошибка при создании таблицы subjects:" << query.lastError().text();
    }

    // Создаем таблицу оценок
    if (!query.exec("CREATE TABLE IF NOT EXISTS grades ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "student_id INT, "
                    "subject_id INT, "
                    "grade INT, "
                    "FOREIGN KEY (student_id) REFERENCES students(id) ON DELETE CASCADE, "
                    "FOREIGN KEY (subject_id) REFERENCES subjects(id) ON DELETE CASCADE)")) {
        qDebug() << "Ошибка при создании таблицы grades:" << query.lastError().text();
    }

    // Создаем таблицу посещаемости
    if (!query.exec("CREATE TABLE IF NOT EXISTS attendance ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "student_id INT, "
                    "date DATE, "
                    "status VARCHAR(20), "
                    "FOREIGN KEY (student_id) REFERENCES students(id) ON DELETE CASCADE)")) {
        qDebug() << "Ошибка при создании таблицы attendance:" << query.lastError().text();
    }
}


void DatabaseManager::insertTestData() {
    QSqlQuery query;

    // Проверяем, есть ли студенты, если есть — данные уже загружены
    query.exec("SELECT COUNT(*) FROM students");
    if (query.next() && query.value(0).toInt() > 0) return;

    // Добавляем студентов
    query.exec("INSERT INTO students (name, age, class) VALUES ('Иван Петров', 14, '9A'), ('Мария Иванова', 13, '8B')");

    // Добавляем учителей
    query.exec("INSERT INTO teachers (name) VALUES ('Алексей Смирнов'), ('Ольга Петрова')");

    // Добавляем классы
    query.exec("INSERT INTO classes (name, teacher_id) VALUES ('9A', 1), ('8B', 2)");

    // Добавляем предметы
    query.exec("INSERT INTO subjects (name, teacher_id) VALUES ('Математика', 1), ('История', 2)");

    // Добавляем оценки
    query.exec("INSERT INTO grades (student_id, subject_id, grade) VALUES (1, 1, 5), (1, 2, 4), (2, 1, 3), (2, 2, 5)");

    // Добавляем посещаемость
    query.exec("INSERT INTO attendance (student_id, date, status) VALUES (1, '2025-03-25', 'Присутствовал'), (2, '2025-03-25', 'Отсутствовал')");
}
