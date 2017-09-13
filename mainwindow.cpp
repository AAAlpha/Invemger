#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString dir = QDir::currentPath();
    dir += "/test.db";

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(dir);

    if( !mydb.open() )
        qDebug() << "Failed to connect";
    else
        qDebug() << "Database connected";

    QSqlQuery query;
//    query.exec("create table inventory "
//                  "(id integer primary key, "
//                  "part varchar(20), "
//                  "description varchar(30), "
//                  "quanity integer)");
    // query.exec(" ") returns true if it successfully ran
    if( query.exec("insert into inventory "
               "values (1,'12398n', 'IC 311', 1)") )
        qDebug() << "query success";
    else
        qDebug() << "query failed";



    mydb.close();
    //qDebug() << "Directory: " << dir ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
