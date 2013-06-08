#include "storageerror.h"

StorageError::StorageError(){}

StorageError::StorageError(QFileDevice::FileError error)
{
    if(error=QFileDevice::NoError){
        _message=QObject::tr("No error occured.");
        _state=NoError;
    }else{
        _state=Error;
        switch(error){
            case QFileDevice::ReadError:_message=QObject::tr("An error occured when reading from the file.");break;
            case QFileDevice::WriteError:_message=QObject::tr("An error occured when writing to the file.");break;
            case QFileDevice::FatalError:_message=QObject::tr("A fatal error occured.");break;
            case QFileDevice::ResourceError:_message=QObject::tr("A resource error occured.");break;
            case QFileDevice::OpenError:_message=QObject::tr("The file could not be opened.");break;
            case QFileDevice::AbortError:_message=QObject::tr("The operation was aborted.");break;
            case QFileDevice::TimeOutError:_message=QObject::tr("A timeout occured.");break;
            case QFileDevice::UnspecifiedError:_message=QObject::tr("An unspecified error occured.");break;
            case QFileDevice::RemoveError:_message=QObject::tr("The file could not be removed.");break;
            case QFileDevice::RenameError:_message=QObject::tr("The file could not be renamed.");break;
            case QFileDevice::PositionError:_message=QObject::tr("The position in the file could not be changed.");break;
            case QFileDevice::ResizeError:_message=QObject::tr("The file could not be resized.");break;
            case QFileDevice::PermissionsError:_message=QObject::tr("The file could not be accessed.");break;
            case QFileDevice::CopyError:_message=QObject::tr("The file could not be copied.");break;
            default:_message=QObject::tr("A unknown error occured(code:%i)").replace("%i",QString::number(error));
        }
    }
}

StorageError::StorageError(ErrorState state, QString message){
    _state=state;
    _message=message;
}

QString StorageError::message(){
    return _message;
}

StorageError::ErrorState StorageError::state(){
    return _state;
}

bool StorageError::isError(){
    return _state!=NoError;
}

StorageError StorageError::success(){
    return StorageError(NoError,QObject::tr("No error occured."));
}
