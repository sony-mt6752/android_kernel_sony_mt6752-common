#ifndef BATTERY_COMMON_H
#define BATTERY_COMMON_H

#include <linux/ioctl.h>
#include <mach/mt_typedefs.h>
#include "charging.h"

/*****************************************************************************
 *  BATTERY VOLTAGE
 ****************************************************************************/
#define PRE_CHARGE_VOLTAGE                  3200
#define CONSTANT_CURRENT_CHARGE_VOLTAGE     4100
#define CONSTANT_VOLTAGE_CHARGE_VOLTAGE     4200
#define CV_DROPDOWN_VOLTAGE                 4000
#define CHARGER_THRESH_HOLD                 4300
#define BATTERY_UVLO_VOLTAGE                2700
#ifndef SHUTDOWN_SYSTEM_VOLTAGE
#define SHUTDOWN_SYSTEM_VOLTAGE		3400
#endif

/*****************************************************************************
 *  BATTERY TIMER
 ****************************************************************************/
/* #define MAX_CHARGING_TIME             1*60*60         // 1hr */
/* #define MAX_CHARGING_TIME                   8*60*60   // 8hr */
/* #define MAX_CHARGING_TIME                   12*60*60  // 12hr */
/*[Lavender][bozhi_lin] check batery waringing message and set charging state to discharging when over charing time 20150430 begin*/
//<2014/12/10-tedwu, change charging time
#if 1

#else
#define MAX_CHARGING_TIME                   24*60*60	/* 24hr */
#endif
//>2014/12/10-tedwu
/*[Lavender][bozhi_lin] 20150430 end*/

#define MAX_POSTFULL_SAFETY_TIME		1*30*60	/* 30mins */
#define MAX_PreCC_CHARGING_TIME		1*30*60	/* 0.5hr */

/* #define MAX_CV_CHARGING_TIME                  1*30*60         // 0.5hr */
#define MAX_CV_CHARGING_TIME			3*60*60	/* 3hr */


#define MUTEX_TIMEOUT                       5000
#define BAT_TASK_PERIOD                     10	/* 10sec */
#define g_free_bat_temp					1000	/* 1 s */

/*****************************************************************************
 *  BATTERY Protection
 ****************************************************************************/
#define Battery_Percent_100    100
#define charger_OVER_VOL	    1
#define BATTERY_UNDER_VOL		2
#define BATTERY_OVER_TEMP		3
#define ADC_SAMPLE_TIMES        5

/*****************************************************************************
 *  Pulse Charging State
 ****************************************************************************/
#define  CHR_PRE                        0x1000
#define  CHR_CC                         0x1001
#define  CHR_TOP_OFF                    0x1002
#define  CHR_POST_FULL                  0x1003
#define  CHR_BATFULL                    0x1004
#define  CHR_ERROR                      0x1005
#define  CHR_HOLD						0x1006
/*[Lavender][bozhi_lin] set AC timer to 5 hours and USB to 100 hours 20150415 begin*/
#define  CHR_TIMEOUT					0x1007
/*[Lavender][bozhi_lin] 20150415 end*/

/*****************************************************************************
 *  CallState
 ****************************************************************************/
#define CALL_IDLE 0
#define CALL_ACTIVE 1

/*****************************************************************************
 *  Enum
 ****************************************************************************/
typedef unsigned int WORD;


typedef enum {
	PMU_STATUS_OK = 0,
	PMU_STATUS_FAIL = 1,
} PMU_STATUS;


typedef enum {
	USB_SUSPEND = 0,
	USB_UNCONFIGURED,
	USB_CONFIGURED
} usb_state_enum;

typedef enum {
	BATTERY_AVG_CURRENT = 0,
	BATTERY_AVG_VOLT = 1,
	BATTERY_AVG_TEMP = 2,
	BATTERY_AVG_MAX
} BATTERY_AVG_ENUM;

typedef enum {
	BATTERY_THREAD_TIME = 0,
	CAR_TIME,
	SUSPEND_TIME,
	DURATION_NUM
} BATTERY_TIME_ENUM;

