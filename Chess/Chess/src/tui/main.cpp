#include <QCoreApplication>
#include <iostream>
#include <Controller.h>
#include <QProcess>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QProcess stock;
    stock.start(folder + prog);
    stock.waitForStarted();
    stock.setInputChannelMode(QProcess::ForwardedInputChannel);
    Controller cont = Controller(View(),Game(), &stock);
    QObject::connect(&stock, SIGNAL(finished(int,QProcess::ExitStatus)), &cont, SLOT(finished(int,QProcess::ExitStatus)));
    QObject::connect(&stock, SIGNAL(readyReadStandardOutput()), &cont, SLOT(readyReadStandardOutput()));
    QObject::connect(&stock, SIGNAL(started()), &cont, SLOT(started()));
    cont.start();
}
