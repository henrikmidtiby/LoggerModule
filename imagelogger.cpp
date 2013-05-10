// #include "loggermodule.h"
#include "imagelogger.h"
#include "imagelogger.moc"

ImageLogger::ImageLogger(const QString pathToLog, const QString lognamePostString)
: LoggerModule(pathToLog, lognamePostString)
{
    std::cout << "In ImageLogger constructor" << std::endl;
    burstLoggerIsActive = true;
    maxNumberOfImages = 100;
    pngImageDir = new QDir(*logdir);
}

ImageLogger::~ImageLogger()
{
  delete pngImageDir;
}

void ImageLogger::pngImageLogger(cv::Mat image)
{
    pngImageLogger(image, "");
}

void ImageLogger::pngImageLogger(cv::Mat image, qint64 timestamp)
{
    std::cout << "Received image with timestamp: " << timestamp << std::endl;
    pngImageLogger(image, "timestamp" + QString::number(timestamp));
}

void ImageLogger::pngImageLogger(cv::Mat image, QString cameraName)
{
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    QString targetFilename = QString::number(QDateTime::currentMSecsSinceEpoch()) + cameraName + ".png";

    // TODO: Check for enough space
    cv::imwrite(pngImageDir->filePath(targetFilename).toStdString(), image, compression_params);
}

void ImageLogger::burstImageLogger(cv::Mat image, qint64 timestamp)
{
    burstImageLogger(image);
}

void ImageLogger::burstImageLogger(cv::Mat image)
{
    if(!burstLoggerIsActive)
    {
        return;
    }
    mutex.lock();
    cv::Mat tempImage = image.clone();
    listOfImages.push_back(tempImage);
    uint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    listOfTimeStamps.push_back(currentTime);
    if(listOfImages.size() > maxNumberOfImages)
    {
        listOfImages.pop_front();
        listOfTimeStamps.pop_front();
    }
    mutex.unlock();
}


void ImageLogger::saveImageBurst(void)
{
    mutex.lock();
    std::cout << "<saveImageBurst>" << std::endl;
    burstLoggerIsActive = false;
    int count = 0;
    while (!listOfImages.empty())
    {
        std::vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(0);
        qint64 timestamp = listOfTimeStamps.front();
        QString targetFilename = QString::number(timestamp) + ".png";
        count++;
        std::string pathToFile = pngImageDir->filePath(targetFilename).toStdString();
        std::cout << "Writing image to: \"" << pathToFile << "\" " << std::endl;
        // TODO: Check for enough space
        cv::Mat imageToWrite = listOfImages.front();
        cv::imwrite(pathToFile, imageToWrite, compression_params);
        listOfImages.pop_front();
        listOfTimeStamps.pop_front();
    }
    burstLoggerIsActive = true;
    std::cout << "</saveImageBurst>" << std::endl;
    mutex.unlock();
}

