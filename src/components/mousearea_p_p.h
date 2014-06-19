#ifndef MOUSEAREA_P_P_H
#define MOUSEAREA_P_P_H

#include "item_p_p.h"
#include "mousearea_p.h"

class MouseAreaPrivate : public ItemPrivate
{

public:
    MouseAreaPrivate(MouseArea *parent);

    MouseDrag* drag();

    MouseDrag *_drag;

    bool containsMouse;

    int mouseX;
    int mouseY;

    bool pressed;

    bool preventStealing;

    int timerId;
};

#endif // MOUSEAREA_P_P_H
