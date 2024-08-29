#include "history.h"

History::History(QTableWidget * tw, ChessPro * moves)
{
    _moves = moves;
    _tw = tw;
}

void History::update(const nvs::Subject * subject)
{
    if(subject == nullptr) return;
    clear();
    init(_moves->getMove());
    std::stringstream sstream(_moves->getMove());
    std::string word;
    char del = ' ';
    bool black = false;
    int i = 0;
    while(std::getline(sstream, word, del)) {
        if (word != "") {
            _tw->setItem(i, black, new QTableWidgetItem(word.c_str()));
            i += black;
            black = !black;
        }
    }
}

int History::getNbMoves(std::string moves)
{
    if (moves.size() == 0) {
        return 0;
    } else if (moves.size() == 4) {
        return 1;
    } else {
        return ((moves.size() - 4) / 5) + 1;
    }
}

void History::clear()
{
    _tw->clear();
    for (int i = 0; i < _tw->rowCount() - 1; ++i) {
        _tw->removeRow(i);
    }
}

void History::init(std::string moves)
{
    int nbMoves = getNbMoves(moves);
    int nbLines = nbMoves / 2 + nbMoves % 2;
    if (nbLines == 0) nbLines = 1;
    _tw->setRowCount(nbLines);
    QStringList list;
    list << "WHITE" << "BLACK";
    _tw->setHorizontalHeaderLabels(list);
    _tw->setColumnWidth(0, 120);
    _tw->setColumnWidth(1, 120);
}

ChessPro *History::getMoves()
{
    return _moves;
}

History::~History()
{
    delete _tw;
    delete _moves;
}
