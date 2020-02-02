#include <iostream>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTimer>
#include <AppConfig.hpp>
#include <NumberGenerator.hpp>

namespace AppConfiguration
{
    AppConfig g_appConfig;
};

const AppConfig& getAppConfig()
{
    return AppConfiguration::g_appConfig;
}

void parseCommandLineArgs(QCoreApplication& app)
{
    QCommandLineParser parser;
    parser.setApplicationDescription("An application for starting your Qt based projects faster.\n"
                                     "Prints a number at the middle of a given interval or a random number inside it.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("start", "The start of the interval.");
    parser.addPositionalArgument("end",  "The end of the interval.");

    QCommandLineOption generateRandomOpt(QStringList() << "r" << "print-random-int", "Prints random integer in range start-end.");
    parser.addOption(generateRandomOpt);
    parser.process(app);

    const QStringList args = parser.positionalArguments();
    // source is args.at(0), destination is args.at(1)
    AppConfiguration::g_appConfig.random = parser.isSet(generateRandomOpt);
    if (parser.positionalArguments().size() != 2){
        std::cerr << parser.helpText().toStdString();
        app.exit(EINVAL);
    }
    AppConfiguration::g_appConfig.start = parser.positionalArguments()[0].toUInt();
    AppConfiguration::g_appConfig.end = parser.positionalArguments()[1].toUInt();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("QStarterApplicaiton");
    QCoreApplication::setApplicationVersion("1.0");

    parseCommandLineArgs(app);

    NumberGenerator numGen;
    QObject::connect(&numGen, &NumberGenerator::FinishedGenerating, 
            [&app](uint32_t genNo){
                std::cout << "Generated number: " << genNo << ".\n"; 
                app.quit();
            }
    );

    QTimer::singleShot(100, &numGen, &NumberGenerator::GenerateNumberSlot);

    return app.exec();
}