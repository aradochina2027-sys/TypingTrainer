#include "typingtrainer.h"
#include "ui_typingtrainer.h"
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
            QString keyName = keys[j];
            QPushButton* btn = new QPushButton(keyName);
            btn->setMinimumSize(40, 40);
            btn->setFocusPolicy(Qt::NoFocus);
            ui->layoutGridKeyboard->addWidget(btn, i, j);
            keyboardMap.insert(keyName.toUpper(), btn);
        }
    }
    // Додаємо пробіл окремо
    QPushButton* spaceBtn = new QPushButton("Space");
    spaceBtn->setMinimumSize(200, 40);
    spaceBtn->setFocusPolicy(Qt::NoFocus);
    ui->layoutGridKeyboard->addWidget(spaceBtn, 4, 2, 1, 6);
    keyboardMap.insert(" ", spaceBtn);
}

void TypingTrainer::scanLessons() {
    ui->comboLesson->clear();
    QDir dir(lessonsPath);
    if (!dir.exists()) dir.mkpath(".");
    ui->comboLesson->addItems(dir.entryList({"*.txt"}, QDir::Files));
}

void TypingTrainer::loadLessonFile(const QString &fileName) {
    QFile file(lessonsPath + "/" + fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        currentText = QTextStream(&file).readAll().trimmed().simplified();
        file.close();
    } else {
        currentText = "Файл не знайдено.";
    }
    currentIndex = 0;
    errorCount = 0;
    updateDisplay();
}

void TypingTrainer::updateDisplay() {
    if (currentText.isEmpty()) return;
    QString typed = "<span style='color:green;'>" + currentText.left(currentIndex) + "</span>";
    QString current = "<span style='background-color:yellow; font-weight:bold; color:black;'>" + QString(currentText.at(currentIndex)) + "</span>";
    QString remaining = currentText.mid(currentIndex + 1);
    ui->textDisplay->setHtml(typed + current + remaining);
    ui->progressTraining->setValue((currentIndex * 100) / currentText.length());
    ui->lblAccuracy->setText("Помилки: " + QString::number(errorCount));
}

void TypingTrainer::keyPressEvent(QKeyEvent *event) {
    if (ui->stackScreens->currentIndex() != 1 || currentText.isEmpty()) return;

    QString charPressed = event->text();
    highlightKey(charPressed, true);

    if (event->key() == Qt::Key_Backspace) {
        if (currentIndex > 0) {
            currentIndex--;
            updateDisplay();
        }
        return;
    }

    if (charPressed.isEmpty()) return;

    if (charPressed == currentText.at(currentIndex)) {
        currentIndex++;
        if (currentIndex >= currentText.length()) finishSession();
        else updateDisplay();
    } else {
        errorCount++;
        updateDisplay();
    }
}

void TypingTrainer::keyReleaseEvent(QKeyEvent *event) {
    highlightKey(event->text(), false);
}

void TypingTrainer::highlightKey(const QString &key, bool pressed) {
    QString k = key.toUpper();
    if (keyboardMap.contains(k)) {
        if (pressed) keyboardMap[k]->setStyleSheet("background-color: lightblue; border: 2px solid blue;");
        else keyboardMap[k]->setStyleSheet("");
    }
}

void TypingTrainer::finishSession() {
    ui->stackScreens->setCurrentIndex(2);
    ui->resTime->setText("Помилок: " + QString::number(errorCount));
    ui->resAccuracy->setText("Завершено успішно!");
}

void TypingTrainer::on_btnStart_clicked() {
    if (ui->comboLesson->currentText().isEmpty()) return;
    loadLessonFile(ui->comboLesson->currentText());
    ui->stackScreens->setCurrentIndex(1);
}

void TypingTrainer::on_btnRandom_clicked() {
    if (ui->comboLesson->count() > 0) {
        ui->comboLesson->setCurrentIndex(QRandomGenerator::global()->bounded(ui->comboLesson->count()));
        on_btnStart_clicked();
    }
}

void TypingTrainer::on_btnRestart_clicked() { on_btnStart_clicked(); }
void TypingTrainer::on_btnReturn_clicked() { ui->stackScreens->setCurrentIndex(0); }
void TypingTrainer::on_actionExit_triggered() { close(); }