/*****************************************************************************
*   JEITA battery temperature standard
    charging info ,like temperatue, charging current, re-charging voltage, CV threshold would be reconfigurated.
    Temperature hysteresis default 6C.
    Reference table:
    degree    AC Current    USB current    CV threshold    Recharge Vol    hysteresis condition
    > 60       no charging current,             X                    X                     <54(Down)
    45~60     600mA         450mA             4.1V               4V                   <39(Down) >60(Up)
    10~45     600mA         450mA             4.2V               4.1V                <10(Down) >45(Up)
    0~10       600mA         450mA             4.1V               4V                   <0(Down)  >16(Up)
    -10~0     200mA         200mA             4V                  3.9V                <-10(Down) >6(Up)
    <-10      no charging current,              X                    X                    >-10(Up)
****************************************************************************/
typedef enum {
//<2015/01/18-tedwu, For battery over temperature protection.
#if 1
        TEMP_BELOW_NEG_10 = 0,  //Ted: now is < 5
        TEMP_NEG_10_TO_POS_45,  //Ted: now is 5 to 45
        TEMP_POS_45_TO_POS_55,
        TEMP_POS_55_TO_POS_57,
        TEMP_POS_57_TO_POS_60,
        TEMP_ABOVE_POS_60
#else
	TEMP_BELOW_NEG_10 = 0,
	TEMP_NEG_10_TO_POS_0,
	TEMP_POS_0_TO_POS_10,
	TEMP_POS_10_TO_POS_45,
	TEMP_POS_45_TO_POS_60,
	TEMP_ABOVE_POS_60
#endif
//>2015/01/18-tedwu
} temp_state_enum;

//<2015/01/18-tedwu, For battery over temperature protection.
#if 1

/*[Lavender][bozhi_lin] for battery temperature safety set different current and voltage 20150415 begin*/
//<2015/03/26-tedwu, change battery notify temperature value.
#if defined(COSMOS)
#define TEMP_POS_TOLERENRCE	               2
#define TEMP_POS_60_THRESHOLD             60
#define TEMP_POS_60_THRES_MINUS_TOLERENRCE  (TEMP_POS_60_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_60_THRES_PLUS_TOLERENRCE   (TEMP_POS_60_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_45_THRESHOLD             45
#define TEMP_POS_45_THRES_MINUS_TOLERENRCE  (TEMP_POS_45_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_45_THRES_PLUS_TOLERENRCE   (TEMP_POS_45_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_10_THRESHOLD             10
#define TEMP_POS_10_THRES_MINUS_TOLERENRCE  (TEMP_POS_10_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_10_THRES_PLUS_TOLERENRCE   (TEMP_POS_10_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_0_THRESHOLD               0
#define TEMP_POS_0_THRES_MINUS_TOLERENRCE   (TEMP_POS_0_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_0_THRES_PLUS_TOLERENRCE    (TEMP_POS_0_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_CRITICAL_THRESHOLD       (70-1)
#define TEMP_POS_60_THRES_MINUS_X_DEGREE  55
#define TEMP_POS_60_THRES_NEAR_X_DEGREE   (67-1)
#elif defined(LAVENDER)
#define TEMP_POS_TOLERENRCE	               2
#define TEMP_POS_60_THRESHOLD             60
#define TEMP_POS_60_THRES_MINUS_TOLERENRCE  (TEMP_POS_60_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_60_THRES_PLUS_TOLERENRCE   (TEMP_POS_60_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_45_THRESHOLD             45
#define TEMP_POS_45_THRES_MINUS_TOLERENRCE  (TEMP_POS_45_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_45_THRES_PLUS_TOLERENRCE   (TEMP_POS_45_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_10_THRESHOLD             10
#define TEMP_POS_10_THRES_MINUS_TOLERENRCE  (TEMP_POS_10_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_10_THRES_PLUS_TOLERENRCE   (TEMP_POS_10_THRESHOLD+TEMP_POS_TOLERENRCE)

#define TEMP_POS_0_THRESHOLD               0
#define TEMP_POS_0_THRES_MINUS_TOLERENRCE   (TEMP_POS_0_THRESHOLD-TEMP_POS_TOLERENRCE)
#define TEMP_POS_0_THRES_PLUS_TOLERENRCE    (TEMP_POS_0_THRESHOLD+TEMP_POS_TOLERENRCE)

