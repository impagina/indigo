#include "indigo.h"

#include <iostream>
#include <QDebug>

#include <QStringList>
#include <QFile>
#include <QFileInfo>

Indigo::Indigo(int argc, char *argv[]) :
    QCoreApplication(argc, argv)
{
    QString INDIGONAME = "Indigo";
    QString INDIGOVERSION = "0.0";
    setApplicationName(INDIGONAME); // TODO: get it from the cmake file
    setApplicationVersion(INDIGOVERSION);
}

int Indigo::run()
{
    int result = EXIT_SUCCESS;
    QStringList arguments = this->arguments();
    QStringList filename = QStringList();
    qDebug() << "arguments" << arguments;


    for (int i = 1; i < arguments.count(); i++)
    {
        QString argument = arguments.at(i);
        if (argument == "-v")
        {
            std::cout << getApplicationVersion().toLocal8Bit().data() << std::endl;
            return EXIT_SUCCESS;
        }
        else if ((argument == "-h") || (argument == "-?") || (argument == "--help"))
        {
            std::cout << getApplicationHelp().toLocal8Bit().data() << std::endl;
            return EXIT_SUCCESS;

        }
        else if (QFileInfo(QFile::decodeName(argument.toLocal8Bit())).exists())
        {

            filename << argument.toLocal8Bit();

        }
        else
        {
            if (argument.left(1) == "-")
            {
                std::cerr << tr("%1: Invalid argument: %2").arg(applicationName()).arg(argument).toLocal8Bit().data() << "\n";
                std::cerr << getApplicationUsage().toUtf8().constData() << "\n";
                return EXIT_FAILURE;
            }
            else
            {
                std::cerr << tr("%1: File %2 does not exist, aborting.").arg(applicationName()).arg(argument).toLocal8Bit().data() << "\n";
                std::cerr << getApplicationUsage().toUtf8().constData() << "\n";
                return EXIT_FAILURE;
            }
        }
    }

    if (filename.empty())
    {
        std::cerr << getApplicationUsage().toUtf8().constData() << "\n";
        return EXIT_FAILURE;
    }

    // loadPlugins();

    // for now, just get the first sla-load plugin, if any, and use it
    // in the future, the user will be able to tell us the version or ask to guess. the default will be to use
    // the current version.
/*
    if (pluginsLoad.empty())
    {
        std::cerr << "no load plugin loaded" << "\n";
        return false;
    }
    qDebug() << "filename" << filename;
    Document *document = new Document();
    foreach (QString item, filename)
    {
        PluginLoadInterface *loader = pluginsLoad.first();
        if (loader->loadFile(item))
        {
            // TODO: put the documents in a list or do some further processing as soon as they're loaded (ale/20130829)
            Document *document = loader->getDocument();
        }

    }
*/

    qDebug() << "result" << result;
    return result;
}

/**
 * @brief Indigo::getApplicationVersion
 * @return
 * TODO: when the output goes to cerr, the eol may have to be replaced by the caller after getting the string
 * TODO: eventually add more information on the version (compile options? license?) (ale/20130828)
 */
QString Indigo::getApplicationVersion()
{
    return tr("%1 version %2").arg(applicationName()).arg(applicationVersion());
}

/**
 * @brief Indigo::getApplicationUsage
 * @return
 * TODO: when the output goes to cerr, the eol may have to be replaced by the caller after getting the string
 */
QString Indigo::getApplicationUsage()
{
    return
        tr("%1 version %2").arg(applicationName()).arg(applicationVersion()) + "\n" +
        tr("Try %1 -h for more information.").arg(arguments().at(0));
}

/**
 * @brief Indigo::getApplicationHelp
 * @return
 * TODO: when the output goes to cerr, the eol may have to be replaced by the caller after getting the string
 */
QString Indigo::getApplicationHelp()
{
    return
        tr("%1 version %2").arg(applicationName()).arg(applicationVersion()) + "\n" +
        tr("Usage:") + "\n" +
        tr("  %1 [arguments] file [..]  process the specified file(s)").arg(arguments().at(0)) + "\n" +
        tr("Arguments:") + "\n" +
        "  -v           " + tr("Print version information and exit") + "\n" +
        "  -h -? --help " + tr("Print Help (this message) and exit");
}

/*
void Indigo::loadPlugins()
{
    // QCoreApplication::addLibraryPath("plugins");
    QDir pluginsDir = QDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    qDebug() << "pluginsDir" << pluginsDir;
    // pluginsDir.cd("load");
    // qDebug() << "pluginsDir" << pluginsDir;
    foreach (QString filename, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(filename));
        qDebug() << "filename is a plugin?" << filename;
        if (QObject *object = loader.instance())
        {
            // qDebug() << "plugin" << plugin;
            PluginLoadInterface* plugin = qobject_cast<PluginLoadInterface *>(object);
            qDebug() << "plugin name" << plugin->getName();
            pluginsLoad.append(plugin);
        }

    }
}
*/

