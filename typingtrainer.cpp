#include "typingtrainer.h"
#include "ui_typingtrainer.h"
#include <QKeyEvent>
#include <QMessageBox>

TypingTrainer::TypingTrainer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TypingTrainer) {
    ui->setupUi(this);

    lessonsPath = QDir::currentPath() + "/lessons";

    setupKeyboard();
    scanLessons();
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

void TypingTrainer::scanLessons() {
    ui->comboLesson->clear();
    QDir dir(lessonsPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QStringList files = dir.entryList({"*.txt"}, QDir::Files);
    ui->comboLesson->addItems(files);
}

void TypingTrainer::loadLessonFile(const QString &fileName) {
    QFile file(lessonsPath + "/" + fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        currentText = in.readAll().trimmed();
        file.close();
    } else {
        currentText = "Error: Lesson file not found.";
    }
    currentIndex = 0;
    errorCount = 0;
    updateDisplay();
}

void TypingTrainer::updateDisplay() {
    if (currentText.isEmpty()) return;
    QString typed = "<span style='color:green;'>" + currentText.left(currentIndex) + "</span>";
    QString current = "<span style='background-color:yellow; font-weight:bold;'>" + QString(currentText.at(currentIndex)) + "</span>";
    QString remaining = currentText.mid(currentIndex + 1);
    ui->textDisplay->setHtml(typed + current + remaining);
    ui->progressTraining->setValue((currentIndex * 100) / currentText.length());
}

void TypingTrainer::keyPressEvent(QKeyEvent *event) {
    if (ui->stackScreens->currentIndex() != 1 || currentText.isEmpty()) return;
    QString keyText = event->text();
    if (keyText.isEmpty()) return;
    if (keyText == currentText.at(currentIndex)) {
        currentIndex++;
        if (currentIndex >= currentText.length()) finishSession();
        else updateDisplay();
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
    if (ui->comboLesson->currentText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please add .txt files to /lessons folder");
        return;
    }
    loadLessonFile(ui->comboLesson->currentText());
    ui->stackScreens->setCurrentIndex(1);
}

void TypingTrainer::on_btnRandom_clicked() {
    int count = ui->comboLesson->count();
    if (count > 0) {
        int index = QRandomGenerator::global()->bounded(count);
        ui->comboLesson->setCurrentIndex(index);
        on_btnStart_clicked();
    }
}

void TypingTrainer::on_btnRestart_clicked() { on_btnStart_clicked(); }
void TypingTrainer::on_btnReturn_clicked() { ui->stackScreens->setCurrentIndex(0); }
void TypingTrainer::on_actionExit_triggered() { close(); }
