#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include <QDebug>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent)//заменить пробелы красить код текстэдит
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(time_step()));

    //on_horizontalSlider_valueChanged(ui->horizontalSlider->value());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->label->setText(arg1);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString str1 = QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.txt");

    QFile file(str1);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            str=str+file.readLine();
        }
        ui->textEdit->setText(str);
        file.close();
    }

}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="Пауза"){
       // ui->horizontalSlider->setEnabled(false);
        timer->stop();
        ui->pushButton_3->setEnabled(true);
        step_or_no = true;
        ui->pushButton->setText("Продолжить");
        return;
    }
    if(ui->pushButton->text()=="Продолжить"){
        ui->pushButton->setText("Пауза");
        ui->pushButton_3->setEnabled(false);
      //  ui->horizontalSlider->setEnabled(true);
      //  timer->start(ui->horizontalSlider->value());
        return;
    }


    save_comand();
    start = true;
    //ui->pushButton->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton->setText("Пауза");

//    QString two = ui->label->text();
//    two = two.remove(0,1);
    //ui->label->setText("<font color = red>"+one+"</font>"+"<font color = #000000>"+two+"</font>");


    timer->start(50);
    //<font color = #545454>

}

void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
    start = false;
    ui->pushButton->setText("Старт");
  //  ui->horizontalSlider->setEnabled(true);
    ui->label->setText(ui->lineEdit->text());
    ui->pushButton->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    comand.clear();
    current_string.clear();
    step_or_no = false;
    ui->label_6->setText("0");
    ui->label_7->setText("0");

    QTextCharFormat fmtback;
    fmtback.setForeground(Qt::black);
    fmtback.setFontWeight(QFont::Medium);
    QTextCursor cursorback(ui->textEdit->document());
    cursorback.setPosition(0, QTextCursor::MoveAnchor);
    cursorback.setPosition(ui->textEdit->toPlainText().length(), QTextCursor::KeepAnchor);
    cursorback.setCharFormat(fmtback);



}

void MainWindow::time_step()
{
    bool chec_invalid_end = true;

    for (int i = 0;i<comand.size();i++) {
        chec_invalid_end = true;
        QString condition = ui->label_6->text();
        QStringList part_comand = comand.at(i).split(QRegExp("\\s+"),QString::SkipEmptyParts);
//        for (int j = 0;j<part_comand.size();j++) {
//            if(part_comand.at(j)=="_"){
//                part_comand[j] = " ";
//            }
//        }
        QStringList part_comand2 = comand.at(i).split(QRegExp("\\s+"),QString::SkipEmptyParts);

        if((condition == part_comand[0])&&(current_char == part_comand[1])){
            current_string[current_pos] = part_comand[2][0];

            QTextCharFormat fmtback;
            fmtback.setForeground(Qt::black);
            fmtback.setFontWeight(QFont::Medium);
            QTextCursor cursorback(ui->textEdit->document());
            cursorback.setPosition(0, QTextCursor::MoveAnchor);
            cursorback.setPosition(ui->textEdit->toPlainText().length(), QTextCursor::KeepAnchor);
            cursorback.setCharFormat(fmtback);

            QTextCharFormat fmt;
            fmt.setForeground(Qt::blue);
            fmt.setFontWeight(QFont::DemiBold);
            QTextCursor cursor(ui->textEdit->document());
            QString str1 = ui->textEdit->toPlainText();
            QString str2 = part_comand2[0]+" "+part_comand2[1]+" "+part_comand2[2]+" "+part_comand2[3]+" "+part_comand2[4];
            int begin = str1.indexOf(str2);
            qDebug()<<begin;
            cursor.setPosition(begin, QTextCursor::MoveAnchor);
            cursor.setPosition(begin+str2.length(), QTextCursor::KeepAnchor);
            cursor.setCharFormat(fmt);

            if(part_comand.at(3)=="r"){
                current_pos++;
            }
            if(part_comand.at(3)=="l"){
                current_pos--;
            }
            if(current_pos>=current_string.size()){
                current_string.push_back('_');
            }
            if(current_pos<0){
                current_pos = 0;
                current_string.push_front('_');
            }
            ui->label->setText("");

            for (int g = 0;g<current_string.size();g++) {
                if(g==current_pos){
                    //ui->label->setText(ui->label->text()+"<span style=background:#FFFFFF>"+current_string.at(g)+"</span>");
                    ui->label->setText(ui->label->text()+"<font color = red>"+current_string.at(g)+"</font>");
                }
                else{
                    //ui->label->setText(ui->label->text()+"<font color = #000000>"+current_string.at(g)+"</font>");
                    ui->label->setText(ui->label->text()+"<font color = #000000>"+current_string.at(g)+"</font>");
                }
            }
            current_char = current_string[current_pos];
            ui->label_6->setText(part_comand.at(4));

            //qDebug()<<current_pos<<current_char<<current_string;
            chec_invalid_end = false;
            break;

        }

    }

    if(chec_invalid_end){
        //qDebug()<<"vse";
        timer->stop();
        start = false;
        ui->label->setText("");
        for (int g = 0;g<current_string.size();g++) {
            ui->label->setText(ui->label->text()+"<font color = #000000>"+current_string.at(g)+"</font>");
        }
        ui->pushButton_3->setEnabled(false);
        ui->pushButton->setEnabled(false);
        return;
    }

    int step = ui->label_7->text().toInt();
    ui->label_7->setNum(++step);
    //qDebug()<<"time";

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton->setText("Продолжить");
    ui->pushButton_4->setEnabled(false);
    //ui->pushButton->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    if(!step_or_no){
       // ui->horizontalSlider->setEnabled(false);
        save_comand();
        start = true;
        step_or_no = true;
    }
    time_step();
}

void MainWindow::save_comand()
{
    comand.clear();
    QStringList list = ui->textEdit->toPlainText().split("\n");

    foreach (QString l, list) {
        if ((l[0]=='/'&&l[1]=='/')||l[0]==';'){
            continue;
        }
        QStringList symvol = l.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        if (symvol.size()==5){
            comand.push_back(symvol.at(0)+" "+symvol.at(1)+" "+symvol.at(2)+" "+symvol.at(3)+" "+symvol.at(4));
        }
    }
    foreach (QString l, comand) {
        qDebug()<<l;
    }

    QCharRef one = ui->label->text()[0];
    current_char = one;
    current_pos = 0;
    for (int i = 0;i<ui->label->text().length();i++) {
        current_string.push_back(ui->label->text().at(i));
    }
}








void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_9->setNum(value);
    if(start){
       timer->stop();
       timer->start(value);
    }
}


