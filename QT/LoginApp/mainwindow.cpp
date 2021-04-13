#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <secdialog.h>
#include <QPixmap>
#include <QDebug>
#include <QSvgRenderer>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect enter key with clicked SIGNAL at password label.
    connect(ui->lineEdit_password, SIGNAL(returnPressed()), ui->pushButton_login, SIGNAL(clicked()), Qt::UniqueConnection);
    QSvgRenderer *svgRender = new QSvgRenderer(QString(":/resources/img/login.svg"));
    pix_pic = QPixmap(300, 400);
    pix_pic.fill(Qt::transparent);
    QPainter painter(&pix_pic);
    svgRender->render(&painter);
    // pix_pic = QPixmap(":/resources/img/login.svg");
    link_db();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::link_db()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setDatabaseName("user_info");
    db.setUserName("root");
    db.setPassword("elwgelwg");
    bool ok = db.open();
    if (ok) {
        qInfo() << "datataset link successfully.";
    }
    else{
        qInfo() << "datataset link failed.";
    }
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QSqlQuery query(db);
    query.prepare("SELECT password FROM users WHERE name = :name");
    query.bindValue(":name", username);
    query.exec();

    query.next();
    qInfo() << query.value(0).toString() << endl;

    if (password != "" && password == query.value(0).toString()){
        ui->statusbar->showMessage("Username and password are correct", 5000);
        secDialog = new SecDialog();
        secDialog->show();
    }else{
        ui->statusbar->showMessage("Username and password are not correct", 5000);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    int w = ui->label_pic->width(), h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix_pic.scaled(w/2, h/2, Qt::KeepAspectRatio));
    // qInfo() << w << '\t' << h;
}


