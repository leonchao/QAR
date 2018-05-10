#include "qarparser.h"
#include <QListWidgetItem>
#include "endianess.h"

QARParser::QARParser(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.toolButton_listen, SIGNAL(clicked(bool)), this, SLOT(onStartListenning(bool)));
	connect(ui.toolButton_open_warning, SIGNAL(clicked(bool)), this, SLOT(onOpenWarning(bool)));
	connect(&receiver, SIGNAL(doGetQARData(QAROriginData)), this, SLOT(onGetQARData(QAROriginData)));
	receiver.startListening();
	/*reader = new FileReader();
	connect(reader, SIGNAL(doGetQARData(QARData)), this, SLOT(onGetQARData(QARData)));
	reader->OpenFile("C:/Users/000009/Documents/WeChat Files/LeonChao1992/Files/20180417183101353.csv");*/
	model = new QStringListModel(this);
	ui.listView->setModel(model);
	ui.listView->setSelectionMode(QAbstractItemView::SingleSelection);

	ui.listView->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui.listView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onListViewMenuRequest(const QPoint&)));

	listViewMenu = new QMenu(ui.listView);
	QAction *actionOpen = listViewMenu->addAction(QString::fromLocal8Bit("打开"));

	QAction *actionClose = listViewMenu->addAction(QString::fromLocal8Bit("关闭"));
	connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(openQARFile(bool)));
	connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(stopFileReader(bool)));
	//actionOpen->setCheckable(true);
	//actionClose->setCheckable(true);

	LoadFileInfo();
	qDebug() << QThread::currentThreadId();

	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSetReaderSpeed(int)));
	connect(&publisher, SIGNAL(doGetAircraftInfo(QARAircraft)), this, SLOT(onGetAircraftInfo(QARAircraft)));
	isWarningOpen = false;

	connect(&timer, SIGNAL(timeout()), this, SLOT(keepXHSIGaugeAlive()));
	timer.start(100);
}

QARParser::~QARParser()
{

}

void QARParser::closeEvent(QCloseEvent *event)
{
	/*reader->StopReader();
	delete reader;
	reader = NULL;*/
	for (auto iter = readerMap.begin(); iter != readerMap.end(); ++iter)
	{
		iter.value()->StopReader();
	}
	readerMap.clear();
	receiver.stopListenning();
}

void QARParser::LoadFileInfo()
{
	QDir fileDir("./");
	QStringList filterList;
	filterList << "*.csv";
	QFileInfoList infos = fileDir.entryInfoList(filterList, QDir::Files);
	for (int i = 0; i < infos.size(); i++)
	{
		fileList.append(infos[i].fileName());
	}
	model->setStringList(fileList);
}

void QARParser::sendADCDPakcet(const QAROriginData &data)
{
	SimDataPacket adcd_packet;
	strcpy(adcd_packet.packet_id, "ADCD");
	int adcdIndex = 0;
	/*adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(PLUGIN_VERSION_ID);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(PLUGIN_VERSION_NUMBER);
	adcdIndex++;*/
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_GROUNDSPEED);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.CAS_L - 4);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_TRUE_AIRSPEED);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.CAS_L);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_LATITUDE);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.LATP_LSH + data.LATP_MSH);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_LONGITUDE);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.LONP_LSH + data.LONP_MSH);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_ELEVATION);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.ALT_STD_LSH + data.ALT_STD_MSH);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_WEATHER_WIND_SPEED_KT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.WINSPD);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_WEATHER_WIND_DIRECTION_DEGT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.WINDIR);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_THETA);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.PITCH_ATT_1);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_PHI);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.ROLL_ATT);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_AIRSPEED_KTS_PILOT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.CAS_L);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_ALTITUDE_FT_PILOT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.ALT_STD_LSH + data.ALT_STD_MSH);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_ACTUATORS_RADIO_ALTIMETER_BUG_FT_PILOT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.RALT1 + data.RALT1_2);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_ACTUATORS_RADIO_ALTIMETER_BUG_FT_COPILOT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.RALT2 + data.RALT2_2);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_HPATH);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.TRUE_HEADING);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(XHSI_AIRCRAFT_GEAR_COUNT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(3);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(XHSI_AIRCRAFT_GEAR_DOOR_COUNT);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(3);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(XHSI_AIRCRAFT_GEAR_DOOR_DEPLOY_RATIO_ + 0);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.LG_M_DNLK_L1);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(XHSI_AIRCRAFT_GEAR_DOOR_DEPLOY_RATIO_ + 1);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.LG_M_DNLK_L1);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(XHSI_AIRCRAFT_GEAR_DOOR_DEPLOY_RATIO_ + 2);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.LG_M_DNLK_L1);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_AIRSPEED_ACCELERATION);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.VRTG_1);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_VPATH);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.TRUE_HEADING);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL_POSITION_ALPHA);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.AOA_ADC_1 + data.AOA_ADC_2);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_COCKPIT2_CONTROLS_GEAR_HANDLE_DOWN);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.LDG_NOSE);
	adcdIndex++;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(SIM_FLIGHTMODEL2_CONTROLS_SPEEDBRAKE_RATIO);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(data.SPD_BRAKE);
	adcdIndex++;

	adcd_packet.nb_of_sim_data_points = custom_htoni(adcdIndex);

	//qDebug() << "adcd packet" <<
	udpSocket.writeDatagram((char*)&adcd_packet, adcdIndex * 8 + 8, QHostAddress("127.0.0.1"), 49020);
}

