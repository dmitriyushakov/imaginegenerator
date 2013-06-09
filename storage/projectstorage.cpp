#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QDomNode>

#include "projectstorage.h"
#include "version.h"

ProjectStorage::ProjectStorage()
{
}

StorageError ProjectStorage::saveLayout(Layer &lay, QString filename){
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();

        writer.writeStartElement("ImagineProject");
        writer.writeAttribute("version",QString::number(PROJECT_VERSION));
        writer.writeAttribute("apilevel",QString::number(PROJECT_API_LEVEL));

        writer.writeStartElement("Layer");

        if(!lay.getScript().isEmpty())writer.writeTextElement("Script",lay.getScript());
        if(!lay.getRComponent().isEmpty())writer.writeTextElement("Red",lay.getRComponent());
        if(!lay.getGComponent().isEmpty())writer.writeTextElement("Green",lay.getGComponent());
        if(!lay.getBComponent().isEmpty())writer.writeTextElement("Blue",lay.getBComponent());
        if(!lay.getGreyComponent().isEmpty())writer.writeTextElement("Grey",lay.getGreyComponent());

        QString xtype;
        if(lay.getXPointType()==Absolute){
            xtype="Absolute";
        }else{
            xtype="Relatively";
        }

        QString ytype;
        if(lay.getYPointType()==Absolute){
            ytype="Absolute";
        }else{
            ytype="Relatively";
        }

        QString colortype;
        if(lay.getColorType()==Tricolor){
            colortype="Tricolor";
        }else{
            colortype="Grey";
        }

        System system=lay.getSystem();
        QString systemtype;
        if(system.type()==System::Rectangle){
            systemtype="Rectangle";
        }else{
            systemtype="Radial";
        }

        QString cxpos;
        if(system.xPos()==System::Left){
            cxpos="Left";
        }else if(system.xPos()==System::XMiddle){
            cxpos="Middle";
        }else{
            cxpos="Right";
        }

        QString cypos;
        if(system.yPos()==System::Up){
            cypos="Up";
        }else if(system.yPos()==System::YMiddle){
            cypos="Middle";
        }else{
            cypos="Down";
        }

        QString yorient;
        if(system.yOrientation()==System::ToUp){
            yorient="toUp";
        }else{
            yorient="toDown";
        }

        writer.writeTextElement("XPointerType",xtype);
        writer.writeTextElement("YPointerType",ytype);
        writer.writeTextElement("ColorType",colortype);

        writer.writeStartElement("CoordSystem");
        writer.writeAttribute("type",systemtype);
        writer.writeAttribute("xcenter",cxpos);
        writer.writeAttribute("ycenter",cypos);
        writer.writeAttribute("yorientation",yorient);
        writer.writeEndElement();

        writer.writeEndElement();

        writer.writeEndElement();

        writer.writeEndDocument();

        file.close();
        return StorageError::success();
    }else return StorageError(file.error());
}

