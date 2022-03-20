#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    ui->decrease_bar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_decide_fate_clicked()
{
    if (!tos_agreed()) return;

    load_progress_bar();
    ui->result->display(roll_dice());
    mess_with_tos();
}

bool MainWindow::tos_agreed() {
    if (ui->terms_of_service->checkState() == Qt::CheckState::Checked) return true;

    QMessageBox msg_box;
    msg_box.setText("you must agree with the terms of service");
    msg_box.exec();
    return false;
}

int MainWindow::roll_dice() {
    int dice_count[] = {
        ui->d4box->value(),
        ui->d6box->value(),
        ui->d8box->value(),
        ui->d10box->value(),
        ui->d12box->value(),
        ui->d20box->value(),
        ui->d100box->value(),
    };

    int sum = 0;

    for (int i = 0; i < 7; i++) {
        int type = dice_type[i];
        int count = dice_count[i];

        for (int e = 0; e < count; e++) {
            // ten sided die has values 0..9
            int inc = type == 10 ? 0 : 1;
            int roll = rand() % type + inc;
            sum += roll;
        }
    }
    return sum;
}

void MainWindow::load_progress_bar() {
    for (int i = 0; i <= 100; i++) {
        QThread::msleep(rand() % 200 + 100);
        ui->decrease_bar->setValue(i);
    }
}

void MainWindow::mess_with_tos() {
    ui->terms_of_service->setCheckState(Qt::CheckState::Unchecked);

    int rand_coords = rand() % 6;
    ui->terms_of_service->move(tos_coords[rand_coords][0], tos_coords[rand_coords][1]);
}
