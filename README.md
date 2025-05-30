# School Management System
Этот проект представляет собой систему для управления школой с использованием Qt и MariaDB. Приложение предоставляет интерфейс для работы с базой данных, который позволяет добавлять, редактировать и удалять записи о студентах, учителях, классах, предметах и посещаемости.

## Описание

Приложение позволяет управлять следующими данными:

- студентов
- учителей
- классов
- предметов
- оценок
- посещаемости

### Функционал

1. Добавление, редактирование и удаление записей.
2. Отображение данных из таблиц базы данных.
3. Подключение к базе данных MariaDB для хранения информации.

## Технологии

- C++
- Qt
- MariaDB

## Установка

### Предварительные требования

1. **C++ компилятор** (например, `g++`).
2. **Qt** (версии 5.15 или выше).
3. **MariaDB** для хранения данных.

### Установка зависимостей

1. Установите необходимые пакеты:

    ```bash
    sudo pacman -S mariadb-connector-c qt6-base cmake make
    ```

2. Установите MariaDB и создайте базу данных:

    ```bash
    sudo apt install mariadb-server
    mysql -u root -p
    CREATE DATABASE museum_db;
    ```

### Склонируйте репозиторий

1. Склонируйте репозиторий и перейдите в директорию проекта:

    ```bash
    git clone https://github.com/yourusername/museum-app.git
    cd museum-app
    mkdir build
    cd build
    cmake ..
    make
    ./museum_app
    ```