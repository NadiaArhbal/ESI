#ifndef PARAMSTOCK_H
#define PARAMSTOCK_H

#include <QDialog>

namespace Ui {
class ParamStock;
}

class ParamStock : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief ParamStock Constructor of the Game parameters Window
     * @param parent the parent
     */
    explicit ParamStock(QWidget *parent = nullptr);

    ~ParamStock();

    /**
     * @brief isPvP Verify if the game is Player versus Player or not (versus Stockfish)
     * @return true if the game is PvP, false if not
     */
    bool isPvP();

    /**
     * @brief parametersOk Verify if at least one parameter is checked
     * @return true if at least one parameters is checked, false if not
     */
    bool parametersOk();

private:
    Ui::ParamStock *_ui;
    bool _PvP;
    bool _parametersOk = false;

signals:
    void filled();

private slots:

    /**
     * @brief on_buttonBox_accepted When the user click on the "OK" button
     */
    void on_buttonBox_accepted();
};

#endif // PARAMSTOCK_H
