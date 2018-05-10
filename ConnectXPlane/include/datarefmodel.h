#ifndef DATAREFMODEL_H
#define DATAREFMODEL_H

#include <QAbstractTableModel>
#include "struct.h"
#include <QMap>

class DatarefModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	DatarefModel(QObject *parent);
	~DatarefModel();

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void setHeaderLabels(QStringList headers);
	void addOneRow(const QString drefStr,const dref_struct_out data);
	void updateValue(const QString drefStr, const float value);
	void updateValue(QMap<QString, dref_struct_out> dataMap);
	void clearData();
	QString nameAt(int offset) const;
	QString indexAt(int offset) const;
	QString valueAt(int offset) const;

private:
	QMap<QString, dref_struct_out> dataMap;
	QStringList header;
};

#endif // DATAREFMODEL_H