void QARParser::sendAvionicsPacket(const QAROriginData &data)
{
	SimDataPacket avio_packet;
	strcpy(avio_packet.packet_id, "AVIO");
	int avioIndex = 0;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(JAR_A320NEO_STATUS);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf((float)0.0);    //仪表打开状态
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT_ELECTRICAL_AVIONICS_ON);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf((float)1.0);    //仪表打开状态
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT_AUTOPILOT_ALTITUDE);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.ALT_SEL);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_AIRSPEED_KTS_PILOT);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.CAS_L);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_AIRSPEED_KTS_COPILOT);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.CAS_L);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_ALTITUDE_FT_PILOT);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.ALT_STD_LSH + data.ALT_STD_MSH);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_ALTITUDE_FT_COPILOT);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.ALT_STD_LSH + data.ALT_STD_MSH);
	avioIndex++;

	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_SIDESLIP_DEGREES);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.TRUE_HEADING - data.HEADING_SEL);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_ACTUATORS_RADIO_ALTIMETER_BUG_FT_PILOT);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.RALT1+data.RALT1_2);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_ACTUATORS_RADIO_ALTIMETER_BUG_FT_COPILOT);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.RALT2+data.RALT2_2);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT_AUTOPILOT_HEADING_MAG);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.HEADING_SEL);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_GAUGES_INDICATORS_AIRSPEED_ACCELERATION);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.VRTG_1);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_ANNUNCIATORS_STALL_WARNING);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.STALL);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_CONTROLS_YOKE_PITCH_RATIO);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.PITCH_CAPT_1);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_CONTROLS_YOKE_ROLL_RATIO);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.ROLL_CAPT_1);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT2_CONTROLS_YOKE_HDG_RATIO);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.YAW);
	avioIndex++;
	avio_packet.sim_data_points[avioIndex].id = custom_htoni(SIM_COCKPIT_AUTOPILOT_AIRSPEED);
	avio_packet.sim_data_points[avioIndex].value = custom_htonf(data.SPD_MACH_A_M);
	avioIndex++;
	avio_packet.nb_of_sim_data_points = custom_htoni(avioIndex);
	//qDebug() << "avio packet" << 
	udpSocket.writeDatagram((char*)&avio_packet, avioIndex * 8 + 8, QHostAddress("127.0.0.1"), 49020);
}

