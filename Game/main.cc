#include "engine.hh"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    StudentSide::Engine engine;
    //StudentSide::Engine* engine = new StudentSide::Engine();


    return a.exec();
}
