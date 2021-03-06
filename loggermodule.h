/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LOGGERMODULE_H
#define LOGGERMODULE_H

#include <qt4/QtCore/QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <qt4/QtCore/QFile>
#include <qt4/QtCore/QDir>
#include <qt4/QtCore/QTextStream>

class LoggerModule : public QThread
{
    Q_OBJECT
public:
    LoggerModule(const QString pathToLog, const QString lognamePostString);
    void run();
    void activate();
    void deactivate();
    QDir * logdir;
public slots:
    void log(const QString nameOfValue, int value);
    void log(const QString nameOfValue, const char* value);
private slots:
    void flushLogs(void);
private:
    static bool isAtLeastOneLoggerModuleInitialized;
    static QDir * baseDirectory;
    
    void checkThatBaseDirectoryExists(const QString pathToLog);
    void ensureThatLogDirectoryExists(const QString pathToLog, const QString lognamePostString);
    void createBaseLogDirectory(const QString pathToLog, const QString lognamePostString);
    void createSubLogDir(const QString subDirName);
    
    bool loggerIsActive;
    
    QFile * runtimeLoggerFile;
    QTextStream * runtimeLoggerStream;
};

#endif // LOGGERMODULE_H
