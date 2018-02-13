#define MANUFACTURER_ID 7337
#define DEVICE_ID 1
#define REVISION 0

#define COMOBJ_cmd1_out 0
#define COMOBJ_cmd1_trig 1
#define COMOBJ_cmd2_out 2
#define COMOBJ_cmd2_trig 3
#define COMOBJ_cmd3_out 4
#define COMOBJ_cmd3_trig 5
#define COMOBJ_cmd4_out 6
#define COMOBJ_cmd4_trig 7
#define COMOBJ_cmd5_out 8
#define COMOBJ_cmd5_trig 9
#define COMOBJ_out1 10
#define COMOBJ_out2 11
#define COMOBJ_out3 12
#define COMOBJ_code_input 13
#define COMOBJ_key_output 14
#define COMOBJ_code_output 15
#define COMOBJ_door_input 16
#define PARAM_cmd1_out 0
#define PARAM_cmd1_out_mode 1
#define PARAM_cmd1_out_pulse 2
#define PARAM_cmd2_out 3
#define PARAM_cmd2_out_mode 4
#define PARAM_cmd2_out_pulse 5
#define PARAM_cmd3_out 6
#define PARAM_cmd3_out_mode 7
#define PARAM_cmd3_out_pulse 8
#define PARAM_cmd4_out 9
#define PARAM_cmd5_out 9
#define PARAM_cmd4_out_mode 10
#define PARAM_cmd5_out_mode 10
#define PARAM_cmd4_out_pulse 11
#define PARAM_cmd5_out_pulse 11
#define PARAM_door_onclose 12
#define PARAM_door_onclose_delay 13
        
KnxComObject KnxDevice::_comObjectsList[] = {
    /* Index 0 - cmd1_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 1 - cmd1_trig */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 2 - cmd2_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 3 - cmd2_trig */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 4 - cmd3_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 5 - cmd3_trig */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 6 - cmd4_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 7 - cmd4_trig */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 8 - cmd5_out */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 9 - cmd5_trig */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 10 - out1 */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 11 - out2 */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 12 - out3 */ KnxComObject(KNX_DPT_1_001, 0x3e),
    /* Index 13 - code_input */ KnxComObject(KNX_DPT_16_001, 0x28),
    /* Index 14 - key_output */ KnxComObject(KNX_DPT_4_001, 0x24),
    /* Index 15 - code_output */ KnxComObject(KNX_DPT_16_001, 0x24),
    /* Index 16 - door_input */ KnxComObject(KNX_DPT_1_009, 0x28)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - cmd1_out */ PARAM_UINT8,
    /* Index 1 - cmd1_out_mode */ PARAM_UINT8,
    /* Index 2 - cmd1_out_pulse */ PARAM_UINT8,
    /* Index 3 - cmd2_out */ PARAM_UINT8,
    /* Index 4 - cmd2_out_mode */ PARAM_UINT8,
    /* Index 5 - cmd2_out_pulse */ PARAM_UINT8,
    /* Index 6 - cmd3_out */ PARAM_UINT8,
    /* Index 7 - cmd3_out_mode */ PARAM_UINT8,
    /* Index 8 - cmd3_out_pulse */ PARAM_UINT8,
    /* Index 9 - cmd4_out */ PARAM_UINT8,
    /* Index 9 - cmd5_out */ PARAM_UINT8,
    /* Index 10 - cmd4_out_mode */ PARAM_UINT8,
    /* Index 10 - cmd5_out_mode */ PARAM_UINT8,
    /* Index 11 - cmd4_out_pulse */ PARAM_UINT8,
    /* Index 11 - cmd5_out_pulse */ PARAM_UINT8,
    /* Index 12 - door_onclose */ PARAM_UINT8,
    /* Index 13 - door_onclose_delay */ PARAM_UINT8
};
const byte KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code