void QARParser::sendCustomAvionicsPacket(const QAROriginData &data)
{
	
	//int i = 0;
	//int j = 0;
	//int packet_size;
	//char nav_id_bytes[4];
	//char qpac_ils_char[12];
	//int fcu_data;
	//int fcu_baro;
	//int ap_appr;
	//int qpac_ils;
	//int qpac_failures;
	//int qpac_spoilers_tab[20];
	//int spoilers;
	//int qpac_fcc_tab[5];
	//int qpac_fcc;
	//float qpac_hyd_press_tab[3];
	//float qpac_hyd_qty_tab[3];
	//int hyd_pumps = 0;
	//int qpac_hyd_pump_tab[3];
	//int qpac_fuel_pumps = 0;
	//int qpac_fuel_pump_tab[6];
	//int qpac_fuel_auto_pump_tab[6];
	//int qpac_fuel_valves = 0;
	//int qpac_fuel_valves_tab[6];
	//int qpac_air_valves;
	//// float ram_air_valve;
	//int bleed_valves;
	//float qpac_door_pax_tab[4];
	//float qpac_door_cargo_tab[4];
	//int elec_status;
	//int qpac_elec_buttons;
	//int qpac_elec_oph_tab[4];
	//float qpac_nacelle_temp_tab[4];
	//int qpac_ignition;
	//int qpac_start_valve_tab[4];
	//int qpac_sd_data_len;
	//int qpac_sd_line_len;
	//float qpac_vib_n2;
	//float qpac_temp;
	//int anti_ice;
	//float qpac_tyre_delta_t;
	//float qpac_tyre_pressure;

	//int auto_brake_level;
	//int brake_status;
	//int door_status;

	//int pa_a320_failures;
	//int xjoymap_stick;

	//SimDataPacket sim_packet;
	//strncpy(sim_packet.packet_id, "AVIO", 4);


	//sim_packet.sim_data_points[i].id = custom_htoni(UFMC_STATUS);
	//sim_packet.sim_data_points[i].value = custom_htonf((float)0);
	//i++;

	//sim_packet.sim_data_points[i].id = custom_htoni(X737_STATUS);
	//sim_packet.sim_data_points[i].value = custom_htonf((float)0);
	//i++;

	//sim_packet.sim_data_points[i].id = custom_htoni(CL30_STATUS);
	//sim_packet.sim_data_points[i].value = custom_htonf((float)0);
	//i++;
	//

	//sim_packet.sim_data_points[i].id = custom_htoni(QPAC_STATUS);
	//sim_packet.sim_data_points[i].value = custom_htonf((float)0);
	//i++;


	//sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_STATUS);
	//sim_packet.sim_data_points[i].value = custom_htonf((float)1);
	//i++;
	//if (1) {

	//	// Approach
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APPR_TYPE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_ap_appr_type));
	//	i++;
	//	// sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APPR_TYPE);
	//	// sim_packet.sim_data_points[i].value = custom_htonf((float) XPLMGetDatai(jar_a320_neo_ap_appr_illuminated));
	//	// i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APPR_DH);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_fma_dh_alt));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APPR_MDA);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_fma_mda_alt));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FMA_CAT);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_fma_cat_mode));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FMA_DUAL);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_fma_dual_mode));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FMA_DH);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_fma_dh_mode));
	//	i++;

	//	// FCU
	//	fcu_data =
	//		XPLMGetDatai(jar_a320_neo_ap1) << 8 |
	//		XPLMGetDatai(jar_a320_neo_ap2) << 7 |
	//		XPLMGetDatai(jar_a320_neo_hdg_managed) << 6 |
	//		XPLMGetDatai(jar_a320_neo_hdg_dashed) << 5 |
	//		XPLMGetDatai(jar_a320_neo_spd_managed) << 4 |
	//		XPLMGetDatai(jar_a320_neo_fd) << 3 |
	//		XPLMGetDatai(jar_a320_neo_vs_dashed) << 2 |
	//		XPLMGetDatai(jar_a320_neo_fcu_metric_alt) << 1 |
	//		XPLMGetDatai(jar_a320_neo_fcu_hdg_trk);
	//	fcu_baro =
	//		// XPLMGetDatai(qpac_baro_std_fo) << 6 |
	//		XPLMGetDatai(jar_a320_neo_baro_hpa) << 5 |
	//		// XPLMGetDatai(qpac_baro_hide_fo) << 4 |
	//		// XPLMGetDatai(qpac_baro_std_capt) << 2 |
	//		XPLMGetDatai(jar_a320_neo_baro_hpa) << 1  // |
	//		// XPLMGetDatai(qpac_baro_hide_capt)
	//		;
	//	ap_appr =
	//		XPLMGetDatai(jar_a320_neo_ap_loc_illuminated) << 1 |
	//		XPLMGetDatai(jar_a320_neo_ap_appr_illuminated);

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FCU);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)fcu_data);
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FCU_BARO);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)fcu_baro);
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APPR);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)ap_appr);
	//	i++;


	//	// Auto-pilot
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AP_PHASE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_ap_phase));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AP_VERTICAL_MODE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_vert_mode));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AP_VERTICAL_ARMED);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_vert_wait));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AP_LATERAL_MODE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_lat_mode));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AP_LATERAL_ARMED);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_lat_wait));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AP_COMMON_MODE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_com_mode));
	//	i++;
	//	// JAR_A320NEO_ALT_IS_CSTR
	//	// JAR_A320NEO_CONSTRAINT_ALT

	//	// Auto-Thrust
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_ATHR_MODE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_athr_mode));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_THR_MODE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_thr_mode));
	//	i++;
	//	// sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_ATHR_LIMITED);
	//	// sim_packet.sim_data_points[i].value = custom_htonf((float) XPLMGetDatai(qpac_athr_limited));
	//	// i++;
	//	// sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_THR_LEVER_MODE);
	//	// sim_packet.sim_data_points[i].value = custom_htonf((float) XPLMGetDatai(qpac_thr_lever_mode));
	//	// i++;
	//	// sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FMA_THR_WARNING);
	//	// sim_packet.sim_data_points[i].value = custom_htonf((float) XPLMGetDatai(qpac_fma_thr_warning));
	//	// i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FLEX_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_flex_t));
	//	i++;


	//	// V Speeds
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_V1);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_v1));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_VR);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_vr));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_VMO);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_vmax));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_VLS);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_vls));
	//	i++;
	//	//sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_VF);
	//	//sim_packet.sim_data_points[i].value = custom_htonf(qpac_ias_shift(XPLMGetDataf(qpac_vf)));
	//	//i++;
	//	//sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_VS);
	//	//sim_packet.sim_data_points[i].value = custom_htonf(qpac_ias_shift(XPLMGetDataf(qpac_vs)));
	//	//i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_V_GREEN_DOT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_vgrdot));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_ALPHA_PROT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_vaprot));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_ALPHA_MAX);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_vamax));
	//	i++;

	//	// EFIS
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_ND_MODE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_neo_nd_mode));
	//	i++;

	//	// Brakes
	//	if (XPLMGetDatai(jar_a320_neo_autobrake_low) == 1) {
	//		auto_brake_level = 1;
	//	}
	//	else if (XPLMGetDatai(jar_a320_neo_autobrake_med) == 1) {
	//		auto_brake_level = 2;
	//	}
	//	else if (XPLMGetDatai(jar_a320_neo_autobrake_max) == 1) {
	//		auto_brake_level = 4;
	//	}
	//	else {
	//		auto_brake_level = 0;
	//	}
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AUTO_BRAKE_LEVEL);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)auto_brake_level);
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_ACCU_PSI);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_brakes_accu_press));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_LEFT_PSI);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_brakes_left_press));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_RIGHT_PSI);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_brakes_right_press));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_TEMP_ + 0);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_wheels_temp_l_1));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_TEMP_ + 1);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_wheels_temp_l_2));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_TEMP_ + 2);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_wheels_temp_r_1));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_TEMP_ + 3);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_wheels_temp_r_2));
	//	i++;
	//	brake_status =
	//		XPLMGetDatai(jar_a320_neo_wheels_ped_disc) << 2 |
	//		XPLMGetDatai(jar_a320_neo_wheels_brake_fan) << 1 |
	//		XPLMGetDatai(jar_a320_neo_wheels_brake_hot);
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BRAKE_STATUS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)brake_status);
	//	i++;

	//	// Hydraulics
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_HYD_B_PRESS);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_hydr_b_press_aft_acc_old));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_HYD_G_PRESS);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_hydr_g_press_aft_acc_old));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_HYD_Y_PRESS);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_hydr_y_press_aft_acc_old));
	//	i++;
	//	// Hydraulic pumps
	//	// Each pump status is on ??? bits
	//	// jar_a320_neo_hydr_b_elec_pump_fault_light
	//	// jar_a320_neo_hydr_g_eng_pump_fault_light
	//	// jar_a320_neo_hydr_y_elec_pump_fault_light
	//	// jar_a320_neo_hydr_y_eng_pump_fault_light
	//	hyd_pumps =
	//		(XPLMGetDatai(jar_a320_neo_hydr_g_eng_pump_mode) & 0x01) |
	//		(XPLMGetDatai(jar_a320_neo_hydr_g_eng_pump_fault_light) & 0x01) << 1 |
	//		(XPLMGetDatai(jar_a320_neo_hydr_y_eng_pump_mode) & 0x01) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_hydr_y_eng_pump_fault_light) & 0x01) << 3 |
	//		(XPLMGetDatai(jar_a320_neo_hydr_b_elec_pump_mode) & 0x01) << 4 |
	//		(XPLMGetDatai(jar_a320_neo_hydr_b_elec_pump_fault_light) & 0x01) << 5;
	//	// Shift 6 bits left for rat, ptu and elec pumps
	//	// jar_a320_neo_hydr_ptu_delta is a float
	//	hyd_pumps <<= 6;
	//	hyd_pumps |=
	//		(XPLMGetDatai(qpac_hyd_rat_mode) & 0x03) |
	//		(XPLMGetDatai(jar_a320_neo_hydr_y_elec_pump_mode) & 0x01) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_hydr_y_elec_pump_fault_light) & 0x01) << 3 |
	//		(XPLMGetDatai(jar_a320_neo_hydr_ptu_mode) & 0x01) << 4;
	//	// (XPLMGetDatai(jar_a320_neo_hydr_ptu_delta) & 0x01) << 5;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_HYD_PUMPS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)hyd_pumps);
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_HYD_PTU);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_hydr_ptu_delta));
	//	i++;

	//	// Doors
	//	door_status = (XPLMGetDataf(jar_a320_neo_doors_c_b_now) > 0.01) |
	//		(XPLMGetDataf(jar_a320_neo_doors_c_f_now) > 0.01) << 1 |
	//		(XPLMGetDataf(jar_a320_neo_doors_p_b_l_now) > 0.01) << 2 |
	//		(XPLMGetDataf(jar_a320_neo_doors_p_b_r_now) > 0.01) << 3 |
	//		(XPLMGetDataf(jar_a320_neo_doors_p_f_l_now) > 0.01) << 4 |
	//		(XPLMGetDataf(jar_a320_neo_doors_p_f_r_now) > 0.01) << 5;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_DOOR_STATUS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)door_status);
	//	i++;

	//	// ATA 21 Conditioning
	//	// Cockpit
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_COCKPIT_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cockpit_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_INLET_COCKPIT_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cockpit_duct));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_COCKPIT_TRIM);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cockpit_trm_valve));
	//	i++;

	//	// Forward
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_FWD_CABIN_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_fwd_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_INLET_FWD1_CABIN_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_fwd_duct));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_ZONE1_TRIM);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_fwd_trm_valve));
	//	i++;

	//	// AFT
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_AFT_CABIN_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_aft_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_INLET_AFT1_CABIN_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_aft_duct));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_ZONE2_TRIM);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_aft_trm_valve));
	//	i++;

	//	// CARGO FWD
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_FWD_CARGO_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cargo_fwd_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_INLET_CARGO_FWD_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cargo_fwd_duct));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_CARGO_FWD_TRIM);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cargo_fwd_trm_valve));
	//	i++;

	//	// CARGO AFT
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_AFT_CARGO_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cargo_aft_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_INLET_CARGO_AFT_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cargo_aft_duct));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_CARGO_AFT_TRIM);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_cargo_aft_trm_valve));
	//	i++;

	//	// TODO: Valves
	//	// Hot air valves - bit arrays (2 bits per valve)
	//	// LSB order : Hot Air 1, Hot Air 2, Cargo 1, Cargo 2
	//	qpac_air_valves = ((XPLMGetDatai(jar_a320_neo_cond_hot_air) & 0x03)) |
	//		((XPLMGetDatai(jar_a320_neo_cond_cargo_hot_air) & 0x03) << 4);
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_HOT_AIR_VALVES);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)qpac_air_valves);
	//	i++;

	//	// PACKs
	//	// bit array (2 bits per valve) : LSB order : PACK 1, PACK 2, RAM AIR, CAB FAN1, CAB FAN2, PRESS MAN MODE (1bit)
	//	qpac_air_valves = ((XPLMGetDatai(jar_a320_neo_cond_ram_air) & 0x01) << 5) |
	//		(!(XPLMGetDatai(jar_a320_neo_press_mode)) & 0x01);
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_AIR_VALVES);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)qpac_air_valves);
	//	i++;
	//
	//	bleed_valves =
	//		(XPLMGetDatai(jar_a320_neo_bleed_cross_valve) & 0x03) |
	//		(XPLMGetDatai(jar_a320_neo_bleed_apu_bleed_valve) & 0x03) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_bleed_eng1_bleed_valve) & 0x03) << 4 |
	//		(XPLMGetDatai(jar_a320_neo_bleed_eng2_bleed_valve) & 0x03) << 6 |
	//		(XPLMGetDatai(jar_a320_neo_bleed_eng1_bleed_hp_valve) & 0x03) << 8 |
	//		(XPLMGetDatai(jar_a320_neo_bleed_eng2_bleed_hp_valve) & 0x03) << 10 |
	//		(XPLMGetDatai(jar_a320_neo_cond_pack1) & 0x03) << 12 |
	//		(XPLMGetDatai(jar_a320_neo_cond_pack2) & 0x03) << 14;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BLEED_VALVES);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)bleed_valves);
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BLEED_LEFT_PRESS);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_bleed_eng1_bleed_psi));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BLEED_RIGHT_PRESS);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_bleed_eng2_bleed_psi));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BLEED_LEFT_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_bleed_eng1_bleed_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_BLEED_RIGHT_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_bleed_eng2_bleed_temp));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK1_COMP_OUTLET_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack1_comp_deg));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK2_COMP_OUTLET_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack2_comp_deg));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK1_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack1_out_deg));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK2_TEMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack2_out_deg));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK1_BYPASS_RATIO);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack1_ndl));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK2_BYPASS_RATIO);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack2_ndl));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK1_FLOW);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack1_flow));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(XHSI_COND_PACK2_FLOW);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_cond_pack2_flow));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_NACELLE_TEMP_ + 0);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_eng_1_nac_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_NACELLE_TEMP_ + 1);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_eng_2_nac_temp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_SD_PAGE);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)XPLMGetDatai(jar_a320_disp_sys_mode));
	//	i++;

	//	// Anti-ice
	//	anti_ice =
	//		(XPLMGetDatai(jar_a320_neo_icerain_wing) & 0x03) |
	//		(XPLMGetDatai(jar_a320_neo_icerain_wing_flt) & 0x03) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_icerain_eng1) & 0x03) << 4 |
	//		(XPLMGetDatai(jar_a320_neo_icerain_eng2) & 0x03) << 8;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_ANTI_ICE_STATUS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)anti_ice);
	//	i++;

	//	// FUEL
	//	// Fuel pumps
	//	// Each pump status is on 2 bits
	//	qpac_fuel_pumps =
	//		(XPLMGetDatai(jar_a320_neo_fuel_t1_pump1) & 0x03) |
	//		(XPLMGetDatai(jar_a320_neo_fuel_t1_pump2) & 0x03) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_fuel_t2_pump1) & 0x03) << 4 |
	//		(XPLMGetDatai(jar_a320_neo_fuel_t2_pump2) & 0x03) << 6 |
	//		(XPLMGetDatai(jar_a320_neo_fuel_t3_pump1) & 0x03) << 8 |
	//		(XPLMGetDatai(jar_a320_neo_fuel_t3_pump2) & 0x03) << 10;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FUEL_PUMPS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)qpac_fuel_pumps);
	//	i++;

	//	/* Fuel valves
	//	* Each engine fuel valve status is on 2 bits
	//	* 0-1 : engine 0
	//	* 1-2 : engine 1
	//	* 3-4 : engine 2
	//	* 5-6 : engine 3
	//	* 7-8-9: X-Feed valve
	//	* 10-11 : Left transfer valves
	//	* 12-13 : Right transfer valves
	//	*/
	//	qpac_fuel_valves = (XPLMGetDatai(jar_a320_neo_eng_2_fuel_valve) & 0x03) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_eng_1_fuel_valve) & 0x03) |
	//		(XPLMGetDatai(jar_a320_neo_fuel_xfeed) & 0x07) << 8 |
	//		(XPLMGetDatai(jar_a320_neo_fuel_inn_out_left) & 0x03) << 11 |
	//		(XPLMGetDatai(jar_a320_neo_fuel_inn_out_right) & 0x03) << 13;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_FUEL_VALVES);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)qpac_fuel_valves);
	//	i++;

	//	// Spoilers
	//	spoilers = ((XPLMGetDataf(left_wing_spoiler_1_def[1])>12.5) & 0x01) |
	//		((XPLMGetDataf(left_wing_spoiler_1_def[1])>1.0) & 0x01) << 2 |
	//		((XPLMGetDataf(left_wing_spoiler_1_def[1])>1.0) & 0x01) << 4 |
	//		((XPLMGetDataf(left_wing_spoiler_2_def[1])>1.0) & 0x01) << 6 |
	//		((XPLMGetDataf(left_wing_spoiler_2_def[1])>0.5) & 0x01) << 8;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_SPOILERS_LEFT);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)spoilers);
	//	i++;
	//	spoilers = ((XPLMGetDataf(right_wing_spoiler_1_def[1])>12.5) & 0x01) |
	//		((XPLMGetDataf(right_wing_spoiler_1_def[1])>1.0) & 0x01) << 2 |
	//		((XPLMGetDataf(right_wing_spoiler_1_def[1])>1.0) & 0x01) << 4 |
	//		((XPLMGetDataf(right_wing_spoiler_2_def[1])>1.0) & 0x01) << 6 |
	//		((XPLMGetDataf(right_wing_spoiler_2_def[1])>0.5) & 0x01) << 8;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_SPOILERS_RIGHT);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)spoilers);
	//	i++;

	//	// ATA24 Electrics

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_EXT_HZ);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_ext_hz));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_EXT_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_ext_volt));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN1_HZ);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen1_hz));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN1_PER);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen1_per));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN1_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen1_volt));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN2_HZ);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen2_hz));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN2_PER);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen2_per));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN2_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen2_volt));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APU_HZ);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_apu_hz));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APU_PER);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_apu_per));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_APU_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_apu_volt));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN_EM_HZ);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen_emer_hz));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN_EM_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_gen_emer_volt));
	//	i++;

	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_TR1_AMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_tr1_amp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_TR1_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_tr1_volt));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_TR2_AMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_tr2_amp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_TR2_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_tr2_volt));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_TR_EM_AMP);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_tr_em_amp));
	//	i++;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_TR_EM_VOLT);
	//	sim_packet.sim_data_points[i].value = custom_htonf(XPLMGetDataf(jar_a320_neo_elec_tr_em_volt));
	//	i++;

	//	elec_status =
	//		(XPLMGetDatai(jar_a320_neo_elec_dc1) & 0x03) |
	//		(XPLMGetDatai(jar_a320_neo_elec_dc2) & 0x03) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_elec_dcbus) & 0x01) << 4 |
	//		(XPLMGetDatai(jar_a320_neo_elec_dc_ess) & 0x01) << 5 |
	//		(XPLMGetDatai(jar_a320_neo_elec_dc_ess_shed) & 0x01) << 6 |
	//		(XPLMGetDatai(jar_a320_neo_elec_dc_some_on) & 0x01) << 7;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_DC_STATUS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)elec_status);
	//	i++;
	//	elec_status =
	//		(XPLMGetDatai(jar_a320_neo_elec_ac1_source) & 0x07) |
	//		(XPLMGetDatai(jar_a320_neo_elec_ac2_source) & 0x07) << 3 |
	//		(XPLMGetDatai(jar_a320_neo_elec_ac_ess) & 0x03) << 6 |
	//		(XPLMGetDatai(jar_a320_neo_elec_ac_ess_alt) & 0x01) << 8 |
	//		(XPLMGetDatai(jar_a320_neo_elec_ac_ess_shed) & 0x01) << 9 |
	//		(XPLMGetDatai(jar_a320_neo_elec_bus_tie) & 0x01) << 10;
	//	// (XPLMGetDatai(jar_a320_neo_elec_commrc) & 0x01) << 11 |
	//	// (XPLMGetDatai(jar_a320_neo_elec_galley) & 0x01) << 12 ;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_AC_STATUS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)elec_status);
	//	i++;
	//	elec_status =
	//		(XPLMGetDatai(jar_a320_neo_elec_lft_gen_on) & 0x01) |
	//		(XPLMGetDatai(jar_a320_neo_elec_rgh_gen_on) & 0x01) << 1 |
	//		(XPLMGetDatai(jar_a320_neo_elec_apu_gen_on) & 0x01) << 2 |
	//		(XPLMGetDatai(jar_a320_neo_elec_gpu_on) & 0x01) << 3 |
	//		(XPLMGetDatai(jar_a320_neo_elec_gpu_av) & 0x01) << 4 |
	//		(XPLMGetDatai(jar_a320_neo_elec_emer) & 0x01) << 5 |
	//		(XPLMGetDatai(jar_a320_neo_elec_gen1_line_on) & 0x01) << 6 |
	//		(XPLMGetDatai(jar_a320_neo_elec_man_rat_on) & 0x01) << 7 |
	//		(XPLMGetDatai(jar_a320_neo_elec_rat_av) & 0x01) << 8 |
	//		(XPLMGetDatai(jar_a320_neo_elec_rat_on) & 0x01) << 9;
	//	sim_packet.sim_data_points[i].id = custom_htoni(JAR_A320NEO_GEN_STATUS);
	//	sim_packet.sim_data_points[i].value = custom_htonf((float)elec_status);
	//	i++;


	//}

	//// now we know the number of datapoints
	//sim_packet.nb_of_sim_data_points = custom_htoni(i);
	//udpSocket.writeDatagram((char*)&sim_packet, 8 * i + 8, QHostAddress(DEFAULT_DEST_IP), DEFAULT_DEST_PORT);
}

