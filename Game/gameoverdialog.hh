/**
  * Ohjelmointi 3 projekti - The Last of Bus II
  * Syksy 2020, vastuuopettaja Terhi Kilamo
  *
  * Olli Luukkonen H282332
  * olli.luukkonen@tuni.fi
  *
  * Matias Kanniainen H285295
  * matias.kanniainen@tuni.fi
  */

#ifndef GAMEOVERDIALOG_HH
#define GAMEOVERDIALOG_HH

#include <QDialog>

namespace Ui {
class gameOverDialog;
}
namespace StudentSide {

class gameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverDialog(QWidget *parent = nullptr);
    ~gameOverDialog();
    void setLabelTexts(QString player, int runningMinutes, int runningSeconds);
    void setTop10(QString total_scores);

    static int const EXIT_CODE_REBOOT = -123456789;

private:
    Ui::gameOverDialog *ui;

private slots:
    void on_restartPushButton_clicked();
    void on_closeButton_clicked();
};
}
#endif // GAMEOVERDIALOG_HH
