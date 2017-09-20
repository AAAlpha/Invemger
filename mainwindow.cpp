#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    Variables intialised
    QString dir = QDir::currentPath();
    dir += "/test.db";
//    qDebug() << "Directory: " << dir ;

    //    Set the database to use SQLite and the directory
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(dir);

//    Place this here as you need to configure the DB before pointing it to the query
    QSqlQuery query(mydb);

    //    Check if the database could open
    if( !mydb.open() )
        qDebug() << "Failed to connect";
    else
        qDebug() << "Database connected";

    //    If the table does not exist, make one
    query.prepare("CREATE TABLE inventory "
                  "(id integer primary key, "
                  "part varchar(20), "
                  "description varchar(30), "
                  "quanity integer)");

    //    query.exec(" ") returns true if it successfully ran
    if ( query.exec() )
        qDebug() << "Created table";
    else
        qDebug() << "No table created";

    //    Signals and Slots
    connect(ui->pushButton, SIGNAL (released()), this, SLOT (handleButton()) );
}

void MainWindow::handleButton()
{
    qDebug() << "button pressed";

    QSqlQuery query(mydb);

    query.prepare("INSERT INTO inventory (part, description, quanity) "
                  "VALUES (:part, :descrip, :quant)" );
    query.bindValue(":part", "MSP430");
    query.bindValue(":descrip", "MCU");
    query.bindValue(":quant", 1);

    if ( query.exec() )
        qDebug() << "query success";
    else
        qDebug() << "query failed";
}

MainWindow::~MainWindow()
{
    qDebug() << "closed database";
    mydb.close();
    delete ui;
}
