#include <iostream>
#include <vector>
#include <observer_pattern/observer.h>
#ifndef OBSERVABLE_H
#define OBSERVABLE_H

struct observable
{

    std::vector<Observer * > obs;

    /**
     * @brief Adds an observer to the list of observers.
     * @param o The observer to add.
     */
    void addObs(Observer & o)
    {
        obs.push_back(&o);
    }

    /**
     * @brief Notifies all of the observers.
     */
    void notify()
    {
        for (Observer * o : obs)
        {
            o->update();
        }
    }
};

#endif // OBSERVABLE_H
