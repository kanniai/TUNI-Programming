/**
  * Ohjelmointi 3 projekti - The Last of Bus II
  * Syksy 2020, vastuuopettaja Terhi Kilamo
  *
  * olli.luukkonen@tuni.fi
  * matias.kanniainen@tuni.fi
  */

#include "engine.hh"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;

    do {
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    StudentSide::Engine engine;

    currentExitCode = a.exec();
    } while( currentExitCode == StudentSide::gameOverDialog::EXIT_CODE_REBOOT );

    return currentExitCode;
}