StorageError ProjectStorage::resoreLayout(Layer &lay, QString filename){
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QDomDocument document;
        bool success=document.setContent(&file);
        if(success){
            QDomElement root=document.documentElement().toElement();

            // Much conditions.
            if(root.tagName()!="ImagineProject")return StorageError(StorageError::Error,QObject::tr("It is not Imagine Generator project."));
            if(!root.hasAttribute("apilevel"))return StorageError(StorageError::Error,QObject::tr("'ImagineProject' have not 'apilevel' attribute."));
            if(!root.hasAttribute("version"))return StorageError(StorageError::Error,QObject::tr("'ImagineProject' have not 'version' attribute."));
            bool ok=true;
            int version=root.attributeNode("version").value().toInt(&ok);
            if(!ok)return StorageError(StorageError::Error,QObject::tr("'version' must have a number value."));
            int apilevel=root.attributeNode("apilevel").value().toInt(&ok);
            if(!ok)return StorageError(StorageError::Error,QObject::tr("'apilevel' must have a number value."));
            if(version>PROJECT_VERSION)return StorageError(StorageError::Error,QObject::tr("This version of program old for open project."));
            if(apilevel>PROJECT_API_LEVEL)return StorageError(StorageError::Warning,QObject::tr("This version of program maybe can't work with this project."));

            if(root.elementsByTagName("Layer").isEmpty())return StorageError(StorageError::Error,QObject::tr("Project have not layer."));

            QDomElement layer=root.elementsByTagName("Layer").at(0).toElement();

            if(layer.elementsByTagName("XPointerType").isEmpty())return StorageError(StorageError::Error,QObject::tr("Project have not X pointer type difenition."));
            if(layer.elementsByTagName("YPointerType").isEmpty())return StorageError(StorageError::Error,QObject::tr("Project have not Y pointer type difenition."));
            if(layer.elementsByTagName("ColorType").isEmpty())return StorageError(StorageError::Error,QObject::tr("Project have not color type difenition."));

            QString xPointerStr=layer.elementsByTagName("XPointerType").at(0).toElement().text();
            if(!(xPointerStr=="Absolute"||xPointerStr=="Relatively"))return StorageError(StorageError::Error,QObject::tr("Unknown '%s' definition.").replace("%s",xPointerStr));
            if(xPointerStr=="Absolute")lay.setXPointType(Absolute);
            else lay.setXPointType(Related);

            QString yPointerStr=layer.elementsByTagName("YPointerType").at(0).toElement().text();
            if(!(yPointerStr=="Absolute"||yPointerStr=="Relatively"))return StorageError(StorageError::Error,QObject::tr("Unknown '%s' definition.").replace("%s",yPointerStr));
            if(yPointerStr=="Absolute")lay.setYPointType(Absolute);
            else lay.setYPointType(Related);

            QString colortype=layer.elementsByTagName("ColorType").at(0).toElement().text();
            if(!(colortype=="Tricolor"||colortype=="Grey"))return StorageError(StorageError::Error,QObject::tr("Unknown '%s' definition.").replace("%s",colortype));
            if(colortype=="Tricolor")lay.setColorType(Tricolor);
            else lay.setColorType(GreyColor);

            if(!layer.elementsByTagName("Script").isEmpty()){
                lay.setScript(layer.elementsByTagName("Script").at(0).toElement().text());
            }

            if(!layer.elementsByTagName("Red").isEmpty()){
                lay.setRComponent(layer.elementsByTagName("Red").at(0).toElement().text());
            }

            if(!layer.elementsByTagName("Green").isEmpty()){
                lay.setGComponent(layer.elementsByTagName("Green").at(0).toElement().text());
            }

            if(!layer.elementsByTagName("Blue").isEmpty()){
                lay.setBComponent(layer.elementsByTagName("Blue").at(0).toElement().text());
            }

            if(!layer.elementsByTagName("Grey").isEmpty()){
                lay.setGreyComponent(layer.elementsByTagName("Grey").at(0).toElement().text());
            }

            if(!layer.elementsByTagName("CoordSystem").isEmpty()){
                QDomElement elem=layer.elementsByTagName("CoordSystem").at(0).toElement();
                QString systemtype=elem.attribute("type","Rectangle");
                QString cxpos=elem.attribute("xcenter","Left");
                QString cypos=elem.attribute("ycenter","Up");
                QString yorient=elem.attribute("yorientation","ToDown");

                System sys;
                sys.setType(systemtype=="Radial"?System::Radial : System::Rectangle);

                if(cxpos=="Right"){
                    sys.setPos(System::Right);
                }else if(cxpos=="Middle"){
                    sys.setPos(System::XMiddle);
                }else{
                    sys.setPos(System::Left);
                }

                if(cypos=="Down"){
                    sys.setPos(System::Down);
                }else if(cypos=="Middle"){
                    sys.setPos(System::YMiddle);
                }else{
                    sys.setPos(System::Up);
                }

                sys.setYOrientation(yorient=="toUp"?System::ToUp:System::ToDown);
                lay.setSystem(sys);
            }

            return StorageError::success();
        }else{
            return StorageError(StorageError::Error,QObject::tr("XML parse error occured."));
        }
    }else return StorageError(file.error());
}
