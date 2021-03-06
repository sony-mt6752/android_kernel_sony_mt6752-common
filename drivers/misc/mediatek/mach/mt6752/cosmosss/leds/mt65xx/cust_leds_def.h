#ifndef _CUST_LEDS_DEF_H
#define _CUST_LEDS_DEF_H
//<<<2016/02/04-dangyiwang, porting lm3533 from cosmos/lavender L to M
//<2014/07/24-Yuting Shih. [Jessicatseng] Integrate backlight IC LM3533.
#if !defined( BACKLIGHT_IC_LM3533 )
  #define   BACKLIGHT_IC_LM3533
#endif
//>2014/07/24-Yuting Shih.
//>>>2016/02/04-dangyiwang, porting lm3533 from cosmos/lavender L to M
//#define CUST_LEDS_BACKLIGHT_PMIC_PARA /* parallel */
//#define CUST_LEDS_BACKLIGHT_PMIC_SERI /* series */
enum mt65xx_led_mode
{
	MT65XX_LED_MODE_NONE,
	MT65XX_LED_MODE_PWM,
	MT65XX_LED_MODE_GPIO,
	MT65XX_LED_MODE_PMIC,
	//MT65XX_LED_MODE_CUST,
	MT65XX_LED_MODE_CUST_LCM,	
	MT65XX_LED_MODE_CUST_BLS_PWM
//<<<2016/02/04-dangyiwang, porting lm3533 from cosmos/lavender L to M
//<2014/07/24-Yuting Shih. [Jessicatseng] Integrate backlight IC LM3533.
#if defined( BACKLIGHT_IC_LM3533 )
	,MT65XX_LED_MODE_LM3533
#endif
//>2014/07/24-Yuting Shih.
	//>>>2016/02/04-dangyiwang, porting lm3533 from cosmos/lavender L to M
};
	//<<<2016/02/08-dangyiwang, porting lm3533 from cosmos/lavender L to M
//<2014/07/24-Yuting Shih. [Jessicatseng] Integrate backlight IC LM3533.
#if defined( BACKLIGHT_IC_LM3533 )
enum mt65xx_led_lm3533
{
	MT65XX_LED_LM3533_H1 = 0,
	MT65XX_LED_LM3533_H2,
	MT65XX_LED_LM3533_L1,
	MT65XX_LED_LM3533_L2,
	MT65XX_LED_LM3533_L3,
	MT65XX_LED_LM3533_L4
};

    #define   MT65XX_LED_LM3533_LCD     MT65XX_LED_LM3533_H1
    #define   MT65XX_LED_LM3533_RED     MT65XX_LED_LM3533_L3
    #define   MT65XX_LED_LM3533_GREEN   MT65XX_LED_LM3533_L2
    #define   MT65XX_LED_LM3533_BLUE    MT65XX_LED_LM3533_L1

#endif
//>2014/07/24-Yuting Shih.
	//>>>2016/02/08-dangyiwang, porting lm3533 from cosmos/lavender L to M
enum mt65xx_led_pmic
{
	MT65XX_LED_PMIC_LCD_ISINK=0,
	MT65XX_LED_PMIC_NLED_ISINK0,
	MT65XX_LED_PMIC_NLED_ISINK1,
	MT65XX_LED_PMIC_NLED_ISINK2,
	MT65XX_LED_PMIC_NLED_ISINK3
};
struct PWM_config
{
	int clock_source;
	int div;
	int low_duration;
	int High_duration;
	BOOL pmic_pad;
};
typedef int (*cust_brightness_set)(int level, int div);
typedef int (*cust_set_brightness)(int level);

/*
 * name : must the same as lights HAL
 * mode : control mode
 * data :
 *    PWM:  pwm number
 *    GPIO: gpio id
 *    PMIC: enum mt65xx_led_pmic
 *    CUST: custom set brightness function pointer
*/
struct cust_mt65xx_led {
	char                 *name;
	enum mt65xx_led_mode  mode;
	long                   data;
 struct PWM_config config_data;
};

extern struct cust_mt65xx_led *get_cust_led_list(void);
#endif /* _CUST_LEDS_DEF_H */