void QARParser::sendEnginesPacket(const QAROriginData &data)
{
	SimDataPacket eng_packet;
	int engiIndex = 0;
	strcpy(eng_packet.packet_id, "ENGI");
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_AIRCRAFT_OVERFLOW_ACF_NUM_TANKS);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(5);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_AIRCRAFT_ENGINE_ACF_NUM_ENGINES);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(2);
	engiIndex++;


	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_N1_ + 0);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.N11);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_N1_ + 1);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.N12);
	engiIndex++;

	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_COCKPIT2_ENGINE_ACTUATORS_THROTTLE_RATIO_ + 0);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.THROTT_ANG1 / 50.0);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_COCKPIT2_ENGINE_ACTUATORS_THROTTLE_RATIO_ + 1);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.THROTT_ANG2 / 50.0);
	engiIndex++;

	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_EGT_C_ + 0);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.EGT1);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_EGT_C_ + 1);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.EGT2);
	engiIndex++;



	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_N2_ + 0);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.N2_1);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_N2_ + 1);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.N2_2);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_FF_ + 0);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.FFKG1 / 3600.0);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_FF_ + 1);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.FFKG2 / 3600.0);
	engiIndex++;

	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_OIL_PRESS_PSI_ + 0);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.OIL_PRS_1);
	engiIndex++;
	eng_packet.sim_data_points[engiIndex].id = custom_htoni(SIM_FLIGHTMODEL_ENGINE_ENGN_OIL_PRESS_PSI_ + 1);
	eng_packet.sim_data_points[engiIndex].value = custom_htonf(data.OIL_PRS_1);
	engiIndex++;





	eng_packet.nb_of_sim_data_points = custom_htoni(engiIndex);
	//qDebug() << "engine packet" <<
	udpSocket.writeDatagram((char*)&eng_packet, engiIndex * 8 + 8, QHostAddress("127.0.0.1"), 49020);
}

