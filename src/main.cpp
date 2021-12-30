#include <./lib/frontend/mainwindow.h>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/src/alagard.ttf");
    QFont f = QFont("Alagard");
    QApplication::setFont(f);
    QPixmap p = QPixmap(":/imgs/src/assets/ui-components/cursor.png");
    QCursor c = QCursor(p, 0, 0);
    QApplication::setOverrideCursor(c);

    MainWindow w;
    w.setWindowTitle("Tales of Liesel");
    w.setWindowIcon(QIcon(QPixmap(":/imgs/src/assets/ui-components/FireballIcon.png")));
    w.show();
    return a.exec();
}
