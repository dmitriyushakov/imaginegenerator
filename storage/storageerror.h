#ifndef STORAGEERROR_H
#define STORAGEERROR_H

#include <QFileDevice>

class StorageError
{
public:
    enum ErrorState{
        NoError,
        Warning,
        Error
    };
    StorageError(QFileDevice::FileError error);
    StorageError(ErrorState state,QString message);
    QString message();
    ErrorState state();
    bool isError();
    static StorageError success();
private:
    QString _message;
    ErrorState _state;
    StorageError();
};

#endif // STORAGEERROR_H
