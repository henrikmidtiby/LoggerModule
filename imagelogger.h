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

#ifndef IMAGELOGGER_H
#define IMAGELOGGER_H

#include "loggermodule.h"
#include <qt4/QtCore/QDateTime>
#include <qt4/QtCore/QMutex>
#include <deque>

class ImageLogger : public LoggerModule
{
    Q_OBJECT
public:
     ImageLogger(const QString pathToLog, const QString lognamePostString);
public slots:
    void pngImageLogger(cv::Mat image);
    void pngImageLogger(cv::Mat image, qint64 timestamp);
    void pngImageLogger(cv::Mat image, QString cameraName);
    void burstImageLogger(cv::Mat image);
    void burstImageLogger(cv::Mat image, qint64 timestamp);
    void saveImageBurst(void);

private slots:
private:
    QMutex mutex;
    QDir * pngImageDir;
    bool burstLoggerIsActive;
    std::deque<cv::Mat> listOfImages;
    std::deque<uint64> listOfTimeStamps;
    int maxNumberOfImages;
};

#endif // IMAGELOGGER_H
