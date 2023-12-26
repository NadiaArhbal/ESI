#include "paramstock.h"
#include "ui_paramstock.h"

ParamStock::ParamStock(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ParamStock)
{
    _ui->setupUi(this);
    setWindowIcon(QIcon(":/icon_chess/ChessIcon.ico"));
    setWindowTitle("Welcome to Chess");
}

ParamStock::~ParamStock()
{
    delete _ui;
}

bool ParamStock::isPvP()
{
    return _PvP;
}

bool ParamStock::parametersOk()
{
    return _parametersOk;
}

void ParamStock::on_buttonBox_accepted()
{
    _PvP = _ui->rb_PvP_TRUE->isChecked();
    _parametersOk = true;
    emit filled();
}

