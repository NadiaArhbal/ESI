#ifndef PLAYERSPECIFICATION_H
#define PLAYERSPECIFICATION_H
#include <string>
namespace std
{
/**
 * @brief The PlayerSpecification class contains
 * the given arguments example here is if no arguments are given then
 * int is represented by 0 or strings with ""
 */
class PlayerSpecification
{
    int _id;
    string _pseudo;
    string _password;
    int _image;
    string _nationality;
    int _elo;
  public:
    PlayerSpecification(int id, string pseudo, string password,
                        int image, string nationality, int elo) : _id(id), _pseudo(pseudo),
        _password(password), _image(image), _nationality(nationality),
        _elo(elo) {}
    /**
     * @brief getID simply gets the id of the specified usr
     * @return the id of the user
     */
    inline int getID();
    /**
     * @brief getPseudo simply gets the pseudo of the specified usr
     * @return the pseudo of the user
     */
    inline const string & getPseudo();
    /**
     * @brief getPassword simply gets the password of the specified usr
     * @return the password of the user
     */
    inline const string & getPassword();
    /**
     * @brief getPassword simply gets the nationality of the specified usr
     * @return the password of the user
     */
    inline const string & getNationality();
    /**
     * @brief getElo simply gets the elo of the specified user
     * @return the elo of the user
     */
    inline int getElo();
    /**
     * @brief getImage simply gets the image of the specified user
     * @return the image of the user
     */
    inline int getImage();

};
inline int PlayerSpecification::getID()
{
    return _id;
}
inline const string & PlayerSpecification::getPseudo()
{
    return _pseudo;
}
inline const string & PlayerSpecification::getPassword()
{
    return _password;
}
inline const string & PlayerSpecification::getNationality()
{
    return _nationality;
}
inline int PlayerSpecification::getElo()
{
    return _elo;
}
inline int PlayerSpecification::getImage()
{
    return _image;
}
}

#endif //PLAYERSPECIFICATION_H
