#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_decide_fate_clicked();

private:
    Ui::MainWindow *ui;

    int dice_type[7] = {4, 6, 8, 10, 12, 20, 100};

    int tos_coords[6][2] = {{20, 10}, {480, 350}, {40, 310}, {150, 530}, {500, 20}, {20, 130}};

    bool tos_agreed();

    int roll_dice();

    void load_progress_bar();

    void mess_with_tos();
};
#endif // MAINWINDOW_H
