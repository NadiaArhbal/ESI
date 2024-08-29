#ifndef PLAYERDTO_H
#define PLAYERDTO_H
#include "EntityDto.h"
namespace std
{
/**
 * @brief The PlayerDto class extends the entitydto as an int
 * Represents the player data, a player is ensentialy modifiable
 * hence this method will have setters
 */
class PlayerDto : public EntityDto<int>
{
    string _pseudo;
    string _password;
    int _image;
    string _nationality;
    int _elo;

  public:
    PlayerDto(int idArg, string pseud, string pswd, int img,
              string natio, int ell) : _pseudo(pseud), _password(pswd), _image(img)
        , _nationality(natio), _elo(ell)
    {
        EntityDto<int>::_id = idArg;
    }
    /**
     * @brief getPseudo gets the username of the player
     * @return a const string reference to it
     */
    const string & getPseudo()
    {
        return _pseudo;
    }
    /**
     * @brief getPassword gets the password of the player
     * @return a const string reference to it
     */
    const string & getPassword()
    {
        return _password;
    }
    /**
     * @brief setPseudo sets the new username of a player
     * @param pseudo new pseudo in a form of a string
     */
    void setPseudo(string pseudo)
    {
        this->_pseudo = pseudo;
    }
    /**
     * @brief setPassword sets the new password of a player
     * @param password new password in a form of a string
     */
    void setPassword(string password)
    {
        this->_password = password;
    }
    /**
     * @brief getNationality gets the nationality of a player with two letters
     * @return a const string reference to it
     */
    const string & getNationality()
    {
        return _nationality;
    }
    /**
     * @brief getElo gets the elo that is must be a 4 decimal number
     * @return the elo of a players
     */
    int getElo()
    {
        return _elo;
    }
    /**
     * @brief setNationality sets a new nationality
     * @param nationality new nationality of a player
     */
    void setNationality(string nationality)
    {
        this->_nationality = nationality;
    }
    /**
     * @brief setElo sets a new elo of a player
     * @param elo new elo value
     */
    void setElo(int elo)
    {
        this->_elo = elo;
    }
    /**
     * @brief getImage gets the image in form of a identifiable number
     * @return the image number
     */
    int getImage()
    {
        return _image;
    }
    /**
     * @brief setImage changes the image of a player
     * @param image new image
     */
    void setImage(int image)
    {
        this->_image = image;
    }
    string to_string()
    {
        return "Pseudo : " + _pseudo + " Password : " + _password +
               " Image : " +  std::to_string(_image) + " Nationality : " +
               _nationality + " Elo : " + std::to_string(_elo);
    }
};
}
#endif // PLAYERDTO.H
