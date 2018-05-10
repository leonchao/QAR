#include "filereader.h"
#include <QDebug>
#include <QTime>

FileReader::FileReader(QObject *parent)
	: QThread(parent)
{
	
}

FileReader::~FileReader()
{

}

void FileReader::run()
{
	if (!readFileData())
		return;
	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()),Qt::DirectConnection);
	timer->start(1000);
	
	exec();
}

void FileReader::OpenFile(QString fileName)
{
	this->fileName = fileName;
	this->start();
	started = true;
}

void FileReader::StopReader()
{
	started = false;
	this->exit();
	this->wait();
}

void FileReader::SetSpeed(int speed)
{
	this->speed = speed;
}

bool FileReader::readFileData()
{
	QTime time;
	time.start();
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "file open failed";
		return false;
	}
	qDebug() << "starting read csv file";
	QString strAll = file.readAll();
	file.close();
	QStringList alllines = strAll.split("\r\n");
	qDebug() << "read all coast" << time.elapsed() << "ms";
	//去掉最后一行空行
	alllines.takeAt(alllines.size() - 1);
	QString headers = alllines.takeAt(0);
	QStringList headerList = headers.split(',');
	for (const QString line : alllines)
	{
		QAROriginData qarData;
		QMap<QString, QString> dataMap;
		QStringList lineItems = line.split(',');
		for (int i = 0; i < lineItems.count(); ++i)
		{
			QString key = headerList.at(i);
			dataMap[key] = lineItems.at(i);
		}
		qarData.ADR_IN_FLT = dataMap["3ADR_IN_FLT"].toFloat();
		qarData.AFT_CGO_HT_INS = dataMap["AFT_CGO_HT_INS"].toFloat();
		qarData.AILERON_LEFT_1 = dataMap["AILERON_LEFT_1"].toFloat();
		qarData.AILERON_LEFT_2 = dataMap["AILERON_LEFT_2"].toFloat();
		qarData.AILERON_RGHT_1 = dataMap["AILERON_RGHT_1"].toFloat();
		qarData.AILERON_RGHT_2 = dataMap["AILERON_RGHT_2"].toFloat();
		qarData.ALT_SEL = dataMap["ALT_SEL"].toFloat();
		qarData.ALT_STD_LSH = dataMap["ALT_STD_LSH"].toFloat();
		qarData.ALT_STD_MSH = dataMap["ALT_STD_MSH"].toFloat();
		qarData.AOAMAX = dataMap["AOAMAX"].toFloat();
		qarData.AOA_ADC_1 = dataMap["AOA_ADC_1"].toFloat();
		qarData.AOA_ADC_2 = dataMap["AOA_ADC_2"].toFloat();
		qarData.AOA_LH = dataMap["AOA_LH"].toFloat();
		qarData.AOA_PROT = dataMap["AOA_PROT"].toFloat();
		qarData.AOA_RH = dataMap["AOA_RH"].toFloat();
		qarData.AOA_VOTED = dataMap["AOA_VOTED"].toFloat();
		qarData.AP1_INST_DISC = dataMap["AP1_INST_DISC"].toFloat();
		qarData.AP2_INST_DISC = dataMap["AP2_INST_DISC"].toFloat();
		qarData.APPR_DH_CA = dataMap["APPR_DH_CA"].toFloat();
		qarData.APPR_DH_FO = dataMap["APPR_DH_FO"].toFloat();
		qarData.APPR_TYPE = dataMap["APPR_TYPE"].toFloat();
		qarData.APU_GEN_FLT = dataMap["APU_GEN_FLT"].toFloat();
		qarData.AP_1 = dataMap["AP_1"].toFloat();
		qarData.AP_2 = dataMap["AP_2"].toFloat();
		qarData.AP_FD_TCAS_ARM = dataMap["AP_FD_TCAS_ARM"].toFloat();
		qarData.AP_FD_TCAS_EGD = dataMap["AP_FD_TCAS_EGD"].toFloat();
		qarData.AP_OFF_VOLUNT = dataMap["AP_OFF_VOLUNT"].toFloat();
		qarData.AP_OFF_WARN = dataMap["AP_OFF_WARN"].toFloat();
		qarData.ATS1_INST_DISC = dataMap["ATS1_INST_DISC"].toFloat();
		qarData.ATS2_INST_DISC = dataMap["ATS2_INST_DISC"].toFloat();
		qarData.AUTBRK_FAULT_1 = dataMap["AUTBRK_FAULT_1"].toFloat();
		qarData.AUTBRK_FAULT_2 = dataMap["AUTBRK_FAULT_2"].toFloat();
		qarData.AUTBRK_OFF_1 = dataMap["AUTBRK_OFF_1"].toFloat();
		qarData.AUTBRK_OFF_2 = dataMap["AUTBRK_OFF_2"].toFloat();
		qarData.AUTO_LAND_WN = dataMap["AUTO_LAND_WN"].toFloat();
		qarData.BACKUP_SPD_ACT = dataMap["BACKUP_SPD_ACT"].toFloat();
		qarData.BACKUP_SPD_VAL = dataMap["BACKUP_SPD_VAL"].toFloat();
		qarData.BACK_ALTI_GPS = dataMap["BACK_ALTI_GPS"].toFloat();
		qarData.BAT1_VOLTAGE = dataMap["BAT1_VOLTAGE"].toFloat();
		qarData.BAT2_VOLTAGE = dataMap["BAT2_VOLTAGE"].toFloat();
		qarData.BNO = dataMap["BNO"];
		qarData.BRAKE_MODE = dataMap["BRAKE_MODE"].toFloat();
		qarData.BRK_FAN_INSTAL = dataMap["BRK_FAN_INSTAL"].toFloat();
		qarData.BRK_SEL_V_FT1 = dataMap["BRK_SEL_V_FT1"].toFloat();
		qarData.BRK_TEMP1 = dataMap["BRK_TEMP1"].toFloat();
		qarData.BRK_TEMP2 = dataMap["BRK_TEMP2"].toFloat();
		qarData.BRK_TEMP3 = dataMap["BRK_TEMP3"].toFloat();
		qarData.BRK_TEMP4 = dataMap["BRK_TEMP4"].toFloat();
		qarData.BSCU1_EGD = dataMap["BSCU1_EGD"].toFloat();
		qarData.BSCU2_EGD = dataMap["BSCU2_EGD"].toFloat();
		qarData.CALL_BY_ADV = dataMap["CALL_BY_ADV"].toFloat();
		qarData.CAS_L = dataMap["CAS_L"].toFloat();
		qarData.Cabin_V_S_SYS_2 = dataMap["Cabin_V/S_SYS.2"].toFloat();
		qarData.Cabin_pressurization_warning = dataMap["Cabin_pressurization_warning"].toFloat();
		qarData.Constraint_Altitude = dataMap["Constraint_Altitude"].toFloat();
		qarData.DECEL_LOW_CA = dataMap["DECEL_LOW_CA"].toFloat();
		qarData.DECEL_LOW_FO = dataMap["DECEL_LOW_FO"].toFloat();
		qarData.DECEL_MAX_CA = dataMap["DECEL_MAX_CA"].toFloat();
		qarData.DECEL_MAX_FO = dataMap["DECEL_MAX_FO"].toFloat();
		qarData.DECEL_MID_CA = dataMap["DECEL_MID_CA"].toFloat();
		qarData.DECEL_MID_FO = dataMap["DECEL_MID_FO"].toFloat();
		qarData.DEC_HEIGHT = dataMap["DEC_HEIGHT"].toFloat();
		qarData.DH_MDAMDH_CA_LSH = dataMap["DH_MDAMDH_CA_LSH"].toFloat();
		qarData.DH_MDAMDH_FO = dataMap["DH_MDAMDH_FO"].toFloat();
		qarData.DISC_AP_MSG_CA = dataMap["DISC_AP_MSG_CA"].toFloat();
		qarData.DMC_Mark_Ident = dataMap["DMC_Mark_Ident"].toFloat();
		qarData.DME1_Frequency = dataMap["DME1_Frequency"].toFloat();
		qarData.DME2_Frequency = dataMap["DME2_Frequency"].toFloat();
		qarData.DTYPE = dataMap["DTYPE"];
		qarData.ECAM_DU1_Anomaly_Off = dataMap["ECAM_DU1_Anomaly/Off"].toFloat();
		qarData.ECAM_DU2_Anomaly_Off = dataMap["ECAM_DU2_Anomaly/Off"].toFloat();
		qarData.ECU_EEC1_channel_B_in_CTL = dataMap["ECU/EEC1_channel_B_in_CTL"].toFloat();
		qarData.ECU_EEC2_channel_B_in_CTL = dataMap["ECU/EEC2_channel_B_in_CTL"].toFloat();
		qarData.EFIS_Mode_Selection_ARC_Capt = dataMap["EFIS_Mode_Selection_ARC_Capt"].toFloat();
		qarData.EFIS_Mode_Selection_PLAN_Capt = dataMap["EFIS_Mode_Selection_PLAN_Capt"].toFloat();
		qarData.EFIS_Mode_Selection_ROSE_ILS_Capt = dataMap["EFIS_Mode_Selection_ROSE-ILS_Capt"].toFloat();
		qarData.EFIS_Mode_Selection_ROSE_NAV_Capt = dataMap["EFIS_Mode_Selection_ROSE-NAV_Capt"].toFloat();
		qarData.EFIS_Mode_Selection_ROSE_VOR_Capt = dataMap["EFIS_Mode_Selection_ROSE-VOR_Capt"].toFloat();
		qarData.EGT1 = dataMap["EGT1"].toFloat();
		qarData.EGT2 = dataMap["EGT2"].toFloat();
		qarData.ELAC1_fault = dataMap["ELAC1_fault"].toFloat();
		qarData.ELAC1_pitch_fault = dataMap["ELAC1_pitch_fault"].toFloat();
		qarData.ELAC1_roll_fault = dataMap["ELAC1_roll_fault"].toFloat();
		qarData.ELAC2_fault = dataMap["ELAC2_fault"].toFloat();
		qarData.ELAC2_pitch_fault = dataMap["ELAC2_pitch_fault"].toFloat();
		qarData.ELAC2_roll_fault = dataMap["ELAC2_roll_fault"].toFloat();
		qarData.ELEV_L_1 = dataMap["ELEV_L_1"].toFloat();
		qarData.ELEV_L_2 = dataMap["ELEV_L_2"].toFloat();
		qarData.ELEV_R_1 = dataMap["ELEV_R_1"].toFloat();
		qarData.ELEV_R_2 = dataMap["ELEV_R_2"].toFloat();
		qarData.EMER_GEN_LINE = dataMap["EMER_GEN_LINE"].toFloat();
		qarData.ENG1_MOD_SEL = dataMap["ENG1_MOD_SEL"].toFloat();
		qarData.ENG2_MOD_SEL = dataMap["ENG2_MOD_SEL"].toFloat();
		qarData.ESNL1 = dataMap["ESNL1"].toFloat();
		qarData.ESNL2 = dataMap["ESNL2"].toFloat();
		qarData.ESNL3 = dataMap["ESNL3"].toFloat();
		qarData.ESNL4 = dataMap["ESNL4"].toFloat();
		qarData.ESNL5 = dataMap["ESNL5"].toFloat();
		qarData.ESNL6 = dataMap["ESNL6"].toFloat();
		qarData.ESNR1 = dataMap["ESNR1"].toFloat();
		qarData.ESNR2 = dataMap["ESNR2"].toFloat();
		qarData.ESNR3 = dataMap["ESNR3"].toFloat();
		qarData.ESNR4 = dataMap["ESNR4"].toFloat();
		qarData.ESNR5 = dataMap["ESNR5"].toFloat();
		qarData.ESNR6 = dataMap["ESNR6"].toFloat();
		qarData.Eng1_Fire = dataMap["Eng1_Fire"].toFloat();
		qarData.Eng2_Fire = dataMap["Eng2_Fire"].toFloat();
		qarData.Event_Marker = dataMap["Event_Marker"].toFloat();
		qarData.FCU_ALT_CHANGE = dataMap["FCU_ALT_CHANGE"].toFloat();
		qarData.FCU_ALT_PULL = dataMap["FCU_ALT_PULL"].toFloat();
		qarData.FCU_ALT_PUSH = dataMap["FCU_ALT_PUSH"].toFloat();
		qarData.FCU_APPR_PB = dataMap["FCU_APPR_PB"].toFloat();
		qarData.FCU_DATA_DW = dataMap["FCU_DATA_DW"].toFloat();
		qarData.FCU_DATA_UP = dataMap["FCU_DATA_UP"].toFloat();
		qarData.FCU_DAT_LH = dataMap["FCU_DAT_LH"].toFloat();
		qarData.FCU_DAT_RH = dataMap["FCU_DAT_RH"].toFloat();
		qarData.FCU_EXPED_PB = dataMap["FCU_EXPED_PB"].toFloat();
		qarData.FCU_FCU1_FAIL = dataMap["FCU_FCU1_FAIL"].toFloat();
		qarData.FCU_FCU1_HEAL = dataMap["FCU_FCU1_HEAL"].toFloat();
		qarData.FCU_FCU1_SEL = dataMap["FCU_FCU1_SEL"].toFloat();
		qarData.FCU_FCU2_FAIL = dataMap["FCU_FCU2_FAIL"].toFloat();
		qarData.FCU_FCU2_HEAL = dataMap["FCU_FCU2_HEAL"].toFloat();
		qarData.FCU_FCU2_SEL = dataMap["FCU_FCU2_SEL"].toFloat();
		qarData.FCU_FDOFF_LH = dataMap["FCU_FDOFF_LH"].toFloat();
		qarData.FCU_FDOFF_RH = dataMap["FCU_FDOFF_RH"].toFloat();
		qarData.FCU_FMGC1_FAIL = dataMap["FCU_FMGC1_FAIL"].toFloat();
		qarData.FCU_FMGC1_SEL = dataMap["FCU_FMGC1_SEL"].toFloat();
		qarData.FCU_FMGC2_FAIL = dataMap["FCU_FMGC2_FAIL"].toFloat();
		qarData.FCU_FMGC2_SEL = dataMap["FCU_FMGC2_SEL"].toFloat();
		qarData.FCU_FPA_SEL = dataMap["FCU_FPA_SEL"].toFloat();
		qarData.FCU_LAT_PULL = dataMap["FCU_LAT_PULL"].toFloat();
		qarData.FCU_LAT_PUSH = dataMap["FCU_LAT_PUSH"].toFloat();
		qarData.FCU_LAT_SET = dataMap["FCU_LAT_SET"].toFloat();
		qarData.FCU_LOC_PRES = dataMap["FCU_LOC_PRES"].toFloat();
		qarData.FCU_METRIC_SEL = dataMap["FCU_METRIC_SEL"].toFloat();
		qarData.FCU_POW_PULSE = dataMap["FCU_POW_PULSE"].toFloat();
		qarData.FCU_SPD_CHANGE = dataMap["FCU_SPD_CHANGE"].toFloat();
		qarData.FCU_SPD_PB = dataMap["FCU_SPD_PB"].toFloat();
		qarData.FCU_SPD_PULL = dataMap["FCU_SPD_PULL"].toFloat();
		qarData.FCU_SPD_PUSH = dataMap["FCU_SPD_PUSH"].toFloat();
		qarData.FCU_VRT_CHANGE = dataMap["FCU_VRT_CHANGE"].toFloat();
		qarData.FCU_VRT_PULL = dataMap["FCU_VRT_PULL"].toFloat();
		qarData.FCU_VRT_PUSH = dataMap["FCU_VRT_PUSH"].toFloat();
		qarData.FCU_V_S_SEL = dataMap["FCU_V_S_SEL"].toFloat();
		qarData.FDPTCH_CA_1 = dataMap["FDPTCH_CA_1"].toFloat();
		qarData.FDPTCH_CA_2 = dataMap["FDPTCH_CA_2"].toFloat();
		qarData.FDPTCH_CA_3 = dataMap["FDPTCH_CA_3"].toFloat();
		qarData.FDPTCH_CA_4 = dataMap["FDPTCH_CA_4"].toFloat();
		qarData.FDROLL_CA_1 = dataMap["FDROLL_CA_1"].toFloat();
		qarData.FDROLL_CA_2 = dataMap["FDROLL_CA_2"].toFloat();
		qarData.FDROLL_CA_3 = dataMap["FDROLL_CA_3"].toFloat();
		qarData.FDROLL_CA_4 = dataMap["FDROLL_CA_4"].toFloat();
		qarData.FDYAW_CA_1 = dataMap["FDYAW_CA_1"].toFloat();
		qarData.FDYAW_CA_2 = dataMap["FDYAW_CA_2"].toFloat();
		qarData.FDYAW_CA_3 = dataMap["FDYAW_CA_3"].toFloat();
		qarData.FDYAW_CA_4 = dataMap["FDYAW_CA_4"].toFloat();
		qarData.FD_1 = dataMap["FD_1"].toFloat();
		qarData.FD_2 = dataMap["FD_2"].toFloat();
		qarData.FFKG1 = dataMap["FFKG1"].toFloat();
		qarData.FFKG2 = dataMap["FFKG2"].toFloat();
		qarData.FIRE_APU = dataMap["FIRE_APU"].toFloat();
		qarData.FLARE_LAW_ACT = dataMap["FLARE_LAW_ACT"].toFloat();
		qarData.FLT_NO1 = dataMap["FLT_NO1"];
		qarData.FLT_NO2 = dataMap["FLT_NO2"];
		qarData.FLT_NO3 = dataMap["FLT_NO3"];
		qarData.FLT_NO4 = dataMap["FLT_NO4"];
		qarData.FLT_NO5 = dataMap["FLT_NO5"];
		qarData.FLT_NO6 = dataMap["FLT_NO6"];
		qarData.FLT_NO7 = dataMap["FLT_NO7"];
		qarData.FLT_NO8 = dataMap["FLT_NO8"];
		qarData.FMA_MSG_CK_AP = dataMap["FMA_MSG_CK_AP"].toFloat();
		qarData.FMA_MSG_CONF = dataMap["FMA_MSG_CONF"].toFloat();
		qarData.FMA_MSG_DECEL = dataMap["FMA_MSG_DECEL"].toFloat();
		qarData.FMA_MSG_DEG = dataMap["FMA_MSG_DEG"].toFloat();
		qarData.FMA_MSG_DISC = dataMap["FMA_MSG_DISC"].toFloat();
		qarData.FMA_MSG_DRAG = dataMap["FMA_MSG_DRAG"].toFloat();
		qarData.FMA_MSG_GEAR = dataMap["FMA_MSG_GEAR"].toFloat();
		qarData.FMA_MSG_G_D = dataMap["FMA_MSG_G_D"].toFloat();
		qarData.FMA_MSG_HOLD = dataMap["FMA_MSG_HOLD"].toFloat();
		qarData.FMA_MSG_M_A = dataMap["FMA_MSG_M_A"].toFloat();
		qarData.FMA_MSG_NAVA = dataMap["FMA_MSG_NAVA"].toFloat();
		qarData.FMA_MSG_UPG = dataMap["FMA_MSG_UPG"].toFloat();
		qarData.FPA = dataMap["FPA"].toFloat();
		qarData.FPA_SELECTED = dataMap["FPA_SELECTED"].toFloat();
		qarData.FRAME_COUNTER = dataMap["FRAME_COUNTER"].toFloat();
		qarData.FROM1 = dataMap["FROM1"];
		qarData.FROM2 = dataMap["FROM2"];
		qarData.FROM2_0 = dataMap["FROM2_0"];
		qarData.FROM3 = dataMap["FROM3"];
		qarData.FROM4 = dataMap["FROM4"];
		qarData.FUEL_QUANTITY = dataMap["FUEL_QUANTITY"].toFloat();
		qarData.FWC_WARN_MSG1_1 = dataMap["FWC_WARN_MSG1_1"].toFloat();
		qarData.FWC_WARN_MSG1_2 = dataMap["FWC_WARN_MSG1_2"].toFloat();
		qarData.FWC_WARN_MSG1_3 = dataMap["FWC_WARN_MSG1_3"].toFloat();
		qarData.FWC_WARN_MSG1_4 = dataMap["FWC_WARN_MSG1_4"].toFloat();
		qarData.FWC_WARN_MSG1_5 = dataMap["FWC_WARN_MSG1_5"].toFloat();
		qarData.FWC_WARN_MSG1_6 = dataMap["FWC_WARN_MSG1_6"].toFloat();
		qarData.FWC_WARN_MSG1_7 = dataMap["FWC_WARN_MSG1_7"].toFloat();
		qarData.FWC_WARN_MSG1_8 = dataMap["FWC_WARN_MSG1_8"].toFloat();
		qarData.FWC_WARN_MSG2_1 = dataMap["FWC_WARN_MSG2_1"].toFloat();
		qarData.FWC_WARN_MSG2_2 = dataMap["FWC_WARN_MSG2_2"].toFloat();
		qarData.FWC_WARN_MSG2_3 = dataMap["FWC_WARN_MSG2_3"].toFloat();
		qarData.FWC_WARN_MSG2_4 = dataMap["FWC_WARN_MSG2_4"].toFloat();
		qarData.FWC_WARN_MSG2_5 = dataMap["FWC_WARN_MSG2_5"].toFloat();
		qarData.FWC_WARN_MSG2_6 = dataMap["FWC_WARN_MSG2_6"].toFloat();
		qarData.FWC_WARN_MSG2_7 = dataMap["FWC_WARN_MSG2_7"].toFloat();
		qarData.FWC_WARN_MSG2_8 = dataMap["FWC_WARN_MSG2_8"].toFloat();
		qarData.F_APP_MSG_CA = dataMap["F_APP_MSG_CA"].toFloat();
		qarData.F_APP_RAW_CA = dataMap["F_APP_RAW_CA"].toFloat();
		qarData.GAZ_OXY_PAX_IN = dataMap["GAZ_OXY_PAX_IN"].toFloat();
		qarData.GD_SPOIL_ARM_1 = dataMap["GD_SPOIL_ARM_1"].toFloat();
		qarData.GD_SPOIL_ARM_2 = dataMap["GD_SPOIL_ARM_2"].toFloat();
		qarData.GEN1_LINE_PB = dataMap["GEN1_LINE_PB"].toFloat();
		qarData.GLA_MLA_ACT = dataMap["GLA_MLA_ACT"].toFloat();
		qarData.GND_FLT_BOOLEA = dataMap["GND_FLT_BOOLEA"].toFloat();
		qarData.GPWS_ALERTS = dataMap["GPWS_ALERTS"].toFloat();
		qarData.GPWS_VA_ON = dataMap["GPWS_VA_ON"].toFloat();
		qarData.GW_LSH = dataMap["GW_LSH"].toFloat();
		qarData.GW_MSH = dataMap["GW_MSH"].toFloat();
		qarData.HDG_VS_SEL = dataMap["HDG_VS_SEL"].toFloat();
		qarData.HEADING_SEL = dataMap["HEADING_SEL"].toFloat();
		qarData.HF_1_EMITTING = dataMap["HF_1_EMITTING"].toFloat();
		qarData.HIGHSPDT = dataMap["HIGHSPDT"].toFloat();
		qarData.HI_ALT_PB = dataMap["HI_ALT_PB"].toFloat();
		qarData.HPV_ENG1 = dataMap["HPV_ENG1"].toFloat();
		qarData.HPV_ENG2 = dataMap["HPV_ENG2"].toFloat();
		qarData.HYD_L_PRES_B = dataMap["HYD_L_PRES_B"].toFloat();
		qarData.HYD_L_PRES_G = dataMap["HYD_L_PRES_G"].toFloat();
		qarData.HYD_L_PRES_Y = dataMap["HYD_L_PRES_Y"].toFloat();
		qarData.ILS1_Frequency = dataMap["ILS1_Frequency"].toFloat();
		qarData.ILS2_Frequency = dataMap["ILS2_Frequency"].toFloat();
		qarData.ILS_SEL_CRS1 = dataMap["ILS_SEL_CRS1"].toFloat();
		qarData.ILS_SEL_CRS2 = dataMap["ILS_SEL_CRS2"].toFloat();
		qarData.INNER_M_ON_1 = dataMap["INNER_M_ON_1"].toFloat();
		qarData.INNER_M_ON_2 = dataMap["INNER_M_ON_2"].toFloat();
		qarData.LAND_2_CAPABILITY = dataMap["LAND_2_CAPABILITY"].toFloat();
		qarData.LAND_CAPAB_STS = dataMap["LAND_CAPAB_STS"].toFloat();
		qarData.LATG_1 = dataMap["LATG_1"].toFloat();
		qarData.LATG_2 = dataMap["LATG_2"].toFloat();
		qarData.LATG_3 = dataMap["LATG_3"].toFloat();
		qarData.LATG_4 = dataMap["LATG_4"].toFloat();
		qarData.LATP_LSH = dataMap["LATP_LSH"].toFloat();
		qarData.LATP_MSH = dataMap["LATP_MSH"].toFloat();
		qarData.LAT_RES_CA = dataMap["LAT_RES_CA"].toFloat();
		qarData.LDG_LH = dataMap["LDG_LH"].toFloat();
		qarData.LDG_NOSE = dataMap["LDG_NOSE"].toFloat();
		qarData.LDG_RH = dataMap["LDG_RH"].toFloat();
		qarData.LDG_UNLOKDW = dataMap["LDG_UNLOKDW"].toFloat();
		qarData.LG_BOGIE_L_L1 = dataMap["LG_BOGIE_L_L1"].toFloat();
		qarData.LG_BOGIE_R_L1 = dataMap["LG_BOGIE_R_L1"].toFloat();
		qarData.LG_COMP_L_L1 = dataMap["LG_COMP_L_L1"].toFloat();
		qarData.LG_COMP_M_L1 = dataMap["LG_COMP_M_L1"].toFloat();
		qarData.LG_COMP_N_L1 = dataMap["LG_COMP_N_L1"].toFloat();
		qarData.LG_COMP_R_L1 = dataMap["LG_COMP_R_L1"].toFloat();
		qarData.LG_DOOR_C_N_L1 = dataMap["LG_DOOR_C_N_L1"].toFloat();
		qarData.LG_DOOR_C_P_L1 = dataMap["LG_DOOR_C_P_L1"].toFloat();
		qarData.LG_DOOR_O_N_L1 = dataMap["LG_DOOR_O_N_L1"].toFloat();
		qarData.LG_DOOR_O_P_L1 = dataMap["LG_DOOR_O_P_L1"].toFloat();
		qarData.LG_FAULT_L1 = dataMap["LG_FAULT_L1"].toFloat();
		qarData.LG_IN_CTL_L1 = dataMap["LG_IN_CTL_L1"].toFloat();
		qarData.LG_M_DNLK_L1 = dataMap["LG_M_DNLK_L1"].toFloat();
		qarData.LG_SOL_E_N_L1 = dataMap["LG_SOL_E_N_L1"].toFloat();
		qarData.LG_SOL_E_P_L1 = dataMap["LG_SOL_E_P_L1"].toFloat();
		qarData.LG_SOL_R_N_L1 = dataMap["LG_SOL_R_N_L1"].toFloat();
		qarData.LG_SOL_R_P_L1 = dataMap["LG_SOL_R_P_L1"].toFloat();
		qarData.LND_3_FL_OPTIVE_CPT = dataMap["LND_3_FL_OPTIVE_CPT"].toFloat();
		qarData.LND_3_FL_PSV_CPBT = dataMap["LND_3_FL_PSV_CPBT"].toFloat();
		qarData.LONGG_1 = dataMap["LONGG_1"].toFloat();
		qarData.LONGG_2 = dataMap["LONGG_2"].toFloat();
		qarData.LONGG_3 = dataMap["LONGG_3"].toFloat();
		qarData.LONGG_4 = dataMap["LONGG_4"].toFloat();
		qarData.LONG_RES_CA = dataMap["LONG_RES_CA"].toFloat();
		qarData.LONP_LSH = dataMap["LONP_LSH"].toFloat();
		qarData.LONP_MSH = dataMap["LONP_MSH"].toFloat();
		qarData.LOWSPDT = dataMap["LOWSPDT"].toFloat();
		qarData.LOW_ENG_1_S1 = dataMap["LOW_ENG_1_S1"].toFloat();
		qarData.LOW_ENG_1_S2 = dataMap["LOW_ENG_1_S2"].toFloat();
		qarData.LOW_ENG_2_S1 = dataMap["LOW_ENG_2_S1"].toFloat();
		qarData.LOW_ENG_2_S2 = dataMap["LOW_ENG_2_S2"].toFloat();
		qarData.MACH = dataMap["MACH"].toFloat();
		qarData.MACH_SELECT = dataMap["MACH_SELECT"].toFloat();
		qarData.MAGNETIC_HEADING_IRS1_2 = dataMap["MAGNETIC HEADING IRS1/2"].toFloat();
		qarData.MAS_CAU_CA_CLR = dataMap["MAS_CAU_CA_CLR"].toFloat();
		qarData.MAS_WAR_CA_CLR = dataMap["MAS_WAR_CA_CLR"].toFloat();
		qarData.MDA_MDH_CA = dataMap["MDA_MDH_CA"].toFloat();
		qarData.MDA_MDH_FO = dataMap["MDA_MDH_FO"].toFloat();
		qarData.MIDDLE_M_ON_1 = dataMap["MIDDLE_M_ON_1"].toFloat();
		qarData.MIDDLE_M_ON_2 = dataMap["MIDDLE_M_ON_2"].toFloat();
		qarData.N11 = dataMap["N11"].toFloat();
		qarData.N12 = dataMap["N12"].toFloat();
		qarData.N2_1 = dataMap["N2_1"].toFloat();
		qarData.N2_2 = dataMap["N2_2"].toFloat();
		qarData.NO_DATA_BMC1 = dataMap["NO_DATA_BMC1"].toFloat();
		qarData.NO_DATA_BMC2 = dataMap["NO_DATA_BMC2"].toFloat();
		qarData.NWS_FAULT = dataMap["NWS_FAULT"].toFloat();
		qarData.NWS_ORDER_ANG_1 = dataMap["NWS_ORDER_ANG_1"].toFloat();
		qarData.NWS_ORDER_ANG_2 = dataMap["NWS_ORDER_ANG_2"].toFloat();
		qarData.NWS_ORDER_ANG_3 = dataMap["NWS_ORDER_ANG_3"].toFloat();
		qarData.NWS_ORDER_ANG_4 = dataMap["NWS_ORDER_ANG_4"].toFloat();
		qarData.NWS_ORDER_CA_1 = dataMap["NWS_ORDER_CA_1"].toFloat();
		qarData.NWS_ORDER_CA_2 = dataMap["NWS_ORDER_CA_2"].toFloat();
		qarData.NWS_ORDER_CA_3 = dataMap["NWS_ORDER_CA_3"].toFloat();
		qarData.NWS_ORDER_CA_4 = dataMap["NWS_ORDER_CA_4"].toFloat();
		qarData.NWS_ORDER_FO_1 = dataMap["NWS_ORDER_FO_1"].toFloat();
		qarData.NWS_ORDER_FO_2 = dataMap["NWS_ORDER_FO_2"].toFloat();
		qarData.NWS_ORDER_FO_3 = dataMap["NWS_ORDER_FO_3"].toFloat();
		qarData.NWS_ORDER_FO_4 = dataMap["NWS_ORDER_FO_4"].toFloat();
		qarData.NWS_SEL_V_FT1 = dataMap["NWS_SEL_V_FT1"].toFloat();
		qarData.NWS_WHEEL_ANG = dataMap["NWS_WHEEL_ANG"].toFloat();
		qarData.No_data_from_ECU_EEC1 = dataMap["No_data_from_ECU/EEC1"].toFloat();
		qarData.No_data_from_ECU_EEC2 = dataMap["No_data_from_ECU/EEC2"].toFloat();
		qarData.OIL_NO_LOW_PRESS_Eng1 = dataMap["OIL_NO_LOW_PRESS_Eng1"].toFloat();
		qarData.OIL_NO_LOW_PRESS_Eng2 = dataMap["OIL_NO_LOW_PRESS_Eng2"].toFloat();
		qarData.OIL_PRS_1 = dataMap["OIL_PRS_1"].toFloat();
		qarData.OIL_PRS_2 = dataMap["OIL_PRS_2"].toFloat();
		qarData.OIQDAR1 = dataMap["OIQDAR1"].toFloat();
		qarData.OIQDAR2 = dataMap["OIQDAR2"].toFloat();
		qarData.OIQ_1 = dataMap["OIQ_1"].toFloat();
		qarData.OIQ_2 = dataMap["OIQ_2"].toFloat();
		qarData.OUTER_M_ON_1 = dataMap["OUTER_M_ON_1"].toFloat();
		qarData.OUTER_M_ON_2 = dataMap["OUTER_M_ON_2"].toFloat();
		qarData.OVERSPEED_WARN = dataMap["OVERSPEED_WARN"].toFloat();
		qarData.PITCH_ATT_1 = dataMap["PITCH_ATT_1"].toFloat();
		qarData.PITCH_ATT_2 = dataMap["PITCH_ATT_2"].toFloat();
		qarData.PITCH_ATT_FO_1 = dataMap["PITCH_ATT_FO_1"].toFloat();
		qarData.PITCH_ATT_FO_2 = dataMap["PITCH_ATT_FO_2"].toFloat();
		qarData.PITCH_CAPT_1 = dataMap["PITCH_CAPT_1"].toFloat();
		qarData.PITCH_CAPT_2 = dataMap["PITCH_CAPT_2"].toFloat();
		qarData.PITCH_DISCR_WN = dataMap["PITCH_DISCR_WN"].toFloat();
		qarData.PITCH_FO_1 = dataMap["PITCH_FO_1"].toFloat();
		qarData.PITCH_FO_2 = dataMap["PITCH_FO_2"].toFloat();
		qarData.PITCH_RATE1_1 = dataMap["PITCH_RATE1_1"].toFloat();
		qarData.PITCH_RATE1_2 = dataMap["PITCH_RATE1_2"].toFloat();
		qarData.PITCH_RATE1_3 = dataMap["PITCH_RATE1_3"].toFloat();
		qarData.PITCH_RATE1_4 = dataMap["PITCH_RATE1_4"].toFloat();
		qarData.PITCH_VAL_CA = dataMap["PITCH_VAL_CA"].toFloat();
		qarData.PRESEL_FQ = dataMap["PRESEL_FQ"].toFloat();
		qarData.PRIORIT_LCK_CA_1 = dataMap["PRIORIT_LCK_CA_1"].toFloat();
		qarData.PRIORIT_LCK_CA_2 = dataMap["PRIORIT_LCK_CA_2"].toFloat();
		qarData.PRIORIT_LCK_CA_3 = dataMap["PRIORIT_LCK_CA_3"].toFloat();
		qarData.PRIORIT_LCK_CA_4 = dataMap["PRIORIT_LCK_CA_4"].toFloat();
		qarData.PRIORIT_LCK_FO_1 = dataMap["PRIORIT_LCK_FO_1"].toFloat();
		qarData.PRIORIT_LCK_FO_2 = dataMap["PRIORIT_LCK_FO_2"].toFloat();
		qarData.PRIORIT_LCK_FO_3 = dataMap["PRIORIT_LCK_FO_3"].toFloat();
		qarData.PRIORIT_LCK_FO_4 = dataMap["PRIORIT_LCK_FO_4"].toFloat();
		qarData.RALT1 = dataMap["RALT1"].toFloat();
		qarData.RALT1_2 = dataMap["RALT1_2"].toFloat();
		qarData.RALT2 = dataMap["RALT2"].toFloat();
		qarData.RALT2_2 = dataMap["RALT2_2"].toFloat();
		qarData.RAW_ONLY_CA = dataMap["RAW_ONLY_CA"].toFloat();
		qarData.RECORD_VERSION = dataMap["RECORD_VERSION"].toFloat();
		qarData.REV_DEPLOY1 = dataMap["REV_DEPLOY1"].toFloat();
		qarData.REV_DEPLOY2 = dataMap["REV_DEPLOY2"].toFloat();
		qarData.REV_UNLOCK1 = dataMap["REV_UNLOCK1"].toFloat();
		qarData.REV_UNLOCK2 = dataMap["REV_UNLOCK2"].toFloat();
		qarData.ROLL_ATT = dataMap["ROLL_ATT"].toFloat();
		qarData.ROLL_ATT_FO = dataMap["ROLL_ATT_FO"].toFloat();
		qarData.ROLL_CAPT_1 = dataMap["ROLL_CAPT_1"].toFloat();
		qarData.ROLL_CAPT_2 = dataMap["ROLL_CAPT_2"].toFloat();
		qarData.ROLL_DISCR_WN = dataMap["ROLL_DISCR_WN"].toFloat();
		qarData.ROLL_FO_1 = dataMap["ROLL_FO_1"].toFloat();
		qarData.ROLL_FO_2 = dataMap["ROLL_FO_2"].toFloat();
		qarData.ROLL_ORDER_1 = dataMap["ROLL_ORDER_1"].toFloat();
		qarData.ROLL_ORDER_2 = dataMap["ROLL_ORDER_2"].toFloat();
		qarData.ROLL_RATE1 = dataMap["ROLL_RATE1"].toFloat();
		qarData.RUDDER_1 = dataMap["RUDDER_1"].toFloat();
		qarData.RUDDER_2 = dataMap["RUDDER_2"].toFloat();
		qarData.RUDDER_PEDAL_1 = dataMap["RUDDER_PEDAL_1"].toFloat();
		qarData.RUDDER_PEDAL_2 = dataMap["RUDDER_PEDAL_2"].toFloat();
		qarData.RUD_PEDA_FORCE_1 = dataMap["RUD_PEDA_FORCE_1"].toFloat();
		qarData.RUD_PEDA_FORCE_2 = dataMap["RUD_PEDA_FORCE_2"].toFloat();
		qarData.RUD_POS_INPROV = dataMap["RUD_POS_INPROV"].toFloat();
		qarData.SAT = dataMap["SAT"].toFloat();
		qarData.SAT_FO = dataMap["SAT_FO"].toFloat();
		qarData.SDAC1_VALID = dataMap["SDAC1_VALID"].toFloat();
		qarData.SDAC2_VALID = dataMap["SDAC2_VALID"].toFloat();
		qarData.SEC1_PB = dataMap["SEC1_PB"].toFloat();
		qarData.SEC1_fault = dataMap["SEC1_fault"].toFloat();
		qarData.SEC2_PB = dataMap["SEC2_PB"].toFloat();
		qarData.SEC2_fault = dataMap["SEC2_fault"].toFloat();
		qarData.SEC3_PB = dataMap["SEC3_PB"].toFloat();
		qarData.SEC3_fault = dataMap["SEC3_fault"].toFloat();
		qarData.SEL_VERT_SPD = dataMap["SEL_VERT_SPD"].toFloat();
		qarData.SMOKE_AVION_1 = dataMap["SMOKE_AVION_1"].toFloat();
		qarData.SMOKE_AVION_2 = dataMap["SMOKE_AVION_2"].toFloat();
		qarData.SMOKE_CARGO_1 = dataMap["SMOKE_CARGO_1"].toFloat();
		qarData.SMOKE_CARGO_2 = dataMap["SMOKE_CARGO_2"].toFloat();
		qarData.SMOKE_LAVAT_1 = dataMap["SMOKE_LAVAT_1"].toFloat();
		qarData.SMOKE_LAVAT_2 = dataMap["SMOKE_LAVAT_2"].toFloat();
		qarData.SP1_L_1 = dataMap["SP1_L_1"].toFloat();
		qarData.SP1_L_2 = dataMap["SP1_L_2"].toFloat();
		qarData.SP1_L_3 = dataMap["SP1_L_3"].toFloat();
		qarData.SP1_L_4 = dataMap["SP1_L_4"].toFloat();
		qarData.SP1_R_1 = dataMap["SP1_R_1"].toFloat();
		qarData.SP1_R_2 = dataMap["SP1_R_2"].toFloat();
		qarData.SP1_R_3 = dataMap["SP1_R_3"].toFloat();
		qarData.SP1_R_4 = dataMap["SP1_R_4"].toFloat();
		qarData.SP2_L = dataMap["SP2_L"].toFloat();
		qarData.SP2_R = dataMap["SP2_R"].toFloat();
		qarData.SP3_L = dataMap["SP3_L"].toFloat();
		qarData.SP3_R = dataMap["SP3_R"].toFloat();
		qarData.SP4_L = dataMap["SP4_L"].toFloat();
		qarData.SP4_R = dataMap["SP4_R"].toFloat();
		qarData.SP5_L = dataMap["SP5_L"].toFloat();
		qarData.SP5_R = dataMap["SP5_R"].toFloat();
		qarData.SPARE_RED_W_13 = dataMap["SPARE_RED_W_13"].toFloat();
		qarData.SPARE_RED_W_14 = dataMap["SPARE_RED_W_14"].toFloat();
		qarData.SPARE_RED_W_15 = dataMap["SPARE_RED_W_15"].toFloat();
		qarData.SPD_BRAKE = dataMap["SPD_BRAKE"].toFloat();
		qarData.SPD_MACH_A_M = dataMap["SPD_MACH_A_M"].toFloat();
		qarData.SPD_SPD_WARN = dataMap["SPD_SPD_WARN"].toFloat();
		qarData.SSTICK_C_INOP = dataMap["SSTICK_C_INOP"].toFloat();
		qarData.SSTICK_FO_INOP = dataMap["SSTICK_FO_INOP"].toFloat();
		qarData.STAB = dataMap["STAB"].toFloat();
		qarData.STALL = dataMap["STALL"].toFloat();
		qarData.STALLSPD_1 = dataMap["STALLSPD_1"].toFloat();
		qarData.STALLSPD_2 = dataMap["STALLSPD_2"].toFloat();
		qarData.Spoiler1_position_valid = dataMap["Spoiler1_position_valid"].toFloat();
		qarData.Spoiler2_position_valid = dataMap["Spoiler2_position_valid"].toFloat();
		qarData.Spoiler3_position_valid = dataMap["Spoiler3_position_valid"].toFloat();
		qarData.Spoiler4_position_valid = dataMap["Spoiler4_position_valid"].toFloat();
		qarData.Spoiler5_position_valid = dataMap["Spoiler5_position_valid"].toFloat();
		qarData.TAIL_NO1 = dataMap["TAIL_NO1"];
		qarData.TAIL_NO2 = dataMap["TAIL_NO2"];
		qarData.TAIL_NO3 = dataMap["TAIL_NO3"];
		qarData.TAIL_NO4 = dataMap["TAIL_NO4"];
		qarData.TAIL_NO5 = dataMap["TAIL_NO5"];
		qarData.TAIL_NO6 = dataMap["TAIL_NO6"];
		qarData.TAIL_NO7 = dataMap["TAIL_NO7"];
		qarData.TCAS_CMB_CTR = dataMap["TCAS_CMB_CTR"].toFloat();
		qarData.TCAS_DWN_ADV = dataMap["TCAS_DWN_ADV"].toFloat();
		qarData.TCAS_RA_INHIB = dataMap["TCAS_RA_INHIB"].toFloat();
		qarData.TCAS_UP_ADV = dataMap["TCAS_UP_ADV"].toFloat();
		qarData.TCAS_VERT_CTR = dataMap["TCAS_VERT_CTR"].toFloat();
		qarData.TGT_SIDE_SLIP = dataMap["TGT_SIDE_SLIP"].toFloat();
		qarData.THROTT_ANG1 = dataMap["THROTT_ANG1"].toFloat();
		qarData.THROTT_ANG2 = dataMap["THROTT_ANG2"].toFloat();
		qarData.TO1 = dataMap["TO1"];
		qarData.TO2 = dataMap["TO2"];
		qarData.TO3 = dataMap["TO3"];
		qarData.TO3_0 = dataMap["TO3_0"];
		qarData.TO4 = dataMap["TO4"];
		qarData.TOWING_ON = dataMap["TOWING_ON"].toFloat();
		qarData.TO_THR_DISAGRE = dataMap["TO_THR_DISAGRE"].toFloat();
		qarData.TRACK_SEL = dataMap["TRACK_SEL"].toFloat();
		qarData.TRKANGTR = dataMap["TRKANGTR"].toFloat();
		qarData.TRK_FPA_SEL = dataMap["TRK_FPA_SEL"].toFloat();
		qarData.TRUE_HEADING = dataMap["TRUE HEADING"].toFloat();
		qarData.UTC_HOURS = dataMap["UTC_HOURS"].toFloat();
		qarData.UTC_MIN = dataMap["UTC_MIN"].toFloat();
		qarData.UTC_SEC = dataMap["UTC_SEC"].toFloat();
		qarData.VAPP = dataMap["VAPP"].toFloat();
		qarData.VAPP_BIS = dataMap["VAPP_BIS"].toFloat();
		qarData.VB11 = dataMap["VB11"].toFloat();
		qarData.VB12 = dataMap["VB12"].toFloat();
		qarData.VB21 = dataMap["VB21"].toFloat();
		qarData.VB22 = dataMap["VB22"].toFloat();
		qarData.VB_N1_ADV_1 = dataMap["VB_N1_ADV_1"].toFloat();
		qarData.VB_N1_ADV_2 = dataMap["VB_N1_ADV_2"].toFloat();
		qarData.VB_N2_ADV_1 = dataMap["VB_N2_ADV_1"].toFloat();
		qarData.VB_N2_ADV_2 = dataMap["VB_N2_ADV_2"].toFloat();
		qarData.VCTRENDS = dataMap["VCTRENDS"].toFloat();
		qarData.VHF_1_EMITTING = dataMap["VHF_1_EMITTING"].toFloat();
		qarData.VOR1_Frequency = dataMap["VOR1_Frequency"].toFloat();
		qarData.VOR2_Frequency = dataMap["VOR2_Frequency"].toFloat();
		qarData.VOR_MODE_ARM = dataMap["VOR_MODE_ARM"].toFloat();
		qarData.VOR_MODE_DIS = dataMap["VOR_MODE_DIS"].toFloat();
		qarData.VOR_MODE_EGD = dataMap["VOR_MODE_EGD"].toFloat();
		qarData.VRTG_1 = dataMap["VRTG_1"].toFloat();
		qarData.VRTG_2 = dataMap["VRTG_2"].toFloat();
		qarData.VRTG_3 = dataMap["VRTG_3"].toFloat();
		qarData.VRTG_4 = dataMap["VRTG_4"].toFloat();
		qarData.VRTG_5 = dataMap["VRTG_5"].toFloat();
		qarData.VRTG_6 = dataMap["VRTG_6"].toFloat();
		qarData.VRTG_7 = dataMap["VRTG_7"].toFloat();
		qarData.VRTG_8 = dataMap["VRTG_8"].toFloat();
		qarData.WINDIR = dataMap["WINDIR"].toFloat();
		qarData.WINSPD = dataMap["WINSPD"].toFloat();
		qarData.WSHEAR_ON_1 = dataMap["WSHEAR_ON_1"].toFloat();
		qarData.WSHEAR_ON_2 = dataMap["WSHEAR_ON_2"].toFloat();
		qarData.YAW = dataMap["YAW"].toFloat();
		qarData.YAW_DAMP1_SYS1_1 = dataMap["YAW_DAMP1_SYS1_1"].toFloat();
		qarData.YAW_DAMP1_SYS1_2 = dataMap["YAW_DAMP1_SYS1_2"].toFloat();
		qarData.YAW_DAMP2_SYS1_1 = dataMap["YAW_DAMP2_SYS1_1"].toFloat();
		qarData.YAW_DAMP2_SYS1_2 = dataMap["YAW_DAMP2_SYS1_2"].toFloat();
		qarData.YAW_RATE = dataMap["YAW_RATE"].toFloat();
		qarData.time = dataMap["time"];
		dataList.push_back(qarData);
	}
	qDebug() << "parse all coast" << time.elapsed() << "ms";
	qDebug() << "read csv file done";
	return true;
}

void FileReader::onTimeout()
{
	if (speed == 0)
	{
		return;
	}
	if (timer->interval() != (1000 / speed))
	{
		timer->stop();
		timer->start(1000 / speed);
		return;
	}
	if (dataList.isEmpty())
	{
		emit fileDone(fileName);
		return;
	}
	emit doGetQARData(dataList.takeFirst());

}

