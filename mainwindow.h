#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* timer;

    QVector<QChar> current_string;
    QString current_char;
    int current_pos = 0;
    QVector<QString> comand;

    bool step_or_no = false;

    bool start = false;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void time_step();

    void on_pushButton_3_clicked();

    void save_comand();

    void on_horizontalSlider_valueChanged(int value);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
