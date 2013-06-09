#include "system.h"

void System::setYOrientation(YOrientation orient){
    _yorient=orient;
}

void System::setType(SystemType type){
    if(type!=_type){
        _type=type;
    }
}

void System::setPos(XPosition pos){
    _xpos=pos;
}

void System::setPos(YPosition pos){
    _ypos=pos;
}

void System::setPos(XPosition xpos, YPosition ypos){
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

System::System(){
    _type=Rectangle;
    _xpos=Left;
    _ypos=Up;
    _yorient=ToDown;
}
