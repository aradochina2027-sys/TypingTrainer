#include "typingtrainer.h"
#include "ui_typingtrainer.h"
#include <QKeyEvent>

TypingTrainer::TypingTrainer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TypingTrainer) {
    ui->setupUi(this);

    ui->comboLesson->addItems({
        "Basic Keys (ASDF JKL;)",
        "Top Row (QWER UIOP)",
        "Bottom Row (ZXCV M,./)",
        "Numbers (1234 5678)"
    });

    setupKeyboard();
    ui->stackScreens->setCurrentIndex(0);
}

TypingTrainer::~TypingTrainer() {
    delete ui;
}

void TypingTrainer::setupKeyboard() {
    QStringList rows = {"1,2,3,4,5,6,7,8,9,0", "Q,W,E,R,T,Y,U,I,O,P", "A,S,D,F,G,H,J,K,L", "Z,X,C,V,B,N,M"};
    for (int i = 0; i < rows.size(); ++i) {
        QStringList keys = rows[i].split(",");
        for (int j = 0; j < keys.size(); ++j) {
            QPushButton* btn = new QPushButton(keys[j]);
            btn->setMinimumSize(40, 40);
            ui->layoutGridKeyboard->addWidget(btn, i, j);
        }
    }
}

void TypingTrainer::loadLesson(int index) {
    QVector<QString> lessons = {
        "asdf jkl; asdf jkl; asdf jkl;",
        "qwer uiop qwer uiop qwer uiop",
        "zxcv m,./ zxcv m,./ zxcv m,./",
        "1234 5678 1234 5678 1234 5678"
    };
    currentText = lessons.at(index);
    currentIndex = 0;
    errorCount = 0;
    updateDisplay();
}

void TypingTrainer::updateDisplay() {
    QString typed = "<span style='color:green;'>" + currentText.left(currentIndex) + "</span>";
    QString current = "<span style='background-color:yellow; font-weight:bold;'>" + QString(currentText.at(currentIndex)) + "</span>";
    QString remaining = currentText.mid(currentIndex + 1);

    ui->textDisplay->setHtml(typed + current + remaining);

    int progress = (currentIndex * 100) / currentText.length();
    ui->progressTraining->setValue(progress);
}

void TypingTrainer::keyPressEvent(QKeyEvent *event) {
    if (ui->stackScreens->currentIndex() != 1) return;

    QString keyText = event->text();
    if (keyText.isEmpty()) return;

    if (keyText == currentText.at(currentIndex)) {
        currentIndex++;
        if (currentIndex >= currentText.length()) {
            finishSession();
        } else {
            updateDisplay();
        }
    } else {
        errorCount++;
    }
}

void TypingTrainer::finishSession() {
    ui->stackScreens->setCurrentIndex(2);
    ui->resTime->setText("Errors: " + QString::number(errorCount));
    ui->resAccuracy->setText("Completed!");
}

void TypingTrainer::on_btnStart_clicked() {
    loadLesson(ui->comboLesson->currentIndex());
    ui->stackScreens->setCurrentIndex(1);
}

void TypingTrainer::on_btnRestart_clicked() {
    loadLesson(ui->comboLesson->currentIndex());
    ui->stackScreens->setCurrentIndex(1);
}

void TypingTrainer::on_btnReturn_clicked() {
    ui->stackScreens->setCurrentIndex(0);
}

void TypingTrainer::on_actionExit_triggered() {
    close();
}