void QARParser::sendStaticPacket(const QAROriginData &data)
{
	int i = 0;
	SimDataPacket sim_packet;
	sim_packet.sim_data_points[i].id = custom_htoni(SIM_AIRCRAFT_VIEW_ACF_TAILNUM_0_3);
	strncpy((char *)&sim_packet.sim_data_points[i].value, data.BNO.toStdString().c_str(), 4);
	i++;
	sim_packet.sim_data_points[i].id = custom_htoni(SIM_AIRCRAFT_VIEW_ACF_TAILNUM_4_7);
	strncpy((char *)&sim_packet.sim_data_points[i].value, data.BNO.toStdString().c_str() + 4, 4);
	i++;

	sim_packet.nb_of_sim_data_points = custom_htoni(i);
	udpSocket.writeDatagram((char*)&sim_packet, 8 * i + 8, QHostAddress("127.0.0.1"), 49020);
}


void QARParser::onStartListenning(bool b)
{
	if (b)
	{
		receiver.startListening();
		ui.toolButton_listen->setText(QString::fromLocal8Bit("关闭监听端口"));
	}
	else
	{
		receiver.stopListenning();
		ui.toolButton_listen->setText(QString::fromLocal8Bit("打开监听端口"));
	}
}

void QARParser::onOpenWarning(bool b)
{
	isWarningOpen = b;
	if (b)
	{
		ui.toolButton_open_warning->setText(QString::fromLocal8Bit("关闭告警系统"));
	}
	else
	{
		ui.toolButton_open_warning->setText(QString::fromLocal8Bit("打开告警系统"));
	}
}

