#ifndef ADMINMODEL_H
#define ADMINMODEL_H
#include <business/AdminFacade.h>

class AdminModel : public AdminFacade
{
  public:
    optional<PlayerDto> getPlayerByID(int id) override;
    optional<PlayerDto> getPlayerLogin(string pseudo,
                                       string password) override;
    int addPlayer(PlayerDto player) override;
    int addGame(GameDto game) override;
    bool updatePlayer(PlayerDto player) override;
};
#endif // ADMINMODEL_H
