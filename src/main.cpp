#include "./lib/frontend/widget.h"

#include <QApplication>
#include <QIcon>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Setup app - Part 1
    QFontDatabase::addApplicationFont(":/fonts/src/alagard.ttf");
    QFont f = QFont("Alagard");
    QApplication::setFont(f);
    QPixmap p = QPixmap(":/imgs/src/assets/ui-components/cursor.png");
    QCursor c = QCursor(p, 0, 0);
    QApplication::setOverrideCursor(c);

    Widget w;

    // Setup app - Part 2
    w.setWindowTitle("Tales of Liesel");
    w.setWindowIcon(QIcon(QPixmap(":/imgs/src/assets/ui-components/FireballIcon.png")));
    w.show();

    return a.exec();
}
