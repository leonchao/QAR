/*
 *数据结构定义头文件
 */
#ifndef STRUCT_H
#define STRUCT_H

#include "comdef.h"
#include "string"
using namespace std;


//DVIS
struct dvis_struct
{
public:
	dvis_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~dvis_struct()
	{

	}
    xdob lat_lon_ele[3];	// double for precision, latitude, longitude, elevation above sea level in meters
    xdob psi_the_phi[3];	// true heading, pitch up, roll right in degrees. double agagain to avoid byte-spacing confusions is all
};
Q_DECLARE_METATYPE(dvis_struct)

struct position_struct
{
public:
	position_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~position_struct()
	{

	}
    double longitude,latitude;				// double is needed for smooth data here. this is good for simple 2-d maps
#ifdef XPLANE_11
	double elevation_MSL;
#else
	float elevation_MSL;
#endif
    float elevation_AGL;		// we have AGL so you can correct the heigh above ground for your visuals to match X-Plane, if desired
    float pitch,heading,roll;				// this is for making your own visuals
    float Vx,Vy,Vz;						// Vxyz are the speeds in the east, up, and south directions, in meters per second. you can use these to predict longitude, latitude, and elevation smoothly.
    float Pdeg,Qdeg,Rdeg;				// P Q R are the roll, pitch, and yaw rates, in aircraft axis, in degrees per second. you can use these to predict pitch, heading, and roll smoothly.
};
Q_DECLARE_METATYPE(position_struct)

//RPOS
struct rpos_struct_in
{
public:
	rpos_struct_in()
	{
		memset(this, 0, sizeof(*this));
	}
	~rpos_struct_in()
	{
	}
#ifdef XPLANE_11
	char rpos_freq[2];
#else
    int rpos_freq;
#endif
};
Q_DECLARE_METATYPE(rpos_struct_in)

//BECN
#pragma pack(1)
struct becn_struct
{
public:
	becn_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~becn_struct(){}
    unsigned char beacon_major_version;		// 1 at the time of X-Plane 10.40
    unsigned char beacon_minor_version;		// 1 at the time of X-Plane 10.40
    xint application_host_id;			// 1 for X-Plane, 2 for PlaneMaker
    xint version_number;			// 104103 for X-Plane 10.41r3
    unsigned int role;						// 1 for master, 2 for extern visual, 3 for IOS
    unsigned short port;					// port number X-Plane is listening on, 49000 by default
    xchr	computer_name[500];		// the hostname of the computer, e.g. “Joe’s Macbook”
};
Q_DECLARE_METATYPE(becn_struct)
#pragma pack()


#ifdef XPLANE_11
#pragma pack(1)
#else
#pragma pack(8)
#endif

//VEH1
struct veh1_struct
{
public:
	veh1_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~veh1_struct()
	{

	}
#ifdef XPLANE_11
	int p;
	xdob lat,lon,ele;
	xflt psi,the,phi;
#else
    int p;
    xdob lat_lon_ele[3];
    xflt psi_the_phi[3];
    xflt gear_flap_vect[3];
#endif
};
Q_DECLARE_METATYPE(veh1_struct)
#pragma pack()


#pragma pack(8)

//VEHA
struct vehA_struct
{
public:
	vehA_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~vehA_struct()
	{

	}
    int num_p;
    xdob lat_lon_ele	[20][3];
    xflt psi_the_phi		[20][3];
    xflt gear_flap_vect	[20][3];
    xdob lat_view,lon_view,ele_view;
    xflt psi_view,the_view,phi_view;
};
Q_DECLARE_METATYPE(vehA_struct)
#pragma pack()

//RREF
struct dref_struct_in
{
public:
	dref_struct_in()
	{
		memset(this, 0, sizeof(*this));
	}
	~dref_struct_in()
	{

	}
    xint dref_freq		;
    xint dref_en		;
    xchr dref_string[400]	;
};
Q_DECLARE_METATYPE(dref_struct_in)

//RREF output
struct dref_struct_out
{
public:
	dref_struct_out()
	{
		memset(this, 0, sizeof(*this));
	}
	~dref_struct_out()
	{

	}
    xint dref_en	;
    xflt dref_flt	;
};
Q_DECLARE_METATYPE(dref_struct_out)

//DREF
struct dref_struct
{
public:
	dref_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~dref_struct()
	{

	}
    xflt var;
    xchr dref_path[500];
};
Q_DECLARE_METATYPE(dref_struct)


//DATA
struct data_struct
{
public:
	data_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~data_struct()
	{

	}
    int index;		 // data index, the index into the list of variables you can output from the Data Output screen in X-Plane.
    float data[8]; 	// the up to 8 numbers you see in the data output screen associated with that selection.. many outputs do not use all 8, though.
};
Q_DECLARE_METATYPE(data_struct)


//PAPT
struct papt_struct							// place at apt... this is used here and there
{
public:
	papt_struct()
	{
		memset(this, 0, sizeof(*this));
	}
	~papt_struct()
	{

	}
	xchr apt_ID[8];
	xint type_start;	//10 选择停机位 //11 放到跑道上 //12 进近 //13进近
	xint lcl_rwy_ram;	//多条跑道之间变换
	xint rwy_dir;
};
Q_DECLARE_METATYPE(papt_struct)
//CMND


//udp 命令
enum COMMANDS
{
    INVALID_COMMAND = 0,
    DVIS,
    RPOS,
    BECN,
    VEH1,
    VEHA,
    RREF,
    DREF,
    DATA,
    CMND,
	PAPT,
};

#endif
