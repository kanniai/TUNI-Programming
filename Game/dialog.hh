/**
  * Ohjelmointi 3 projekti - The Last of Bus II
  * Syksy 2020, vastuuopettaja Terhi Kilamo
  *
  * olli.luukkonen@tuni.fi
  * matias.kanniainen@tuni.fi
  */

#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <QString>
#include <map>


namespace Ui {

class Dialog;
}


namespace StudentSide {
/**
 * @brief The Dialog class is presented in making pregame-choices before
 * actually starting the game
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void selectName();

signals:
    // Player vehicle selection
    void helicopterSelected();
    void fighterSelected();
    void spaceShipSelected();

    void player1Name(QString name);
    void player2Name(QString name);

private slots:
    void on_heliButton_clicked();
    void on_jetButton_clicked();
    void on_spaceButton_clicked();

    void on_name1Button_clicked();
    void on_name2Button_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::Dialog *ui;
    QString name1_;
    QString name2_;
    bool startGame_ = false;
};
}
#endif // DIALOG_HH
