#ifndef PROMOTION_H
#define PROMOTION_H

#include <QDialog>
#include <pieceitem.h>

namespace Ui {
class Promotion;
}

class Promotion : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Promotion the Constructor of the Promotion Window
     * @param parent the parent
     */
    explicit Promotion(Game *, Position, QWidget *parent = nullptr);
    ~Promotion();

private slots:
    /**
     * @brief on_buttonBox_accepted When the player click on the "OK" button
     */
    void on_buttonBox_accepted();

private:
    Game * _game;
    Position _position;
    Ui::Promotion *_ui;
    std::vector<PieceItem *> _pieces;
    int getIDSelected();

};

#endif // PROMOTION_H
