#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QFile>
#include <QLocale>
#include <QLibraryInfo>

#include "gui/window.h"

int main(int argc,char **argv){
    QApplication app(argc,argv);

    QTranslator qtTranslator;
#ifdef Q_OS_LINUX
    const QString qtTranslationsDir =
            QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#else
    const QString qtTranslationsDir=QCoreApplication::applicationDirPath().append("/qttranslations");
#endif
    QString qtTrFileName=QString("qt_")+QLocale::system().name()+QString(".qm");
    if(qtTranslator.load(qtTrFileName,qtTranslationsDir))
        app.installTranslator(&qtTranslator);

    QTranslator translator;
    QString trFileName=QLocale::languageToString(QLocale::system().language()).append(".qm");
#ifdef Q_OS_LINUX
    const QString trDirPath=QCoreApplication::applicationDirPath().append("/../share/imaginegenerator/translations");
#else
    const QString trDirPath=QCoreApplication::applicationDirPath().append("/translations");
#endif
    if(translator.load(trFileName,trDirPath))
        app.installTranslator(&translator);

    Window win;
    if(argc!=1){
        win.open(QString(argv[1]));
    }
    win.show();

    return app.exec();
}