/*[Lavender][bozhi_lin] check batery waringing message and set charging state to discharging when over charing time 20150430 begin*/
#define TEMP_POS_CRITICAL_THRESHOLD       65
#define TEMP_POS_60_THRES_NEAR_X_DEGREE   62
/*[Lavender][bozhi_lin] 20150430 end*/
#else
#define TEMP_POS_60_THRESHOLD             60
#define TEMP_POS_60_THRES_MINUS_X_DEGREE  55
#define TEMP_POS_60_THRES_NEAR_X_DEGREE   57

#define TEMP_POS_45_THRESHOLD             45
#define TEMP_POS_45_THRES_MINUS_X_DEGREE  39
#define TEMP_POS_45_THRES_NEAR_X_DEGREE   42

#define TEMP_POS_10_THRESHOLD             10
#define TEMP_POS_10_THRES_PLUS_X_DEGREE   15

#define TEMP_POS_0_THRESHOLD              0
#define TEMP_POS_0_THRES_PLUS_X_DEGREE    6
#endif
//>2015/03/26-tedwu
/*[Lavender][bozhi_lin] 20150415 end*/

#else

#define TEMP_POS_60_THRESHOLD  50
#define TEMP_POS_60_THRES_MINUS_X_DEGREE 47

#define TEMP_POS_45_THRESHOLD  45
#define TEMP_POS_45_THRES_MINUS_X_DEGREE 39

#define TEMP_POS_10_THRESHOLD  10
#define TEMP_POS_10_THRES_PLUS_X_DEGREE 16

#define TEMP_POS_0_THRESHOLD  0
#define TEMP_POS_0_THRES_PLUS_X_DEGREE 6

#endif
//>2015/01/18-tedwu

#ifdef CONFIG_MTK_FAN5405_SUPPORT
//<2015/01/18-tedwu, For battery over temperature protection.
  #if 1
    #define TEMP_NEG_10_THRESHOLD             5 //(-10)
    #define TEMP_NEG_10_THRES_PLUS_X_DEGREE   8 //(-5)
  #else
    #define TEMP_NEG_10_THRESHOLD  0
    #define TEMP_NEG_10_THRES_PLUS_X_DEGREE  0
  #endif
//>2015/01/18-tedwu
#elif defined(CONFIG_MTK_BQ24158_SUPPORT)
#define TEMP_NEG_10_THRESHOLD  0
#define TEMP_NEG_10_THRES_PLUS_X_DEGREE  0
#else
#define TEMP_NEG_10_THRESHOLD  0
#define TEMP_NEG_10_THRES_PLUS_X_DEGREE  0
#endif

/*****************************************************************************
 *  Normal battery temperature state
 ****************************************************************************/
/*[Lavender][bozhi_lin] for battery temperature safety set different current and voltage 20150415 begin*/
//<2016/06/07-stevenchen, Fix OSS build error
#if defined(COSMOS) || defined(LAVENDER)
//>2016/06/07-stevenchen
typedef enum {
	TEMP_POS_COLD = 0,
	TEMP_POS_COOL,
	TEMP_POS_NORMAL,
	TEMP_POS_WARM,
	TEMP_POS_HOT
} batt_temp_state_enum;
#else
typedef enum {
	TEMP_POS_LOW = 0,
	TEMP_POS_NORMAL,
//<2016/06/07-stevenchen, Fix OSS build error
	TEMP_POS_DEC_CHARGE,
//>2016/06/07-stevenchen
	TEMP_POS_HIGH
} batt_temp_state_enum;
#endif
/*[Lavender][bozhi_lin] 20150415 end*/

/*****************************************************************************
 *  structure
 ****************************************************************************/
