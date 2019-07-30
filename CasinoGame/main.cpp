#include "casinogamewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if(argc != 2)
        return 1;

    QApplication a(argc, argv);
    CasinoGameWidget widget(argv[1]);
    widget.resize(885, 490);
    widget.show();

    return a.exec();
}
