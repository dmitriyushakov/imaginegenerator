#ifndef PROJECTSTORAGE_H
#define PROJECTSTORAGE_H

#include "model/layer.h"
#include "storageerror.h"

class ProjectStorage
{
public:
    static StorageError saveLayout(Layer &lay,QString filename);
    static StorageError resoreLayout(Layer &lay,QString filename);
    ProjectStorage();
};

#endif // PROJECTSTORAGE_H
