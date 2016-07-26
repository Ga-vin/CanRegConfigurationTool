#include <QApplication>
#include <QTextCodec>

#include "canregdlg.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

    /* Todo here */
    CanRegDlg *p_window = new CanRegDlg;
    p_window->show();

    return app.exec();
}
