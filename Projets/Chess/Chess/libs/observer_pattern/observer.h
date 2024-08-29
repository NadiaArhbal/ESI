#ifndef OBSERVER_H
#define OBSERVER_H
struct Observer
{
    /**
     * @brief The observer gets updated when the observable changes
     */
    virtual void update() {};
    virtual ~Observer() {};
};


#endif // OBSERVER_H
