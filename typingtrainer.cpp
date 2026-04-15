#include "typingtrainer.h"
#include "ui_typingtrainer.h"
#include <QMessageBox>

TypingTrainer::TypingTrainer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TypingTrainer) {
    ui->setupUi(this);

    ui->comboLesson->addItems({
        "Starter Text", "Numbers and Symbols",
        "Common Words Part 1", "Common Words Part 2",
        "Python Code Sample", "Lorem Ipsum"
    });

    setupKeyboard();
    ui->stackScreens->setCurrentIndex(0);
}

TypingTrainer::~TypingTrainer() {
    delete ui;
}

void TypingTrainer::setupKeyboard() {
    QStringList rows = {
        "1,2,3,4,5,6,7,8,9,0,-,=",
        "Q,W,E,R,T,Y,U,I,O,P,[,]",
        "A,S,D,F,G,H,J,K,L,;,',Enter",
        "Z,X,C,V,B,N,M,,,.,/"
    };

    for (int i = 0; i < rows.size(); ++i) {
        QStringList rowKeys = rows[i].split(",");
        for (int j = 0; j < rowKeys.size(); ++j) {
            QPushButton* btn = new QPushButton(rowKeys[j]);
            btn->setMinimumSize(40, 40);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            ui->layoutGridKeyboard->addWidget(btn, i, j);
            keys.push_back(btn);
        }
    }
}

void TypingTrainer::on_btnStart_clicked() {
    ui->stackScreens->setCurrentIndex(1);
}

void TypingTrainer::on_btnRestart_clicked() {
    ui->stackScreens->setCurrentIndex(1);
}

void TypingTrainer::on_btnReturn_clicked() {
    ui->stackScreens->setCurrentIndex(0);
}

void TypingTrainer::on_actionExit_triggered() {
    close();
}
