#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <secdialog.h>
#include <QResizeEvent>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    SecDialog *secDialog;
    QPixmap pix_pic;
    QSqlDatabase db;
private:
    void link_db();
};
#endif // MAINWINDOW_H
