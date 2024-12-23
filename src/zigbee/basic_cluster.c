#include "tl_common.h"
#include "zb_common.h"
#include "endpoint.h"
#include "basic_cluster.h"
#include "cluster_common.h"


const u8 zclVersion     = 0x03;
const u8 appVersion     = 0x03;
const u8 stackVersion   = 0x02;
const u8 hwVersion      = 0x00;
DEF_STR("Tuya-CUSTOM", manuName);
DEF_STR("TS0042-CUSTOM", modelId);
const u8 powerSource    = POWER_SOURCE_MAINS_1_PHASE;
DEF_STR_NON_CONST("0000-0000", swBuildId);
DEF_STR_NON_CONST("00000000", dateCode);


void populate_sw_build();
void populate_date_code();


status_t basic_cluster_callback_trampoline(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{	
	return ZCL_STA_SUCCESS;
}

void basic_cluster_add_to_endpoint(zigbee_basic_cluster *cluster, zigbee_endpoint *endpoint) {
    populate_sw_build();
    populate_date_code();

    // Fill Attrs
    SETUP_ATTR(0, ZCL_ATTRID_BASIC_ZCL_VER,             ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, zclVersion);
    SETUP_ATTR(1, ZCL_ATTRID_BASIC_APP_VER,             ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, appVersion);
    SETUP_ATTR(2, ZCL_ATTRID_BASIC_STACK_VER,           ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, stackVersion);
    SETUP_ATTR(3, ZCL_ATTRID_BASIC_HW_VER,              ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, hwVersion);
    SETUP_ATTR(4, ZCL_ATTRID_BASIC_MFR_NAME,            ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ, manuName);
    SETUP_ATTR(5, ZCL_ATTRID_BASIC_MODEL_ID,            ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ, modelId);
    SETUP_ATTR(6, ZCL_ATTRID_BASIC_POWER_SOURCE,        ZCL_DATA_TYPE_ENUM8,    ACCESS_CONTROL_READ, powerSource);
    SETUP_ATTR(7, ZCL_ATTRID_BASIC_DEV_ENABLED,         ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, cluster->deviceEnable);
    SETUP_ATTR(8, ZCL_ATTRID_BASIC_SW_BUILD_ID,         ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ, swBuildId);
    SETUP_ATTR(9, ZCL_ATTRID_BASIC_DATE_CODE,           ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ, dateCode);
    SETUP_ATTR(10, ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ, zcl_attr_global_clusterRevision);

    zigbee_endpoint_add_cluster(endpoint, 1, ZCL_CLUSTER_GEN_BASIC);
    zcl_specClusterInfo_t *info = zigbee_endpoint_reserve_info(endpoint);
    info->clusterId = ZCL_CLUSTER_GEN_BASIC;
    info->manuCode = MANUFACTURER_CODE_NONE;
    info->attrNum = 11;
    info->attrTbl = cluster->attr_infos;
    info->clusterRegisterFunc = zcl_basic_register;
    info->clusterAppCb = basic_cluster_callback_trampoline;
}


char int_to_hex(u8 num) {
	const char * hex_ascii = {"0123456789ABCDEF"};
	if (num > 15) return hex_ascii[0];
	return hex_ascii[num];
}

void populate_sw_build() {
	swBuildId.str[0] = int_to_hex(STACK_RELEASE>>4);
	swBuildId.str[1] = int_to_hex(STACK_RELEASE & 0xf);
	swBuildId.str[2] = int_to_hex(STACK_BUILD>>4);
	swBuildId.str[3] = int_to_hex(STACK_BUILD & 0xf);
	swBuildId.str[4] = int_to_hex(APP_RELEASE>>4);
	swBuildId.str[5] = int_to_hex(APP_RELEASE & 0xf);
	swBuildId.str[6] = int_to_hex(APP_BUILD>>4);
	swBuildId.str[7] = int_to_hex(APP_BUILD & 0xf);
}

void populate_date_code() {
	u8 month;
	if (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n') month = 1;
	else if (__DATE__[0] == 'F') month = 2;
	else if (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r') month = 3;
	else if (__DATE__[0] == 'A' && __DATE__[1] == 'p') month = 4;
	else if (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y') month = 5;
	else if (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n') month = 6;
	else if (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l') month = 7;
	else if (__DATE__[0] == 'A' && __DATE__[1] == 'u') month = 8;
	else if (__DATE__[0] == 'S') month = 9;
	else if (__DATE__[0] == 'O') month = 10;
	else if (__DATE__[0] == 'N') month = 11;
	else if (__DATE__[0] == 'D') month = 12;

	dateCode.str[0] = __DATE__[7];
	dateCode.str[1] = __DATE__[8];
	dateCode.str[2] = __DATE__[9];
	dateCode.str[3] = __DATE__[10];
	dateCode.str[4] = '0' + month / 10;
	dateCode.str[5] = '0' + month % 10;
	dateCode.str[6] = __DATE__[4] >= '0' ? (__DATE__[4]) : '0';
	dateCode.str[7] = __DATE__[5];
}
