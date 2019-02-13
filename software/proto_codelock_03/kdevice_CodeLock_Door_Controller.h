#define MANUFACTURER_ID 7337
#define DEVICE_ID 20
#define REVISION 0

#define COMOBJ_cmd0_out 0
#define COMOBJ_cmd1_out 1
#define COMOBJ_cmd2_out 2
#define COMOBJ_cmd3_out 3
#define COMOBJ_cmd4_out 4
#define COMOBJ_cmd5_out 5
#define COMOBJ_cmd6_out 6
#define COMOBJ_cmd7_out 7
#define COMOBJ_cmd8_out 8
#define COMOBJ_cmd9_out 9
#define COMOBJ_cmd_wrong 10
#define COMOBJ_cmd_all 11
#define COMOBJ_key_output 12
#define COMOBJ_lock_open 13
#define COMOBJ_lock_unlock 14
#define COMOBJ_door_input 15
#define COMOBJ_error_code 16
#define PARAM_device_mode 0
#define PARAM_code 1
#define PARAM_default_cmd 2
#define PARAM_cmd0_out_mode 3
#define PARAM_cmd1_out_mode 4
#define PARAM_cmd2_out_mode 5
#define PARAM_cmd3_out_mode 6
#define PARAM_cmd4_out_mode 7
#define PARAM_cmd5_out_mode 8
#define PARAM_cmd6_out_mode 9
#define PARAM_cmd7_out_mode 10
#define PARAM_cmd8_out_mode 11
#define PARAM_cmd9_out_mode 12
#define PARAM_motorlock_onclose 13
#define PARAM_motorlock_open_cmd 14
#define PARAM_motorlock_lock_cmd 15
#define PARAM_motorlock_unlock_cmd 16
        
KnxComObject KnxDevice::_comObjectsList[] = {
    /* Index 0 - cmd0_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 1 - cmd1_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 2 - cmd2_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 3 - cmd3_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 4 - cmd4_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 5 - cmd5_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 6 - cmd6_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 7 - cmd7_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 8 - cmd8_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 9 - cmd9_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 10 - cmd_wrong */ KnxComObject(KNX_DPT_1_001, 0x24),
    /* Index 11 - cmd_all */ KnxComObject(KNX_DPT_5_010, 0x24),
    /* Index 12 - key_output */ KnxComObject(KNX_DPT_4_001, 0x24),
    /* Index 13 - lock_open */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 14 - lock_unlock */ KnxComObject(KNX_DPT_1_009, 0x28),
    /* Index 15 - door_input */ KnxComObject(KNX_DPT_1_009, 0x28),
    /* Index 16 - error_code */ KnxComObject(KNX_DPT_12_001, 0x34)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - device_mode */ PARAM_UINT8,
    /* Index 1 - code */ PARAM_UINT32,
    /* Index 2 - default_cmd */ PARAM_UINT8,
    /* Index 3 - cmd0_out_mode */ PARAM_UINT8,
    /* Index 4 - cmd1_out_mode */ PARAM_UINT8,
    /* Index 5 - cmd2_out_mode */ PARAM_UINT8,
    /* Index 6 - cmd3_out_mode */ PARAM_UINT8,
    /* Index 7 - cmd4_out_mode */ PARAM_UINT8,
    /* Index 8 - cmd5_out_mode */ PARAM_UINT8,
    /* Index 9 - cmd6_out_mode */ PARAM_UINT8,
    /* Index 10 - cmd7_out_mode */ PARAM_UINT8,
    /* Index 11 - cmd8_out_mode */ PARAM_UINT8,
    /* Index 12 - cmd9_out_mode */ PARAM_UINT8,
    /* Index 13 - motorlock_onclose */ PARAM_UINT8,
    /* Index 14 - motorlock_open_cmd */ PARAM_UINT8,
    /* Index 15 - motorlock_lock_cmd */ PARAM_UINT8,
    /* Index 16 - motorlock_unlock_cmd */ PARAM_UINT8
};
const byte KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code