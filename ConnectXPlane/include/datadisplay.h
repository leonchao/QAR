#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QWidget>
#include "ui_datadisplay.h"
#include "datarefmodel.h"
#include <QEvent>

class DataDisplay : public QWidget
{
	Q_OBJECT

public:
	DataDisplay(QWidget *parent = 0);
	~DataDisplay();

	void addOneRow(QString name, int index, float value);
	void setRowData(QString name, float value);
	void setTableData(QMap<QString, dref_struct_out> dataMap);
	void clearTableData();



private:
	Ui::DataDisplay ui;
	DatarefModel *model;
};

#endif // DATADISPLAY_H
