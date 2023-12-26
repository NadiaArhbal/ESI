#include <business/AdminModel.h>

optional<PlayerDto> AdminModel::getPlayerByID(int id)
{
    DBManager::startTransaction();
    const auto & playerDto = PlayerBusinessLogic::findByID(id);
    DBManager::validateTransaction();
    return playerDto;
}
optional<PlayerDto> AdminModel::getPlayerLogin(string pseudo,
        string password)
{
    DBManager::startTransaction();
    optional<PlayerDto> playerID = PlayerBusinessLogic::findByLogin(
                                       pseudo, password);
    DBManager::validateTransaction();
    return playerID;
}
int AdminModel::addPlayer(PlayerDto player)
{
    DBManager::startTransaction();
    // Here if method return id = 0 -> isAdded false
    int givenID = PlayerBusinessLogic::add(player);
    DBManager::validateTransaction();
    return givenID;
}
bool AdminModel::updatePlayer(PlayerDto player)
{
    DBManager::startTransaction();
    auto isUpdated = PlayerBusinessLogic::update(player);
    DBManager::validateTransaction();
    return isUpdated;
}
int AdminModel::addGame(GameDto game)
{
    DBManager::startTransaction();
    int gameID = GameBusinessLogic::insert(game);
    DBManager::validateTransaction();
    return gameID;
}