void QARParser::onGetQARData(QAROriginData data)
{
	//收到的数据不是实时数据，直接返回
	qDebug() <<  data.time;
	if (data.DTYPE != "R")
		return;

	data.aircraft.tailNumber = data.BNO;
	data.aircraft.flightNumber = data.BNO;
	if (isWarningOpen)
	{
		if (abs(data.ROLL_ATT) > 5.0 && abs(data.ROLL_ATT) < 10.0)
		{
			data.warning.warningKind = 1;
			data.warning.warningLevel = 1;
		}
		else if (abs(data.ROLL_ATT) >= 10.0)
		{
			data.warning.warningKind = 1;
			data.warning.warningLevel = 2;
		}
		else
		{
			data.warning.warningKind = 0;
			data.warning.warningLevel = 0;
		}
	}
	else
	{
		data.warning.warningKind = 0;
		data.warning.warningLevel = 0;
	}
	qDebug() << "send data to all";
	publisher.WriteMsg(Serialize<QAROriginData>(data).data(), Serialize<QAROriginData>(data).size());
	//发送xhsi仪表数据
	if (simulatingAircraft.tailNumber == data.aircraft.tailNumber)
	{
		qDebug() << "send data to gauges";
		sendADCDPakcet(data);
		sendAvionicsPacket(data);
		sendCustomAvionicsPacket(data);
		sendEnginesPacket(data);
		sendStaticPacket(data);
	}
}

