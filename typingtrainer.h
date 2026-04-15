#ifndef TYPINGTRAINER_H
#define TYPINGTRAINER_H

#include <QMainWindow>
#include <QPushButton>
#include <QStringList>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class TypingTrainer; }
QT_END_NAMESPACE

class TypingTrainer : public QMainWindow {
    Q_OBJECT

public:
    TypingTrainer(QWidget *parent = nullptr);
    ~TypingTrainer();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnStart_clicked();
    void on_btnRestart_clicked();
    void on_btnReturn_clicked();
    void on_actionExit_triggered();

private:
    Ui::TypingTrainer *ui;

    QString currentText;
    int currentIndex;
    int errorCount;

    void setupKeyboard();
    void loadLesson(int index);
    void updateDisplay();
    void finishSession();
};

#endif
