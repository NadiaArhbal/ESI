#ifndef ENTITYDTO_H
#define ENTITYDTO_H
#include <string>
template <class T>
/**
 * Abstract class that every dto has to extend
 * @param template <class T>
 */
class EntityDto
{
  protected:

    /**
     * @brief _id Primary key of the epersisted item
     * Each class can have a different ypu of identifier
     */
    T _id;
  public:
    /**
     * @brief isPersistant checks if dto has id or not
     * @return true if id is not equivalent to 0
     */
    inline bool isPersistant()
    {
        return _id != 0;
    }
    /**
     * @brief getID return the value of the ID
     * @return this value is equivalent to 0 or "" si rien n'est précisé
     */
    inline T getID()
    {
        return _id;
    }
    /**
     * @brief setID sets the value of the ID
     * @param id value of templated type
     */
    inline void setID(T id)
    {
        this->_id = id;
    }
    /**
     * @brief isEquals compares dto to other other Dto's
     * @param rhs other dto
     * @return true if the two dto are the same
     */
    inline bool isEquals(const EntityDto & rhs)
    {

        if (rhs == nullptr || rhs != this ||
                rhs.isPersistant() == this->isPersistant() )
        {
            return false;
        }
        return this->getID() == rhs->getID();
    }
    /**
     * @brief to_string pre virtual function that makes this class abstract
     * @return the string containing all of the members value in a form a string
     */
    virtual std::string to_string() = 0;
};
#endif //ENTITYDTO_H