void QARParser::onListViewMenuRequest(const QPoint&pos)
{
	QModelIndex index = ui.listView->indexAt(pos);
	if (index.row() < 0)
		return;	listViewMenu->exec(QCursor::pos());
}

void QARParser::openQARFile(bool b)
{
	//获取选中行
	QModelIndexList modelIndexList = ui.listView->selectionModel()->selectedIndexes();
	if (modelIndexList.size() <= 0)	//没有选中任何数据项
	{
		return;
	}
	QString fileName = model->data(modelIndexList.at(0), Qt::DisplayRole).toString();	//获取选中文件名
	if (readerMap.contains(fileName))
	{
		return;
	}
	readerMap[fileName] = new FileReader();
	connect(readerMap[fileName], SIGNAL(doGetQARData(QAROriginData)), this, SLOT(onGetQARData(QAROriginData)));
	connect(readerMap[fileName], SIGNAL(fileDone(QString)), this, SLOT(onFileDone(QString)));
	readerMap[fileName]->OpenFile(fileName);
	readerMap[fileName]->SetSpeed(ui.horizontalSlider->value());
	
}

void QARParser::stopFileReader(bool b)
{
	QModelIndexList modelIndexList = ui.listView->selectionModel()->selectedIndexes();
	if (modelIndexList.size() <= 0)	//没有选中任何数据项
	{
		return;
	}
	QString fileName = model->data(modelIndexList.at(0), Qt::DisplayRole).toString();	//获取选中文件名
	if (!readerMap.contains(fileName))
	{
		return;
	}
	readerMap[fileName]->StopReader();
	delete readerMap[fileName];
	readerMap[fileName] = NULL;
	readerMap.remove(fileName);

}

