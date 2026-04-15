#ifndef TYPINGTRAINER_H
#define TYPINGTRAINER_H

#include <QMainWindow>
#include <QPushButton>
#include <QStringList>
#include <QMap>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QKeyEvent>

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
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void on_btnStart_clicked();
    void on_btnRandom_clicked();
    void on_btnRestart_clicked();
    void on_btnReturn_clicked();
    void on_actionExit_triggered();

private:
    Ui::TypingTrainer *ui;
    QString currentText;
    int currentIndex;
    int errorCount;
    QString lessonsPath;

    QMap<QString, QPushButton*> keyboardMap;

    void setupKeyboard();
    void scanLessons();
    void loadLessonFile(const QString &fileName);
    void updateDisplay();
    void finishSession();
    void highlightKey(const QString &key, bool pressed);
};

#endif
