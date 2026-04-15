#include "typingtrainer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TypingTrainer w;
    w.show();
    return a.exec();
}
