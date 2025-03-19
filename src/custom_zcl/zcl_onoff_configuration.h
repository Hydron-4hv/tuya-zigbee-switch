#ifndef ZCL_ONOFF_CONFIGURATION_H
#define ZCL_ONOFF_CONFIGURATION_H



/*********************************************************************
 * CONSTANTS
 */

/**
 *  @brief	relative humidity measurement cluster Attribute IDs
 */

#define ZCL_ATTRID_ONOFF_CONFIGURATION_SWITCH_TYPE              0x0000
#define ZCL_ATTRID_ONOFF_CONFIGURATION_SWITCH_ACTIONS           0x0010
#define ZCL_ATTRID_ONOFF_CONFIGURATION_SWITCH_MODE              0xff00
#define ZCL_ATTRID_ONOFF_CONFIGURATION_SWITCH_RELAY_MODE        0xff01
#define ZCL_ATTRID_ONOFF_CONFIGURATION_SWITCH_RELAY_INDEX       0xff02
#define ZCL_ATTRID_ONOFF_CONFIGURATION_SWITCH_LONG_PRESS_DUR    0xff03


#define ZCL_ONOFF_CONFIGURATION_SWITCH_TYPE_TOGGLE              0x00
#define ZCL_ONOFF_CONFIGURATION_SWITCH_TYPE_MOMENTARY           0x01
#define ZCL_ONOFF_CONFIGURATION_SWITCH_TYPE_MULTIFUNCTION       0x02

#define ZCL_ONOFF_CONFIGURATION_SWITCH_ACTION_ONOFF             0x00
#define ZCL_ONOFF_CONFIGURATION_SWITCH_ACTION_OFFON             0x01
#define ZCL_ONOFF_CONFIGURATION_SWITCH_ACTION_TOGGLE            0x02

#define ZCL_ONOFF_CONFIGURATION_RELAY_MODE_DETACHED             0x00
#define ZCL_ONOFF_CONFIGURATION_RELAY_MODE_RISE                 0x01
#define ZCL_ONOFF_CONFIGURATION_RELAY_MODE_LONG                 0x02


status_t zcl_onoff_configuration_register(u8 endpoint, u16 manuCode, u8 attrNum, const zclAttrInfo_t attrTbl[], cluster_forAppCb_t cb);

#endif  /* ZCL_RELATIVE_HUMIDITY_H */
