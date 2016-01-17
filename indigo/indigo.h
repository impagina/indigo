#ifndef INDIGO_H
#define INDIGO_H

#include <QCoreApplication>

class QString;

// #include <QList>
// #include <plugins/pluginInterface.h>


class Indigo : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Indigo(int argc, char *argv[]);
    int run();
    QString getApplicationVersion();
    QString getApplicationUsage();
    QString getApplicationHelp();

    // void loadPlugins();

protected:
    // QList<PluginLoadInterface*> pluginsLoad;

signals:
    
public slots:
    
};

#endif // INDIGO_H

