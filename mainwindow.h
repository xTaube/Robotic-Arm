#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listView_indexesMoved(const QModelIndexList &indexes);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
