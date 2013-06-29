#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
    enum SystemType{
        Rectangle,
        Radial
    };
    enum YPosition{
        Up=0,
        YMiddle=1,
        Down=2
    };
    enum XPosition{
        Left=0,
        XMiddle=1,
        Right=2
    };
    enum YOrientation{
        ToDown,
        ToUp
    };

private:
    int dx;
    int dy;
    YPosition _ypos;
    XPosition _xpos;
    YOrientation _yorient;
    SystemType _type;
public:
    void setYOrientation(YOrientation orient);
    void setType(SystemType type);
    void setPos(XPosition pos);
    void setPos(YPosition pos);
    void setPos(XPosition xpos,YPosition ypos);
    void setShiftX(int val);
    void setShiftY(int val);
    int getShiftX();
    int getShiftY();
    YOrientation yOrientation();
    SystemType type();
    XPosition xPos();
    YPosition yPos();
    System();
};

#endif // SYSTEM_H
