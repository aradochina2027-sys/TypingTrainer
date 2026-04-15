#ifndef TYPINGTRAINER_H
#define TYPINGTRAINER_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class TypingTrainer; }
QT_END_NAMESPACE

class TypingTrainer : public QMainWindow {
    Q_OBJECT

public:
    TypingTrainer(QWidget *parent = nullptr);
    ~TypingTrainer();

private slots:
    void on_btnStart_clicked();
    void on_btnRestart_clicked();
    void on_btnReturn_clicked();
    void on_actionExit_triggered();

private:
    Ui::TypingTrainer *ui;
    void setupKeyboard();
    std::vector<QPushButton*> keys;
};

#endif
