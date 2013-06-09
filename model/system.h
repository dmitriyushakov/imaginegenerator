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
    YPosition _ypos;
    XPosition _xpos;
    YOrientation _yorient;
    SystemType _type;
    void setStandart();
public:
    void setYOrientation(YOrientation orient);
    void setType(SystemType type);
    void setPos(XPosition pos);
    void setPos(YPosition pos);
    void setPos(XPosition xpos,YPosition ypos);
    YOrientation yOrientation();
    SystemType type();
    XPosition xPos();
    YPosition yPos();
    static System getRadial();
    static System getRectangle(XPosition xpos,YPosition ypos,YOrientation yorient);
    System();
};

#endif // SYSTEM_H
