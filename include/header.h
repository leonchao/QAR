#ifndef HEADER_H
#define HEADER_H

#include <QMap>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QVector>
#include <QList>
#include <string>

const int QARDomainId = 1;
const std::string QARDataTopic = "QARData";
const std::string QARAircraftTopic = "QARAircraft";


#ifdef _DEBUG
#include <QDebug>
#endif

#endif // !HEADER_H