typedef struct {
	kal_bool bat_exist;
	kal_bool bat_full;
	INT32 bat_charging_state;
	UINT32 bat_vol;
	kal_bool bat_in_recharging_state;
	kal_uint32 Vsense;
	kal_bool charger_exist;
	UINT32 charger_vol;
	INT32 charger_protect_status;
	INT32 ICharging;
	INT32 IBattery;
	INT32 temperature;
	INT32 temperatureR;
	INT32 temperatureV;
//<2015/01/18-tedwu, For battery over temperature protection.
	INT32 old_temperature;
//>2015/01/18-tedwu
	UINT32 total_charging_time;
	UINT32 PRE_charging_time;
	UINT32 CC_charging_time;
	UINT32 TOPOFF_charging_time;
	UINT32 POSTFULL_charging_time;
	UINT32 charger_type;
	INT32 SOC;
	INT32 UI_SOC;
	INT32 UI_SOC2;
	UINT32 nPercent_ZCV;
	UINT32 nPrecent_UI_SOC_check_point;
	UINT32 ZCV;
/*[Lavender][bozhi_lin] set AC timer to 5 hours and USB to 100 hours 20150415 begin*/
	UINT32 charging_timer;
/*[Lavender][bozhi_lin] 20150415 end*/
/*[Lavender][bozhi_lin] enable charging maintenance 20150522 begin*/
#if defined(CHARGING_MAINTAIN)
	UINT32 MAINTAIN_charging_time;
#endif
    /*[Lavender][bozhi_lin] 20150522 end*/
        // <<< 2016/04/01-youchihwang. Battery. FP022589. Battery Swelling Mitigation for retail demo.
        INT32 enable_llk;
        INT32 llk_socmax;
        INT32 llk_socmin;
        // >>> 2016/04/01-youchihwang. Battery. FP022589. Battery Swelling Mitigation for retail demo.
} PMU_ChargerStruct;

struct battery_custom_data {
	/* mt_charging.h */
	/* stop charging while in talking mode */
	int stop_charging_in_takling;
	int talking_recharge_voltage;
	int talking_sync_time;

	/* Battery Temperature Protection */
	int mtk_temperature_recharge_support;
	int max_charge_temperature;
	int max_charge_temperature_minus_x_degree;
	int min_charge_temperature;
	int min_charge_temperature_plus_x_degree;
	int err_charge_temperature;

	/* Linear Charging Threshold */
	int v_pre2cc_thres;
	int v_cc2topoff_thres;
	int recharging_voltage;
	int charging_full_current;

	/* Charging Current Setting */
	int config_usb_if;
	int usb_charger_current_suspend;
	int usb_charger_current_unconfigured;
	int usb_charger_current_configured;
	int usb_charger_current;
	int ac_charger_input_current;
	int ac_charger_current;
	int non_std_ac_charger_current;
	int charging_host_charger_current;
	int apple_0_5a_charger_current;
	int apple_1_0a_charger_current;
	int apple_2_1a_charger_current;

	/* Precise Tunning
	   int battery_average_data_number;
	   int battery_average_size;
	 */

	/* charger error check */
	int bat_low_temp_protect_enable;
	int v_charger_enable;
	int v_charger_max;
	int v_charger_min;

	/* Tracking TIME */
	int onehundred_percent_tracking_time;
	int npercent_tracking_time;
	int sync_to_real_tracking_time;
	int v_0percent_tracking;

	/* Battery Notify
	   int battery_notify_case_0001_vcharger;
	   int battery_notify_case_0002_vbattemp;
	   int battery_notify_case_0003_icharging;
	   int battery_notify_case_0004_vbat;
	   int battery_notify_case_0005_total_chargingtime;
	 */

	/* High battery support */
	int high_battery_voltage_support;

	/* JEITA parameter */
	int mtk_jeita_standard_support;
	int cust_soc_jeita_sync_time;
	int jeita_recharge_voltage;
	int jeita_temp_above_pos_60_cv_voltage;
	int jeita_temp_pos_45_to_pos_60_cv_voltage;
	int jeita_temp_pos_10_to_pos_45_cv_voltage;
	int jeita_temp_pos_0_to_pos_10_cv_voltage;
	int jeita_temp_neg_10_to_pos_0_cv_voltage;
	int jeita_temp_below_neg_10_cv_voltage;

