#include "system.h"

void System::setStandart(){
    _xpos=Left;
    _ypos=Up;
    _yorient=ToDown;
}

void System::setYOrientation(YOrientation orient){
    setType(Rectangle);
    _yorient=orient;
}

void System::setType(SystemType type){
    if(type!=_type){
        if(type==Radial)setStandart();
        _type=type;
    }
}

void System::setPos(XPosition pos){
    setType(Rectangle);
    _xpos=pos;
}

void System::setPos(YPosition pos){
    setType(Rectangle);
    _ypos=pos;
}

void System::setPos(XPosition xpos, YPosition ypos){
    setType(Rectangle);
    _xpos=xpos;
    _ypos=ypos;
}

System::YOrientation System::yOrientation(){
    return _yorient;
}

System::SystemType System::type(){
    return _type;
}

System::XPosition System::xPos(){
    return _xpos;
}

System::YPosition System::yPos(){
    return _ypos;
}

System System::getRadial(){
    System system;
    system._type=Radial;
    system.setStandart();
    return system;
}

System System::getRectangle(XPosition xpos, YPosition ypos, YOrientation yorient){
    System system;
    system._type=Rectangle;
    system._xpos=xpos;
    system._ypos=ypos;
    system._yorient=yorient;
    return system;
}

System::System(){
    _type=Rectangle;
    setStandart();
}