void QARParser::onSetReaderSpeed(int value)
{
	qDebug() << QThread::currentThreadId();
	for (auto iter = readerMap.begin(); iter != readerMap.end(); ++iter)
	{
		iter.value()->SetSpeed(value);
	}
	ui.label_simulate_speed->setText(QString::number(value));
}

void QARParser::onGetAircraftInfo(QARAircraft aircraft)
{
	simulatingAircraft = aircraft;
}

void QARParser::keepXHSIGaugeAlive()
{
	SimDataPacket adcd_packet;
	strcpy(adcd_packet.packet_id, "ADCD");
	int adcdIndex = 0;
	adcd_packet.sim_data_points[adcdIndex].id = custom_htoni(PLUGIN_VERSION_ID);
	adcd_packet.sim_data_points[adcdIndex].value = custom_htonf(PLUGIN_VERSION_NUMBER);
	adcdIndex++;
	adcd_packet.nb_of_sim_data_points = custom_htoni(adcdIndex);
	udpSocket.writeDatagram((char*)&adcd_packet, adcdIndex * 8 + 8, QHostAddress(DEFAULT_DEST_IP), DEFAULT_DEST_PORT);

	SimDataPacket static_packet;
	strcpy(static_packet.packet_id, "STAT");
	int statIndex = 0;
	static_packet.sim_data_points[statIndex].id = custom_htoni(XHSI_STYLE);
	static_packet.sim_data_points[statIndex].value = custom_htonf(1); //设定仪表类型为显示320
	statIndex++;
	static_packet.sim_data_points[statIndex].id = custom_htoni(SIM_AIRCRAFT_VIEW_ACF_VNE);
	static_packet.sim_data_points[statIndex].value = custom_htonf(999); //设定仪表类型为显示320
	statIndex++;
	static_packet.nb_of_sim_data_points = custom_ntohi(statIndex);
	udpSocket.writeDatagram((char*)&static_packet, statIndex * 8 + 8, QHostAddress(DEFAULT_DEST_IP), DEFAULT_DEST_PORT);
}

void QARParser::onFileDone(QString fileName)
{
	qDebug() << "file send done";
	readerMap[fileName]->StopReader();
	delete readerMap[fileName];
	readerMap[fileName] = NULL;
	readerMap.remove(fileName);
}