	/* For JEITA Linear Charging only */
	int jeita_neg_10_to_pos_0_full_current;
	int jeita_temp_pos_45_to_pos_60_recharge_voltage;
	int jeita_temp_pos_10_to_pos_45_recharge_voltage;
	int jeita_temp_pos_0_to_pos_10_recharge_voltage;
	int jeita_temp_neg_10_to_pos_0_recharge_voltage;
	int jeita_temp_pos_45_to_pos_60_cc2topoff_threshold;
	int jeita_temp_pos_10_to_pos_45_cc2topoff_threshold;
	int jeita_temp_pos_0_to_pos_10_cc2topoff_threshold;
	int jeita_temp_neg_10_to_pos_0_cc2topoff_threshold;

	/* cust_pe.h */
	int mtk_pump_express_plus_support;
	int ta_start_battery_soc;
	int ta_stop_battery_soc;
	int ta_ac_12v_input_current;
	int ta_ac_9v_input_current;
	int ta_ac_7v_input_current;
	int ta_ac_charging_current;
	int ta_12v_support;
	int ta_9v_support;
};

/*****************************************************************************
 *  Extern Variable
 ****************************************************************************/
extern PMU_ChargerStruct BMT_status;
extern struct battery_custom_data batt_cust_data;
extern CHARGING_CONTROL battery_charging_control;
extern kal_bool g_ftm_battery_flag;
extern int charging_level_data[1];
extern kal_bool g_call_state;
extern kal_bool g_charging_full_reset_bat_meter;
#if defined(CONFIG_MTK_PUMP_EXPRESS_SUPPORT) || defined(CONFIG_MTK_PUMP_EXPRESS_PLUS_SUPPORT)
extern kal_bool ta_check_chr_type;
extern kal_bool ta_cable_out_occur;
extern kal_bool is_ta_connect;
extern struct wake_lock TA_charger_suspend_lock;
#endif
extern U32 sleep_total_time;
//<2015/01/18-tedwu, For battery over temperature protection.
extern unsigned int g_BatTempLevel;
//>2015/01/18-tedwu

/*****************************************************************************
 *  Extern Function
 ****************************************************************************/
extern void charging_suspend_enable(void);
extern void charging_suspend_disable(void);
extern kal_bool bat_is_charger_exist(void);
extern kal_bool bat_is_charging_full(void);
extern kal_uint32 bat_get_ui_percentage(void);
extern kal_uint32 get_charging_setting_current(void);
extern kal_uint32 bat_is_recharging_phase(void);
extern void do_chrdet_int_task(void);
extern void set_usb_current_unlimited(bool enable);
extern bool get_usb_current_unlimited(void);
extern CHARGER_TYPE mt_get_charger_type(void);

extern kal_uint32 mt_battery_get_duration_time(BATTERY_TIME_ENUM duration_type);
extern void mt_battery_update_time(struct timespec *pre_time, BATTERY_TIME_ENUM duration_type);

extern kal_uint32 mt_battery_shutdown_check(void);

extern kal_uint8 bat_is_kpoc(void);

#ifdef CONFIG_MTK_SMART_BATTERY
extern void wake_up_bat(void);
extern void wake_up_bat2(void);
extern void wake_up_bat3(void);

extern unsigned long BAT_Get_Battery_Voltage(int polling_mode);
extern void mt_battery_charging_algorithm(void);
#if defined(CONFIG_MTK_JEITA_STANDARD_SUPPORT)
extern PMU_STATUS do_jeita_state_machine(void);
#endif

#else

#define wake_up_bat()			do {} while (0)
#define wake_up_bat2()			do {} while (0)
#define wake_up_bat3()			do {} while (0)


#define BAT_Get_Battery_Voltage(polling_mode)	({ 0; })

#endif

#ifdef CONFIG_MTK_POWER_EXT_DETECT
extern kal_bool bat_is_ext_power(void);
#endif

extern kal_bool is_usb_rdy(void);
extern bool mt_usb_is_device(void);
#if defined(CONFIG_USB_MTK_HDRC) || defined(CONFIG_USB_MU3D_DRV)
extern void mt_usb_connect(void);
extern void mt_usb_disconnect(void);
#else
#define mt_usb_connect() do { } while (0)
#define mt_usb_disconnect() do { } while (0)
#endif
void check_battery_exist(void);
extern void reset_parameter_dod_empty(void);
extern void reset_parameter_dod_charger_plug_event(void);


#endif				/* #ifndef BATTERY_COMMON_H */
