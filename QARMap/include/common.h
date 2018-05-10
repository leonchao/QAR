#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

typedef struct AircraftInfo
{
    QString aircraftNum;    //航班号
    QString tailNumber;     //飞机尾号
    float latitude;         //纬度
    float longitude;        //经度
    float altitude;         //高度
    float rotation;         //朝向
    float speed;            //速度
    bool isFault;           //是否故障
    int warningKind;
    int warningLevel;
//    AircraftInfo()
//    {
//        aircraftNum = "";
//        latitude = 0.0f;
//        longitude = 0.0f;
//        altitude = 0.0f;
//        rotation = 0.0f;
//        isFault = false;
//    }
}Aircraft_Info;



#pragma pack(1)
struct GPS_Position
{
    quint32 fsxStatus;
    quint32 ulLockedSatCnt;
    double dLongitude;
    double dLatitude;
    double dAltitude;
    double dSpeed;
    double dGpsTime;
    double dMagenetic;
    double dDirection;
    unsigned char ucNorSInd;
    unsigned char ucEorInd;
    unsigned char aucRcvd[2];
    GPS_Position()
    {
        memset(this,0,sizeof(GPS_Position));
    }
};
#pragma pack()

inline QString structToJson(const AircraftInfo &info)
{
    QJsonObject json;
    json.insert("name",info.aircraftNum);
    json.insert("tailNumber",info.tailNumber);
    json.insert("latitude",info.latitude);
    json.insert("longitude",info.longitude);
    json.insert("altitude",info.altitude);
    json.insert("rotation",info.rotation);
    json.insert("speed",info.speed);
    json.insert("isfault",info.isFault);
    json.insert("warningKind",info.warningKind);
    json.insert("warningLevel",info.warningLevel);
    QJsonDocument document;
    document.setObject(json);
    QByteArray data = document.toJson(QJsonDocument::Compact);
    return QString(data);
}

#endif // COMMON_H
