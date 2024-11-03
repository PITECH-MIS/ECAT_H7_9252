#include "esc_coe.h"
#include "utypes.h"
#include <stddef.h>

#ifndef HW_REV
#define HW_REV "1.0"
#endif

#ifndef SW_REV
#define SW_REV "1.0"
#endif

static const char acName1000[] = "Device Type";
static const char acName1008[] = "Manufacturer Device Name";
static const char acName1009[] = "Manufacturer Hardware Version";
static const char acName100A[] = "Manufacturer Software Version";
static const char acName1018[] = "Identity Object";
static const char acName1018_00[] = "Max SubIndex";
static const char acName1018_01[] = "Vendor ID";
static const char acName1018_02[] = "Product Code";
static const char acName1018_03[] = "Revision Number";
static const char acName1018_04[] = "Serial Number";
static const char acName1600[] = "Motor1_Set";
static const char acName1600_00[] = "Max SubIndex";
static const char acName1600_01[] = "Enable";
static const char acName1600_02[] = "Mode";
static const char acName1600_03[] = "IqSet";
static const char acName1600_04[] = "SetSpeed";
static const char acName1600_05[] = "SetRawAngle";
static const char acName1600_06[] = "SetTrajectoryAngle";
static const char acName1600_07[] = "SetCurrentLimit";
static const char acName1601[] = "Motor2_Set";
static const char acName1601_00[] = "Max SubIndex";
static const char acName1601_01[] = "Enable";
static const char acName1601_02[] = "Mode";
static const char acName1601_03[] = "IqSet";
static const char acName1601_04[] = "SetSpeed";
static const char acName1601_05[] = "SetRawAngle";
static const char acName1601_06[] = "SetTrajectoryAngle";
static const char acName1601_07[] = "SetCurrentLimit";
static const char acName1602[] = "Motor3_Set";
static const char acName1602_00[] = "Max SubIndex";
static const char acName1602_01[] = "Enable";
static const char acName1602_02[] = "Mode";
static const char acName1602_03[] = "IqSet";
static const char acName1602_04[] = "SetSpeed";
static const char acName1602_05[] = "SetRawAngle";
static const char acName1602_06[] = "SetTrajectoryAngle";
static const char acName1602_07[] = "SetCurrentLimit";
static const char acName1603[] = "Motor4_Set";
static const char acName1603_00[] = "Max SubIndex";
static const char acName1603_01[] = "Enable";
static const char acName1603_02[] = "Mode";
static const char acName1603_03[] = "IqSet";
static const char acName1603_04[] = "SetSpeed";
static const char acName1603_05[] = "SetRawAngle";
static const char acName1603_06[] = "SetTrajectoryAngle";
static const char acName1603_07[] = "SetCurrentLimit";
static const char acName1604[] = "Motor5_Set";
static const char acName1604_00[] = "Max SubIndex";
static const char acName1604_01[] = "Enable";
static const char acName1604_02[] = "Mode";
static const char acName1604_03[] = "IqSet";
static const char acName1604_04[] = "SetSpeed";
static const char acName1604_05[] = "SetRawAngle";
static const char acName1604_06[] = "SetTrajectoryAngle";
static const char acName1604_07[] = "SetCurrentLimit";
static const char acName1605[] = "Motor6_Set";
static const char acName1605_00[] = "Max SubIndex";
static const char acName1605_01[] = "Enable";
static const char acName1605_02[] = "Mode";
static const char acName1605_03[] = "IqSet";
static const char acName1605_04[] = "SetSpeed";
static const char acName1605_05[] = "SetRawAngle";
static const char acName1605_06[] = "SetTrajectoryAngle";
static const char acName1605_07[] = "SetCurrentLimit";
static const char acName1606[] = "Motor7_Set";
static const char acName1606_00[] = "Max SubIndex";
static const char acName1606_01[] = "Enable";
static const char acName1606_02[] = "Mode";
static const char acName1606_03[] = "IqSet";
static const char acName1606_04[] = "SetSpeed";
static const char acName1606_05[] = "SetRawAngle";
static const char acName1606_06[] = "SetTrajectoryAngle";
static const char acName1606_07[] = "SetCurrentLimit";
static const char acName1607[] = "Motor8_Set";
static const char acName1607_00[] = "Max SubIndex";
static const char acName1607_01[] = "Enable";
static const char acName1607_02[] = "Mode";
static const char acName1607_03[] = "IqSet";
static const char acName1607_04[] = "SetSpeed";
static const char acName1607_05[] = "SetRawAngle";
static const char acName1607_06[] = "SetTrajectoryAngle";
static const char acName1607_07[] = "SetCurrentLimit";
static const char acName1608[] = "RxBuf";
static const char acName1608_00[] = "Max SubIndex";
static const char acName1608_01[] = "RxBuf Packet Header";
static const char acName1608_02[] = "RxBuf Packet ID";
static const char acName1608_03[] = "RxBuf Sender ID";
static const char acName1608_04[] = "RxBuf Receiver ID";
static const char acName1608_05[] = "RxBuf IsReturn";
static const char acName1608_06[] = "RxBuf Payload 0";
static const char acName1608_07[] = "RxBuf Payload 1";
static const char acName1608_08[] = "RxBuf Payload 2";
static const char acName1608_09[] = "RxBuf Payload 3";
static const char acName1608_0A[] = "RxBuf Payload 4";
static const char acName1608_0B[] = "RxBuf Payload 5";
static const char acName1608_0C[] = "RxBuf Payload 6";
static const char acName1608_0D[] = "RxBuf Payload 7";
static const char acName1608_0E[] = "RxBuf Payload 8";
static const char acName1608_0F[] = "RxBuf Payload 9";
static const char acName1608_10[] = "RxBuf Payload 10";
static const char acName1608_11[] = "RxBuf Payload 11";
static const char acName1608_12[] = "RxBuf Payload 12";
static const char acName1608_13[] = "RxBuf Payload 13";
static const char acName1608_14[] = "RxBuf Payload 14";
static const char acName1608_15[] = "RxBuf Payload 15";
static const char acName1608_16[] = "RxBuf Payload 16";
static const char acName1608_17[] = "RxBuf Payload 17";
static const char acName1608_18[] = "RxBuf Payload 18";
static const char acName1608_19[] = "RxBuf Payload 19";
static const char acName1608_1A[] = "RxBuf Payload 20";
static const char acName1608_1B[] = "RxBuf Payload 21";
static const char acName1608_1C[] = "RxBuf Payload 22";
static const char acName1608_1D[] = "RxBuf Payload 23";
static const char acName1608_1E[] = "RxBuf Payload 24";
static const char acName1608_1F[] = "RxBuf Payload 25";
static const char acName1608_20[] = "RxBuf Payload 26";
static const char acName1608_21[] = "RxBuf Payload 27";
static const char acName1608_22[] = "RxBuf Payload 28";
static const char acName1608_23[] = "RxBuf Payload 29";
static const char acName1608_24[] = "RxBuf Payload 30";
static const char acName1608_25[] = "RxBuf Payload 31";
static const char acName1608_26[] = "RxBuf Payload 32";
static const char acName1608_27[] = "RxBuf Payload 33";
static const char acName1608_28[] = "RxBuf Payload 34";
static const char acName1608_29[] = "RxBuf Payload 35";
static const char acName1608_2A[] = "RxBuf Payload 36";
static const char acName1608_2B[] = "RxBuf Payload 37";
static const char acName1608_2C[] = "RxBuf Payload 38";
static const char acName1608_2D[] = "RxBuf Payload 39";
static const char acName1608_2E[] = "RxBuf Payload 40";
static const char acName1608_2F[] = "RxBuf CRC16 MSB";
static const char acName1608_30[] = "RxBuf CRC16 LSB";
static const char acName1A00[] = "Interface_State";
static const char acName1A00_00[] = "Max SubIndex";
static const char acName1A00_01[] = "MotorCount";
static const char acName1A00_02[] = "MCUTemp";
static const char acName1A00_03[] = "Vbus";
static const char acName1A00_04[] = "FramesPerSec";
static const char acName1A00_05[] = "Uptime";
static const char acName1A01[] = "Motor1_State";
static const char acName1A01_00[] = "Max SubIndex";
static const char acName1A01_01[] = "IsAlive";
static const char acName1A01_02[] = "Enable";
static const char acName1A01_03[] = "NodeID";
static const char acName1A01_04[] = "Mode";
static const char acName1A01_05[] = "MotorTemp";
static const char acName1A01_06[] = "MCUTemp";
static const char acName1A01_07[] = "LimiterState";
static const char acName1A01_08[] = "ErrorCode";
static const char acName1A01_09[] = "SN";
static const char acName1A01_0A[] = "IqReal";
static const char acName1A01_0B[] = "IdReal";
static const char acName1A01_0C[] = "Vbus";
static const char acName1A01_0D[] = "Ibus";
static const char acName1A01_0E[] = "EstimateSpeed";
static const char acName1A01_0F[] = "EstimateRawAngle";
static const char acName1A01_10[] = "CurrentLimit";
static const char acName1A02[] = "Motor2_State";
static const char acName1A02_00[] = "Max SubIndex";
static const char acName1A02_01[] = "IsAlive";
static const char acName1A02_02[] = "Enable";
static const char acName1A02_03[] = "NodeID";
static const char acName1A02_04[] = "Mode";
static const char acName1A02_05[] = "MotorTemp";
static const char acName1A02_06[] = "MCUTemp";
static const char acName1A02_07[] = "LimiterState";
static const char acName1A02_08[] = "ErrorCode";
static const char acName1A02_09[] = "SN";
static const char acName1A02_0A[] = "IqReal";
static const char acName1A02_0B[] = "IdReal";
static const char acName1A02_0C[] = "Vbus";
static const char acName1A02_0D[] = "Ibus";
static const char acName1A02_0E[] = "EstimateSpeed";
static const char acName1A02_0F[] = "EstimateRawAngle";
static const char acName1A02_10[] = "CurrentLimit";
static const char acName1A03[] = "Motor3_State";
static const char acName1A03_00[] = "Max SubIndex";
static const char acName1A03_01[] = "IsAlive";
static const char acName1A03_02[] = "Enable";
static const char acName1A03_03[] = "NodeID";
static const char acName1A03_04[] = "Mode";
static const char acName1A03_05[] = "MotorTemp";
static const char acName1A03_06[] = "MCUTemp";
static const char acName1A03_07[] = "LimiterState";
static const char acName1A03_08[] = "ErrorCode";
static const char acName1A03_09[] = "SN";
static const char acName1A03_0A[] = "IqReal";
static const char acName1A03_0B[] = "IdReal";
static const char acName1A03_0C[] = "Vbus";
static const char acName1A03_0D[] = "Ibus";
static const char acName1A03_0E[] = "EstimateSpeed";
static const char acName1A03_0F[] = "EstimateRawAngle";
static const char acName1A03_10[] = "CurrentLimit";
static const char acName1A04[] = "Motor4_State";
static const char acName1A04_00[] = "Max SubIndex";
static const char acName1A04_01[] = "IsAlive";
static const char acName1A04_02[] = "Enable";
static const char acName1A04_03[] = "NodeID";
static const char acName1A04_04[] = "Mode";
static const char acName1A04_05[] = "MotorTemp";
static const char acName1A04_06[] = "MCUTemp";
static const char acName1A04_07[] = "LimiterState";
static const char acName1A04_08[] = "ErrorCode";
static const char acName1A04_09[] = "SN";
static const char acName1A04_0A[] = "IqReal";
static const char acName1A04_0B[] = "IdReal";
static const char acName1A04_0C[] = "Vbus";
static const char acName1A04_0D[] = "Ibus";
static const char acName1A04_0E[] = "EstimateSpeed";
static const char acName1A04_0F[] = "EstimateRawAngle";
static const char acName1A04_10[] = "CurrentLimit";
static const char acName1A05[] = "Motor5_State";
static const char acName1A05_00[] = "Max SubIndex";
static const char acName1A05_01[] = "IsAlive";
static const char acName1A05_02[] = "Enable";
static const char acName1A05_03[] = "NodeID";
static const char acName1A05_04[] = "Mode";
static const char acName1A05_05[] = "MotorTemp";
static const char acName1A05_06[] = "MCUTemp";
static const char acName1A05_07[] = "LimiterState";
static const char acName1A05_08[] = "ErrorCode";
static const char acName1A05_09[] = "SN";
static const char acName1A05_0A[] = "IqReal";
static const char acName1A05_0B[] = "IdReal";
static const char acName1A05_0C[] = "Vbus";
static const char acName1A05_0D[] = "Ibus";
static const char acName1A05_0E[] = "EstimateSpeed";
static const char acName1A05_0F[] = "EstimateRawAngle";
static const char acName1A05_10[] = "CurrentLimit";
static const char acName1A06[] = "Motor6_State";
static const char acName1A06_00[] = "Max SubIndex";
static const char acName1A06_01[] = "IsAlive";
static const char acName1A06_02[] = "Enable";
static const char acName1A06_03[] = "NodeID";
static const char acName1A06_04[] = "Mode";
static const char acName1A06_05[] = "MotorTemp";
static const char acName1A06_06[] = "MCUTemp";
static const char acName1A06_07[] = "LimiterState";
static const char acName1A06_08[] = "ErrorCode";
static const char acName1A06_09[] = "SN";
static const char acName1A06_0A[] = "IqReal";
static const char acName1A06_0B[] = "IdReal";
static const char acName1A06_0C[] = "Vbus";
static const char acName1A06_0D[] = "Ibus";
static const char acName1A06_0E[] = "EstimateSpeed";
static const char acName1A06_0F[] = "EstimateRawAngle";
static const char acName1A06_10[] = "CurrentLimit";
static const char acName1A07[] = "Motor7_State";
static const char acName1A07_00[] = "Max SubIndex";
static const char acName1A07_01[] = "IsAlive";
static const char acName1A07_02[] = "Enable";
static const char acName1A07_03[] = "NodeID";
static const char acName1A07_04[] = "Mode";
static const char acName1A07_05[] = "MotorTemp";
static const char acName1A07_06[] = "MCUTemp";
static const char acName1A07_07[] = "LimiterState";
static const char acName1A07_08[] = "ErrorCode";
static const char acName1A07_09[] = "SN";
static const char acName1A07_0A[] = "IqReal";
static const char acName1A07_0B[] = "IdReal";
static const char acName1A07_0C[] = "Vbus";
static const char acName1A07_0D[] = "Ibus";
static const char acName1A07_0E[] = "EstimateSpeed";
static const char acName1A07_0F[] = "EstimateRawAngle";
static const char acName1A07_10[] = "CurrentLimit";
static const char acName1A08[] = "Motor8_State";
static const char acName1A08_00[] = "Max SubIndex";
static const char acName1A08_01[] = "IsAlive";
static const char acName1A08_02[] = "Enable";
static const char acName1A08_03[] = "NodeID";
static const char acName1A08_04[] = "Mode";
static const char acName1A08_05[] = "MotorTemp";
static const char acName1A08_06[] = "MCUTemp";
static const char acName1A08_07[] = "LimiterState";
static const char acName1A08_08[] = "ErrorCode";
static const char acName1A08_09[] = "SN";
static const char acName1A08_0A[] = "IqReal";
static const char acName1A08_0B[] = "IdReal";
static const char acName1A08_0C[] = "Vbus";
static const char acName1A08_0D[] = "Ibus";
static const char acName1A08_0E[] = "EstimateSpeed";
static const char acName1A08_0F[] = "EstimateRawAngle";
static const char acName1A08_10[] = "CurrentLimit";
static const char acName1A09[] = "TxBuf";
static const char acName1A09_00[] = "Max SubIndex";
static const char acName1A09_01[] = "TxBuf Packet Header";
static const char acName1A09_02[] = "TxBuf Packet ID";
static const char acName1A09_03[] = "TxBuf Sender ID";
static const char acName1A09_04[] = "TxBuf Receiver ID";
static const char acName1A09_05[] = "TxBuf IsReturn";
static const char acName1A09_06[] = "TxBuf Payload 0";
static const char acName1A09_07[] = "TxBuf Payload 1";
static const char acName1A09_08[] = "TxBuf Payload 2";
static const char acName1A09_09[] = "TxBuf Payload 3";
static const char acName1A09_0A[] = "TxBuf Payload 4";
static const char acName1A09_0B[] = "TxBuf Payload 5";
static const char acName1A09_0C[] = "TxBuf Payload 6";
static const char acName1A09_0D[] = "TxBuf Payload 7";
static const char acName1A09_0E[] = "TxBuf Payload 8";
static const char acName1A09_0F[] = "TxBuf Payload 9";
static const char acName1A09_10[] = "TxBuf Payload 10";
static const char acName1A09_11[] = "TxBuf Payload 11";
static const char acName1A09_12[] = "TxBuf Payload 12";
static const char acName1A09_13[] = "TxBuf Payload 13";
static const char acName1A09_14[] = "TxBuf Payload 14";
static const char acName1A09_15[] = "TxBuf Payload 15";
static const char acName1A09_16[] = "TxBuf Payload 16";
static const char acName1A09_17[] = "TxBuf Payload 17";
static const char acName1A09_18[] = "TxBuf Payload 18";
static const char acName1A09_19[] = "TxBuf Payload 19";
static const char acName1A09_1A[] = "TxBuf Payload 20";
static const char acName1A09_1B[] = "TxBuf Payload 21";
static const char acName1A09_1C[] = "TxBuf Payload 22";
static const char acName1A09_1D[] = "TxBuf Payload 23";
static const char acName1A09_1E[] = "TxBuf Payload 24";
static const char acName1A09_1F[] = "TxBuf Payload 25";
static const char acName1A09_20[] = "TxBuf Payload 26";
static const char acName1A09_21[] = "TxBuf Payload 27";
static const char acName1A09_22[] = "TxBuf Payload 28";
static const char acName1A09_23[] = "TxBuf Payload 29";
static const char acName1A09_24[] = "TxBuf Payload 30";
static const char acName1A09_25[] = "TxBuf Payload 31";
static const char acName1A09_26[] = "TxBuf Payload 32";
static const char acName1A09_27[] = "TxBuf Payload 33";
static const char acName1A09_28[] = "TxBuf Payload 34";
static const char acName1A09_29[] = "TxBuf Payload 35";
static const char acName1A09_2A[] = "TxBuf Payload 36";
static const char acName1A09_2B[] = "TxBuf Payload 37";
static const char acName1A09_2C[] = "TxBuf Payload 38";
static const char acName1A09_2D[] = "TxBuf Payload 39";
static const char acName1A09_2E[] = "TxBuf Payload 40";
static const char acName1A09_2F[] = "TxBuf CRC16 MSB";
static const char acName1A09_30[] = "TxBuf CRC16 LSB";
static const char acName1C00[] = "Sync Manager Communication Type";
static const char acName1C00_00[] = "Max SubIndex";
static const char acName1C00_01[] = "Communications Type SM0";
static const char acName1C00_02[] = "Communications Type SM1";
static const char acName1C00_03[] = "Communications Type SM2";
static const char acName1C00_04[] = "Communications Type SM3";
static const char acName1C12[] = "Sync Manager 2 PDO Assignment";
static const char acName1C12_00[] = "Max SubIndex";
static const char acName1C12_01[] = "PDO Mapping";
static const char acName1C12_02[] = "PDO Mapping";
static const char acName1C12_03[] = "PDO Mapping";
static const char acName1C12_04[] = "PDO Mapping";
static const char acName1C12_05[] = "PDO Mapping";
static const char acName1C12_06[] = "PDO Mapping";
static const char acName1C12_07[] = "PDO Mapping";
static const char acName1C12_08[] = "PDO Mapping";
static const char acName1C12_09[] = "PDO Mapping";
static const char acName1C13[] = "Sync Manager 3 PDO Assignment";
static const char acName1C13_00[] = "Max SubIndex";
static const char acName1C13_01[] = "PDO Mapping";
static const char acName1C13_02[] = "PDO Mapping";
static const char acName1C13_03[] = "PDO Mapping";
static const char acName1C13_04[] = "PDO Mapping";
static const char acName1C13_05[] = "PDO Mapping";
static const char acName1C13_06[] = "PDO Mapping";
static const char acName1C13_07[] = "PDO Mapping";
static const char acName1C13_08[] = "PDO Mapping";
static const char acName1C13_09[] = "PDO Mapping";
static const char acName1C13_0A[] = "PDO Mapping";
static const char acName6000[] = "Interface_State";
static const char acName6000_00[] = "Max SubIndex";
static const char acName6000_01[] = "MotorCount";
static const char acName6000_02[] = "MCUTemp";
static const char acName6000_03[] = "Vbus";
static const char acName6000_04[] = "FramesPerSec";
static const char acName6000_05[] = "Uptime";
static const char acName6001[] = "Motor1_State";
static const char acName6001_00[] = "Max SubIndex";
static const char acName6001_01[] = "IsAlive";
static const char acName6001_02[] = "Enable";
static const char acName6001_03[] = "NodeID";
static const char acName6001_04[] = "Mode";
static const char acName6001_05[] = "MotorTemp";
static const char acName6001_06[] = "MCUTemp";
static const char acName6001_07[] = "LimiterState";
static const char acName6001_08[] = "ErrorCode";
static const char acName6001_09[] = "SN";
static const char acName6001_0A[] = "IqReal";
static const char acName6001_0B[] = "IdReal";
static const char acName6001_0C[] = "Vbus";
static const char acName6001_0D[] = "Ibus";
static const char acName6001_0E[] = "EstimateSpeed";
static const char acName6001_0F[] = "EstimateRawAngle";
static const char acName6001_10[] = "CurrentLimit";
static const char acName6002[] = "Motor2_State";
static const char acName6002_00[] = "Max SubIndex";
static const char acName6002_01[] = "IsAlive";
static const char acName6002_02[] = "Enable";
static const char acName6002_03[] = "NodeID";
static const char acName6002_04[] = "Mode";
static const char acName6002_05[] = "MotorTemp";
static const char acName6002_06[] = "MCUTemp";
static const char acName6002_07[] = "LimiterState";
static const char acName6002_08[] = "ErrorCode";
static const char acName6002_09[] = "SN";
static const char acName6002_0A[] = "IqReal";
static const char acName6002_0B[] = "IdReal";
static const char acName6002_0C[] = "Vbus";
static const char acName6002_0D[] = "Ibus";
static const char acName6002_0E[] = "EstimateSpeed";
static const char acName6002_0F[] = "EstimateRawAngle";
static const char acName6002_10[] = "CurrentLimit";
static const char acName6003[] = "Motor3_State";
static const char acName6003_00[] = "Max SubIndex";
static const char acName6003_01[] = "IsAlive";
static const char acName6003_02[] = "Enable";
static const char acName6003_03[] = "NodeID";
static const char acName6003_04[] = "Mode";
static const char acName6003_05[] = "MotorTemp";
static const char acName6003_06[] = "MCUTemp";
static const char acName6003_07[] = "LimiterState";
static const char acName6003_08[] = "ErrorCode";
static const char acName6003_09[] = "SN";
static const char acName6003_0A[] = "IqReal";
static const char acName6003_0B[] = "IdReal";
static const char acName6003_0C[] = "Vbus";
static const char acName6003_0D[] = "Ibus";
static const char acName6003_0E[] = "EstimateSpeed";
static const char acName6003_0F[] = "EstimateRawAngle";
static const char acName6003_10[] = "CurrentLimit";
static const char acName6004[] = "Motor4_State";
static const char acName6004_00[] = "Max SubIndex";
static const char acName6004_01[] = "IsAlive";
static const char acName6004_02[] = "Enable";
static const char acName6004_03[] = "NodeID";
static const char acName6004_04[] = "Mode";
static const char acName6004_05[] = "MotorTemp";
static const char acName6004_06[] = "MCUTemp";
static const char acName6004_07[] = "LimiterState";
static const char acName6004_08[] = "ErrorCode";
static const char acName6004_09[] = "SN";
static const char acName6004_0A[] = "IqReal";
static const char acName6004_0B[] = "IdReal";
static const char acName6004_0C[] = "Vbus";
static const char acName6004_0D[] = "Ibus";
static const char acName6004_0E[] = "EstimateSpeed";
static const char acName6004_0F[] = "EstimateRawAngle";
static const char acName6004_10[] = "CurrentLimit";
static const char acName6005[] = "Motor5_State";
static const char acName6005_00[] = "Max SubIndex";
static const char acName6005_01[] = "IsAlive";
static const char acName6005_02[] = "Enable";
static const char acName6005_03[] = "NodeID";
static const char acName6005_04[] = "Mode";
static const char acName6005_05[] = "MotorTemp";
static const char acName6005_06[] = "MCUTemp";
static const char acName6005_07[] = "LimiterState";
static const char acName6005_08[] = "ErrorCode";
static const char acName6005_09[] = "SN";
static const char acName6005_0A[] = "IqReal";
static const char acName6005_0B[] = "IdReal";
static const char acName6005_0C[] = "Vbus";
static const char acName6005_0D[] = "Ibus";
static const char acName6005_0E[] = "EstimateSpeed";
static const char acName6005_0F[] = "EstimateRawAngle";
static const char acName6005_10[] = "CurrentLimit";
static const char acName6006[] = "Motor6_State";
static const char acName6006_00[] = "Max SubIndex";
static const char acName6006_01[] = "IsAlive";
static const char acName6006_02[] = "Enable";
static const char acName6006_03[] = "NodeID";
static const char acName6006_04[] = "Mode";
static const char acName6006_05[] = "MotorTemp";
static const char acName6006_06[] = "MCUTemp";
static const char acName6006_07[] = "LimiterState";
static const char acName6006_08[] = "ErrorCode";
static const char acName6006_09[] = "SN";
static const char acName6006_0A[] = "IqReal";
static const char acName6006_0B[] = "IdReal";
static const char acName6006_0C[] = "Vbus";
static const char acName6006_0D[] = "Ibus";
static const char acName6006_0E[] = "EstimateSpeed";
static const char acName6006_0F[] = "EstimateRawAngle";
static const char acName6006_10[] = "CurrentLimit";
static const char acName6007[] = "Motor7_State";
static const char acName6007_00[] = "Max SubIndex";
static const char acName6007_01[] = "IsAlive";
static const char acName6007_02[] = "Enable";
static const char acName6007_03[] = "NodeID";
static const char acName6007_04[] = "Mode";
static const char acName6007_05[] = "MotorTemp";
static const char acName6007_06[] = "MCUTemp";
static const char acName6007_07[] = "LimiterState";
static const char acName6007_08[] = "ErrorCode";
static const char acName6007_09[] = "SN";
static const char acName6007_0A[] = "IqReal";
static const char acName6007_0B[] = "IdReal";
static const char acName6007_0C[] = "Vbus";
static const char acName6007_0D[] = "Ibus";
static const char acName6007_0E[] = "EstimateSpeed";
static const char acName6007_0F[] = "EstimateRawAngle";
static const char acName6007_10[] = "CurrentLimit";
static const char acName6008[] = "Motor8_State";
static const char acName6008_00[] = "Max SubIndex";
static const char acName6008_01[] = "IsAlive";
static const char acName6008_02[] = "Enable";
static const char acName6008_03[] = "NodeID";
static const char acName6008_04[] = "Mode";
static const char acName6008_05[] = "MotorTemp";
static const char acName6008_06[] = "MCUTemp";
static const char acName6008_07[] = "LimiterState";
static const char acName6008_08[] = "ErrorCode";
static const char acName6008_09[] = "SN";
static const char acName6008_0A[] = "IqReal";
static const char acName6008_0B[] = "IdReal";
static const char acName6008_0C[] = "Vbus";
static const char acName6008_0D[] = "Ibus";
static const char acName6008_0E[] = "EstimateSpeed";
static const char acName6008_0F[] = "EstimateRawAngle";
static const char acName6008_10[] = "CurrentLimit";
static const char acName6009[] = "TxBuf";
static const char acName6009_00[] = "Max SubIndex";
static const char acName6009_01[] = "TxBuf Packet Header";
static const char acName6009_02[] = "TxBuf Packet ID";
static const char acName6009_03[] = "TxBuf Sender ID";
static const char acName6009_04[] = "TxBuf Receiver ID";
static const char acName6009_05[] = "TxBuf IsReturn";
static const char acName6009_06[] = "TxBuf Payload 0";
static const char acName6009_07[] = "TxBuf Payload 1";
static const char acName6009_08[] = "TxBuf Payload 2";
static const char acName6009_09[] = "TxBuf Payload 3";
static const char acName6009_0A[] = "TxBuf Payload 4";
static const char acName6009_0B[] = "TxBuf Payload 5";
static const char acName6009_0C[] = "TxBuf Payload 6";
static const char acName6009_0D[] = "TxBuf Payload 7";
static const char acName6009_0E[] = "TxBuf Payload 8";
static const char acName6009_0F[] = "TxBuf Payload 9";
static const char acName6009_10[] = "TxBuf Payload 10";
static const char acName6009_11[] = "TxBuf Payload 11";
static const char acName6009_12[] = "TxBuf Payload 12";
static const char acName6009_13[] = "TxBuf Payload 13";
static const char acName6009_14[] = "TxBuf Payload 14";
static const char acName6009_15[] = "TxBuf Payload 15";
static const char acName6009_16[] = "TxBuf Payload 16";
static const char acName6009_17[] = "TxBuf Payload 17";
static const char acName6009_18[] = "TxBuf Payload 18";
static const char acName6009_19[] = "TxBuf Payload 19";
static const char acName6009_1A[] = "TxBuf Payload 20";
static const char acName6009_1B[] = "TxBuf Payload 21";
static const char acName6009_1C[] = "TxBuf Payload 22";
static const char acName6009_1D[] = "TxBuf Payload 23";
static const char acName6009_1E[] = "TxBuf Payload 24";
static const char acName6009_1F[] = "TxBuf Payload 25";
static const char acName6009_20[] = "TxBuf Payload 26";
static const char acName6009_21[] = "TxBuf Payload 27";
static const char acName6009_22[] = "TxBuf Payload 28";
static const char acName6009_23[] = "TxBuf Payload 29";
static const char acName6009_24[] = "TxBuf Payload 30";
static const char acName6009_25[] = "TxBuf Payload 31";
static const char acName6009_26[] = "TxBuf Payload 32";
static const char acName6009_27[] = "TxBuf Payload 33";
static const char acName6009_28[] = "TxBuf Payload 34";
static const char acName6009_29[] = "TxBuf Payload 35";
static const char acName6009_2A[] = "TxBuf Payload 36";
static const char acName6009_2B[] = "TxBuf Payload 37";
static const char acName6009_2C[] = "TxBuf Payload 38";
static const char acName6009_2D[] = "TxBuf Payload 39";
static const char acName6009_2E[] = "TxBuf Payload 40";
static const char acName6009_2F[] = "TxBuf CRC16 MSB";
static const char acName6009_30[] = "TxBuf CRC16 LSB";
static const char acName7000[] = "Motor1_Set";
static const char acName7000_00[] = "Max SubIndex";
static const char acName7000_01[] = "Enable";
static const char acName7000_02[] = "Mode";
static const char acName7000_03[] = "IqSet";
static const char acName7000_04[] = "SetSpeed";
static const char acName7000_05[] = "SetRawAngle";
static const char acName7000_06[] = "SetTrajectoryAngle";
static const char acName7000_07[] = "SetCurrentLimit";
static const char acName7001[] = "Motor2_Set";
static const char acName7001_00[] = "Max SubIndex";
static const char acName7001_01[] = "Enable";
static const char acName7001_02[] = "Mode";
static const char acName7001_03[] = "IqSet";
static const char acName7001_04[] = "SetSpeed";
static const char acName7001_05[] = "SetRawAngle";
static const char acName7001_06[] = "SetTrajectoryAngle";
static const char acName7001_07[] = "SetCurrentLimit";
static const char acName7002[] = "Motor3_Set";
static const char acName7002_00[] = "Max SubIndex";
static const char acName7002_01[] = "Enable";
static const char acName7002_02[] = "Mode";
static const char acName7002_03[] = "IqSet";
static const char acName7002_04[] = "SetSpeed";
static const char acName7002_05[] = "SetRawAngle";
static const char acName7002_06[] = "SetTrajectoryAngle";
static const char acName7002_07[] = "SetCurrentLimit";
static const char acName7003[] = "Motor4_Set";
static const char acName7003_00[] = "Max SubIndex";
static const char acName7003_01[] = "Enable";
static const char acName7003_02[] = "Mode";
static const char acName7003_03[] = "IqSet";
static const char acName7003_04[] = "SetSpeed";
static const char acName7003_05[] = "SetRawAngle";
static const char acName7003_06[] = "SetTrajectoryAngle";
static const char acName7003_07[] = "SetCurrentLimit";
static const char acName7004[] = "Motor5_Set";
static const char acName7004_00[] = "Max SubIndex";
static const char acName7004_01[] = "Enable";
static const char acName7004_02[] = "Mode";
static const char acName7004_03[] = "IqSet";
static const char acName7004_04[] = "SetSpeed";
static const char acName7004_05[] = "SetRawAngle";
static const char acName7004_06[] = "SetTrajectoryAngle";
static const char acName7004_07[] = "SetCurrentLimit";
static const char acName7005[] = "Motor6_Set";
static const char acName7005_00[] = "Max SubIndex";
static const char acName7005_01[] = "Enable";
static const char acName7005_02[] = "Mode";
static const char acName7005_03[] = "IqSet";
static const char acName7005_04[] = "SetSpeed";
static const char acName7005_05[] = "SetRawAngle";
static const char acName7005_06[] = "SetTrajectoryAngle";
static const char acName7005_07[] = "SetCurrentLimit";
static const char acName7006[] = "Motor7_Set";
static const char acName7006_00[] = "Max SubIndex";
static const char acName7006_01[] = "Enable";
static const char acName7006_02[] = "Mode";
static const char acName7006_03[] = "IqSet";
static const char acName7006_04[] = "SetSpeed";
static const char acName7006_05[] = "SetRawAngle";
static const char acName7006_06[] = "SetTrajectoryAngle";
static const char acName7006_07[] = "SetCurrentLimit";
static const char acName7007[] = "Motor8_Set";
static const char acName7007_00[] = "Max SubIndex";
static const char acName7007_01[] = "Enable";
static const char acName7007_02[] = "Mode";
static const char acName7007_03[] = "IqSet";
static const char acName7007_04[] = "SetSpeed";
static const char acName7007_05[] = "SetRawAngle";
static const char acName7007_06[] = "SetTrajectoryAngle";
static const char acName7007_07[] = "SetCurrentLimit";
static const char acName7008[] = "RxBuf";
static const char acName7008_00[] = "Max SubIndex";
static const char acName7008_01[] = "RxBuf Packet Header";
static const char acName7008_02[] = "RxBuf Packet ID";
static const char acName7008_03[] = "RxBuf Sender ID";
static const char acName7008_04[] = "RxBuf Receiver ID";
static const char acName7008_05[] = "RxBuf IsReturn";
static const char acName7008_06[] = "RxBuf Payload 0";
static const char acName7008_07[] = "RxBuf Payload 1";
static const char acName7008_08[] = "RxBuf Payload 2";
static const char acName7008_09[] = "RxBuf Payload 3";
static const char acName7008_0A[] = "RxBuf Payload 4";
static const char acName7008_0B[] = "RxBuf Payload 5";
static const char acName7008_0C[] = "RxBuf Payload 6";
static const char acName7008_0D[] = "RxBuf Payload 7";
static const char acName7008_0E[] = "RxBuf Payload 8";
static const char acName7008_0F[] = "RxBuf Payload 9";
static const char acName7008_10[] = "RxBuf Payload 10";
static const char acName7008_11[] = "RxBuf Payload 11";
static const char acName7008_12[] = "RxBuf Payload 12";
static const char acName7008_13[] = "RxBuf Payload 13";
static const char acName7008_14[] = "RxBuf Payload 14";
static const char acName7008_15[] = "RxBuf Payload 15";
static const char acName7008_16[] = "RxBuf Payload 16";
static const char acName7008_17[] = "RxBuf Payload 17";
static const char acName7008_18[] = "RxBuf Payload 18";
static const char acName7008_19[] = "RxBuf Payload 19";
static const char acName7008_1A[] = "RxBuf Payload 20";
static const char acName7008_1B[] = "RxBuf Payload 21";
static const char acName7008_1C[] = "RxBuf Payload 22";
static const char acName7008_1D[] = "RxBuf Payload 23";
static const char acName7008_1E[] = "RxBuf Payload 24";
static const char acName7008_1F[] = "RxBuf Payload 25";
static const char acName7008_20[] = "RxBuf Payload 26";
static const char acName7008_21[] = "RxBuf Payload 27";
static const char acName7008_22[] = "RxBuf Payload 28";
static const char acName7008_23[] = "RxBuf Payload 29";
static const char acName7008_24[] = "RxBuf Payload 30";
static const char acName7008_25[] = "RxBuf Payload 31";
static const char acName7008_26[] = "RxBuf Payload 32";
static const char acName7008_27[] = "RxBuf Payload 33";
static const char acName7008_28[] = "RxBuf Payload 34";
static const char acName7008_29[] = "RxBuf Payload 35";
static const char acName7008_2A[] = "RxBuf Payload 36";
static const char acName7008_2B[] = "RxBuf Payload 37";
static const char acName7008_2C[] = "RxBuf Payload 38";
static const char acName7008_2D[] = "RxBuf Payload 39";
static const char acName7008_2E[] = "RxBuf Payload 40";
static const char acName7008_2F[] = "RxBuf CRC16 MSB";
static const char acName7008_30[] = "RxBuf CRC16 LSB";

const _objd SDO1000[] =
{
  {0x0, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1000, 0x01901389, NULL},
};
const _objd SDO1008[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 112, ATYPE_RO, acName1008, 0, "iFOC_Interface"},
};
const _objd SDO1009[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 24, ATYPE_RO, acName1009, 0, HW_REV},
};
const _objd SDO100A[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 24, ATYPE_RO, acName100A, 0, SW_REV},
};
const _objd SDO1018[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1018_00, 4, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_01, 0x1337, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_02, 1234, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_03, 0, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1018_04, 0x00000000, &Obj.serial},
};
const _objd SDO1600[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1600_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_01, 0x70000108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_02, 0x70000208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_03, 0x70000320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_04, 0x70000420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_05, 0x70000520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_06, 0x70000620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1600_07, 0x70000720, NULL},
};
const _objd SDO1601[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1601_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_01, 0x70010108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_02, 0x70010208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_03, 0x70010320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_04, 0x70010420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_05, 0x70010520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_06, 0x70010620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1601_07, 0x70010720, NULL},
};
const _objd SDO1602[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1602_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_01, 0x70020108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_02, 0x70020208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_03, 0x70020320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_04, 0x70020420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_05, 0x70020520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_06, 0x70020620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1602_07, 0x70020720, NULL},
};
const _objd SDO1603[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1603_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_01, 0x70030108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_02, 0x70030208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_03, 0x70030320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_04, 0x70030420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_05, 0x70030520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_06, 0x70030620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1603_07, 0x70030720, NULL},
};
const _objd SDO1604[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1604_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_01, 0x70040108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_02, 0x70040208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_03, 0x70040320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_04, 0x70040420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_05, 0x70040520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_06, 0x70040620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1604_07, 0x70040720, NULL},
};
const _objd SDO1605[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1605_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_01, 0x70050108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_02, 0x70050208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_03, 0x70050320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_04, 0x70050420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_05, 0x70050520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_06, 0x70050620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1605_07, 0x70050720, NULL},
};
const _objd SDO1606[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1606_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_01, 0x70060108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_02, 0x70060208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_03, 0x70060320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_04, 0x70060420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_05, 0x70060520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_06, 0x70060620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1606_07, 0x70060720, NULL},
};
const _objd SDO1607[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1607_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_01, 0x70070108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_02, 0x70070208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_03, 0x70070320, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_04, 0x70070420, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_05, 0x70070520, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_06, 0x70070620, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1607_07, 0x70070720, NULL},
};
const _objd SDO1608[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1608_00, 48, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_01, 0x70080108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_02, 0x70080208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_03, 0x70080308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_04, 0x70080408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_05, 0x70080508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_06, 0x70080608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_07, 0x70080708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_08, 0x70080808, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_09, 0x70080908, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_0A, 0x70080A08, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_0B, 0x70080B08, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_0C, 0x70080C08, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_0D, 0x70080D08, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_0E, 0x70080E08, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_0F, 0x70080F08, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_10, 0x70081008, NULL},
  {0x11, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_11, 0x70081108, NULL},
  {0x12, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_12, 0x70081208, NULL},
  {0x13, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_13, 0x70081308, NULL},
  {0x14, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_14, 0x70081408, NULL},
  {0x15, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_15, 0x70081508, NULL},
  {0x16, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_16, 0x70081608, NULL},
  {0x17, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_17, 0x70081708, NULL},
  {0x18, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_18, 0x70081808, NULL},
  {0x19, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_19, 0x70081908, NULL},
  {0x1A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_1A, 0x70081A08, NULL},
  {0x1B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_1B, 0x70081B08, NULL},
  {0x1C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_1C, 0x70081C08, NULL},
  {0x1D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_1D, 0x70081D08, NULL},
  {0x1E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_1E, 0x70081E08, NULL},
  {0x1F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_1F, 0x70081F08, NULL},
  {0x20, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_20, 0x70082008, NULL},
  {0x21, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_21, 0x70082108, NULL},
  {0x22, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_22, 0x70082208, NULL},
  {0x23, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_23, 0x70082308, NULL},
  {0x24, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_24, 0x70082408, NULL},
  {0x25, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_25, 0x70082508, NULL},
  {0x26, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_26, 0x70082608, NULL},
  {0x27, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_27, 0x70082708, NULL},
  {0x28, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_28, 0x70082808, NULL},
  {0x29, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_29, 0x70082908, NULL},
  {0x2A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_2A, 0x70082A08, NULL},
  {0x2B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_2B, 0x70082B08, NULL},
  {0x2C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_2C, 0x70082C08, NULL},
  {0x2D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_2D, 0x70082D08, NULL},
  {0x2E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_2E, 0x70082E08, NULL},
  {0x2F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_2F, 0x70082F08, NULL},
  {0x30, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1608_30, 0x70083008, NULL},
};
const _objd SDO1A00[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A00_00, 5, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_01, 0x60000108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_02, 0x60000208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_03, 0x60000310, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_04, 0x60000410, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_05, 0x60000520, NULL},
};
const _objd SDO1A01[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A01_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_01, 0x60010108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_02, 0x60010208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_03, 0x60010308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_04, 0x60010408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_05, 0x60010508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_06, 0x60010608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_07, 0x60010708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_08, 0x60010810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_09, 0x60010920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_0A, 0x60010A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_0B, 0x60010B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_0C, 0x60010C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_0D, 0x60010D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_0E, 0x60010E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_0F, 0x60010F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A01_10, 0x60011020, NULL},
};
const _objd SDO1A02[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A02_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_01, 0x60020108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_02, 0x60020208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_03, 0x60020308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_04, 0x60020408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_05, 0x60020508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_06, 0x60020608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_07, 0x60020708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_08, 0x60020810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_09, 0x60020920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_0A, 0x60020A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_0B, 0x60020B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_0C, 0x60020C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_0D, 0x60020D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_0E, 0x60020E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_0F, 0x60020F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A02_10, 0x60021020, NULL},
};
const _objd SDO1A03[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A03_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_01, 0x60030108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_02, 0x60030208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_03, 0x60030308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_04, 0x60030408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_05, 0x60030508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_06, 0x60030608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_07, 0x60030708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_08, 0x60030810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_09, 0x60030920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_0A, 0x60030A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_0B, 0x60030B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_0C, 0x60030C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_0D, 0x60030D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_0E, 0x60030E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_0F, 0x60030F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A03_10, 0x60031020, NULL},
};
const _objd SDO1A04[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A04_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_01, 0x60040108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_02, 0x60040208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_03, 0x60040308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_04, 0x60040408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_05, 0x60040508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_06, 0x60040608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_07, 0x60040708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_08, 0x60040810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_09, 0x60040920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_0A, 0x60040A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_0B, 0x60040B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_0C, 0x60040C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_0D, 0x60040D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_0E, 0x60040E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_0F, 0x60040F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A04_10, 0x60041020, NULL},
};
const _objd SDO1A05[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A05_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_01, 0x60050108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_02, 0x60050208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_03, 0x60050308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_04, 0x60050408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_05, 0x60050508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_06, 0x60050608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_07, 0x60050708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_08, 0x60050810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_09, 0x60050920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_0A, 0x60050A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_0B, 0x60050B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_0C, 0x60050C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_0D, 0x60050D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_0E, 0x60050E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_0F, 0x60050F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A05_10, 0x60051020, NULL},
};
const _objd SDO1A06[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A06_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_01, 0x60060108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_02, 0x60060208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_03, 0x60060308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_04, 0x60060408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_05, 0x60060508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_06, 0x60060608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_07, 0x60060708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_08, 0x60060810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_09, 0x60060920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_0A, 0x60060A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_0B, 0x60060B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_0C, 0x60060C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_0D, 0x60060D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_0E, 0x60060E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_0F, 0x60060F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A06_10, 0x60061020, NULL},
};
const _objd SDO1A07[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A07_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_01, 0x60070108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_02, 0x60070208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_03, 0x60070308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_04, 0x60070408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_05, 0x60070508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_06, 0x60070608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_07, 0x60070708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_08, 0x60070810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_09, 0x60070920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_0A, 0x60070A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_0B, 0x60070B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_0C, 0x60070C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_0D, 0x60070D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_0E, 0x60070E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_0F, 0x60070F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A07_10, 0x60071020, NULL},
};
const _objd SDO1A08[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A08_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_01, 0x60080108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_02, 0x60080208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_03, 0x60080308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_04, 0x60080408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_05, 0x60080508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_06, 0x60080608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_07, 0x60080708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_08, 0x60080810, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_09, 0x60080920, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_0A, 0x60080A20, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_0B, 0x60080B20, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_0C, 0x60080C20, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_0D, 0x60080D20, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_0E, 0x60080E20, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_0F, 0x60080F20, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A08_10, 0x60081020, NULL},
};
const _objd SDO1A09[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1A09_00, 48, NULL},
  {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_01, 0x60090108, NULL},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_02, 0x60090208, NULL},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_03, 0x60090308, NULL},
  {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_04, 0x60090408, NULL},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_05, 0x60090508, NULL},
  {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_06, 0x60090608, NULL},
  {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_07, 0x60090708, NULL},
  {0x08, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_08, 0x60090808, NULL},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_09, 0x60090908, NULL},
  {0x0A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_0A, 0x60090A08, NULL},
  {0x0B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_0B, 0x60090B08, NULL},
  {0x0C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_0C, 0x60090C08, NULL},
  {0x0D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_0D, 0x60090D08, NULL},
  {0x0E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_0E, 0x60090E08, NULL},
  {0x0F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_0F, 0x60090F08, NULL},
  {0x10, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_10, 0x60091008, NULL},
  {0x11, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_11, 0x60091108, NULL},
  {0x12, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_12, 0x60091208, NULL},
  {0x13, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_13, 0x60091308, NULL},
  {0x14, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_14, 0x60091408, NULL},
  {0x15, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_15, 0x60091508, NULL},
  {0x16, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_16, 0x60091608, NULL},
  {0x17, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_17, 0x60091708, NULL},
  {0x18, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_18, 0x60091808, NULL},
  {0x19, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_19, 0x60091908, NULL},
  {0x1A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_1A, 0x60091A08, NULL},
  {0x1B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_1B, 0x60091B08, NULL},
  {0x1C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_1C, 0x60091C08, NULL},
  {0x1D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_1D, 0x60091D08, NULL},
  {0x1E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_1E, 0x60091E08, NULL},
  {0x1F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_1F, 0x60091F08, NULL},
  {0x20, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_20, 0x60092008, NULL},
  {0x21, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_21, 0x60092108, NULL},
  {0x22, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_22, 0x60092208, NULL},
  {0x23, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_23, 0x60092308, NULL},
  {0x24, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_24, 0x60092408, NULL},
  {0x25, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_25, 0x60092508, NULL},
  {0x26, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_26, 0x60092608, NULL},
  {0x27, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_27, 0x60092708, NULL},
  {0x28, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_28, 0x60092808, NULL},
  {0x29, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_29, 0x60092908, NULL},
  {0x2A, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_2A, 0x60092A08, NULL},
  {0x2B, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_2B, 0x60092B08, NULL},
  {0x2C, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_2C, 0x60092C08, NULL},
  {0x2D, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_2D, 0x60092D08, NULL},
  {0x2E, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_2E, 0x60092E08, NULL},
  {0x2F, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_2F, 0x60092F08, NULL},
  {0x30, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A09_30, 0x60093008, NULL},
};
const _objd SDO1C00[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_00, 4, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_01, 1, NULL},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_02, 2, NULL},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_03, 3, NULL},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C00_04, 4, NULL},
};
const _objd SDO1C12[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C12_00, 9, NULL},
  {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_01, 0x1600, NULL},
  {0x02, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_02, 0x1601, NULL},
  {0x03, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_03, 0x1602, NULL},
  {0x04, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_04, 0x1603, NULL},
  {0x05, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_05, 0x1604, NULL},
  {0x06, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_06, 0x1605, NULL},
  {0x07, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_07, 0x1606, NULL},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_08, 0x1607, NULL},
  {0x09, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C12_09, 0x1608, NULL},
};
const _objd SDO1C13[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName1C13_00, 10, NULL},
  {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_01, 0x1A00, NULL},
  {0x02, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_02, 0x1A01, NULL},
  {0x03, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_03, 0x1A02, NULL},
  {0x04, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_04, 0x1A03, NULL},
  {0x05, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_05, 0x1A04, NULL},
  {0x06, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_06, 0x1A05, NULL},
  {0x07, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_07, 0x1A06, NULL},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_08, 0x1A07, NULL},
  {0x09, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_09, 0x1A08, NULL},
  {0x0A, DTYPE_UNSIGNED16, 16, ATYPE_RO, acName1C13_0A, 0x1A09, NULL},
};
const _objd SDO6000[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6000_00, 5, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6000_01, 0, &Obj.Interface_State.MotorCount},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6000_02, 0, &Obj.Interface_State.MCUTemp},
  {0x03, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6000_03, 0, &Obj.Interface_State.Vbus},
  {0x04, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6000_04, 0, &Obj.Interface_State.FramesPerSec},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6000_05, 0, &Obj.Interface_State.Uptime},
};
const _objd SDO6001[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6001_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_01, 0, &Obj.Motor1_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_02, 0, &Obj.Motor1_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_03, 0, &Obj.Motor1_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_04, 0, &Obj.Motor1_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_05, 0, &Obj.Motor1_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_06, 0, &Obj.Motor1_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6001_07, 0, &Obj.Motor1_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6001_08, 0, &Obj.Motor1_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_09, 0, &Obj.Motor1_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_0A, 0x00000000, &Obj.Motor1_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_0B, 0x00000000, &Obj.Motor1_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_0C, 0x00000000, &Obj.Motor1_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_0D, 0x00000000, &Obj.Motor1_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_0E, 0x00000000, &Obj.Motor1_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_0F, 0x00000000, &Obj.Motor1_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6001_10, 0x00000000, &Obj.Motor1_State.CurrentLimit},
};
const _objd SDO6002[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6002_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_01, 0, &Obj.Motor2_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_02, 0, &Obj.Motor2_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_03, 0, &Obj.Motor2_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_04, 0, &Obj.Motor2_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_05, 0, &Obj.Motor2_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_06, 0, &Obj.Motor2_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6002_07, 0, &Obj.Motor2_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6002_08, 0, &Obj.Motor2_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_09, 0, &Obj.Motor2_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_0A, 0x00000000, &Obj.Motor2_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_0B, 0x00000000, &Obj.Motor2_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_0C, 0x00000000, &Obj.Motor2_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_0D, 0x00000000, &Obj.Motor2_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_0E, 0x00000000, &Obj.Motor2_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_0F, 0x00000000, &Obj.Motor2_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6002_10, 0x00000000, &Obj.Motor2_State.CurrentLimit},
};
const _objd SDO6003[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6003_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_01, 0, &Obj.Motor3_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_02, 0, &Obj.Motor3_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_03, 0, &Obj.Motor3_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_04, 0, &Obj.Motor3_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_05, 0, &Obj.Motor3_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_06, 0, &Obj.Motor3_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6003_07, 0, &Obj.Motor3_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6003_08, 0, &Obj.Motor3_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_09, 0, &Obj.Motor3_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_0A, 0x00000000, &Obj.Motor3_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_0B, 0x00000000, &Obj.Motor3_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_0C, 0x00000000, &Obj.Motor3_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_0D, 0x00000000, &Obj.Motor3_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_0E, 0x00000000, &Obj.Motor3_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_0F, 0x00000000, &Obj.Motor3_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6003_10, 0x00000000, &Obj.Motor3_State.CurrentLimit},
};
const _objd SDO6004[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6004_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_01, 0, &Obj.Motor4_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_02, 0, &Obj.Motor4_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_03, 0, &Obj.Motor4_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_04, 0, &Obj.Motor4_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_05, 0, &Obj.Motor4_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_06, 0, &Obj.Motor4_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6004_07, 0, &Obj.Motor4_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6004_08, 0, &Obj.Motor4_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_09, 0, &Obj.Motor4_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_0A, 0x00000000, &Obj.Motor4_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_0B, 0x00000000, &Obj.Motor4_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_0C, 0x00000000, &Obj.Motor4_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_0D, 0x00000000, &Obj.Motor4_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_0E, 0x00000000, &Obj.Motor4_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_0F, 0x00000000, &Obj.Motor4_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6004_10, 0x00000000, &Obj.Motor4_State.CurrentLimit},
};
const _objd SDO6005[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6005_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_01, 0, &Obj.Motor5_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_02, 0, &Obj.Motor5_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_03, 0, &Obj.Motor5_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_04, 0, &Obj.Motor5_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_05, 0, &Obj.Motor5_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_06, 0, &Obj.Motor5_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6005_07, 0, &Obj.Motor5_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6005_08, 0, &Obj.Motor5_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_09, 0, &Obj.Motor5_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_0A, 0x00000000, &Obj.Motor5_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_0B, 0x00000000, &Obj.Motor5_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_0C, 0x00000000, &Obj.Motor5_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_0D, 0x00000000, &Obj.Motor5_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_0E, 0x00000000, &Obj.Motor5_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_0F, 0x00000000, &Obj.Motor5_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6005_10, 0x00000000, &Obj.Motor5_State.CurrentLimit},
};
const _objd SDO6006[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6006_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_01, 0, &Obj.Motor6_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_02, 0, &Obj.Motor6_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_03, 0, &Obj.Motor6_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_04, 0, &Obj.Motor6_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_05, 0, &Obj.Motor6_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_06, 0, &Obj.Motor6_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6006_07, 0, &Obj.Motor6_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6006_08, 0, &Obj.Motor6_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_09, 0, &Obj.Motor6_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_0A, 0x00000000, &Obj.Motor6_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_0B, 0x00000000, &Obj.Motor6_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_0C, 0x00000000, &Obj.Motor6_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_0D, 0x00000000, &Obj.Motor6_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_0E, 0x00000000, &Obj.Motor6_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_0F, 0x00000000, &Obj.Motor6_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6006_10, 0x00000000, &Obj.Motor6_State.CurrentLimit},
};
const _objd SDO6007[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6007_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_01, 0, &Obj.Motor7_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_02, 0, &Obj.Motor7_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_03, 0, &Obj.Motor7_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_04, 0, &Obj.Motor7_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_05, 0, &Obj.Motor7_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_06, 0, &Obj.Motor7_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6007_07, 0, &Obj.Motor7_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6007_08, 0, &Obj.Motor7_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_09, 0, &Obj.Motor7_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_0A, 0x00000000, &Obj.Motor7_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_0B, 0x00000000, &Obj.Motor7_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_0C, 0x00000000, &Obj.Motor7_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_0D, 0x00000000, &Obj.Motor7_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_0E, 0x00000000, &Obj.Motor7_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_0F, 0x00000000, &Obj.Motor7_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6007_10, 0x00000000, &Obj.Motor7_State.CurrentLimit},
};
const _objd SDO6008[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6008_00, 16, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_01, 0, &Obj.Motor8_State.IsAlive},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_02, 0, &Obj.Motor8_State.Enable},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_03, 0, &Obj.Motor8_State.NodeID},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_04, 0, &Obj.Motor8_State.Mode},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_05, 0, &Obj.Motor8_State.MotorTemp},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_06, 0, &Obj.Motor8_State.MCUTemp},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6008_07, 0, &Obj.Motor8_State.LimiterState},
  {0x08, DTYPE_UNSIGNED16, 16, ATYPE_RO | ATYPE_TXPDO, acName6008_08, 0, &Obj.Motor8_State.ErrorCode},
  {0x09, DTYPE_UNSIGNED32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_09, 0, &Obj.Motor8_State.SN},
  {0x0A, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_0A, 0x00000000, &Obj.Motor8_State.IqReal},
  {0x0B, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_0B, 0x00000000, &Obj.Motor8_State.IdReal},
  {0x0C, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_0C, 0x00000000, &Obj.Motor8_State.Vbus},
  {0x0D, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_0D, 0x00000000, &Obj.Motor8_State.Ibus},
  {0x0E, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_0E, 0x00000000, &Obj.Motor8_State.EstimateSpeed},
  {0x0F, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_0F, 0x00000000, &Obj.Motor8_State.EstimateRawAngle},
  {0x10, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_TXPDO, acName6008_10, 0x00000000, &Obj.Motor8_State.CurrentLimit},
};
const _objd SDO6009[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName6009_00, 48, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_01, 0, &Obj.TxBuf[0]},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_02, 0, &Obj.TxBuf[1]},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_03, 0, &Obj.TxBuf[2]},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_04, 0, &Obj.TxBuf[3]},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_05, 0, &Obj.TxBuf[4]},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_06, 0, &Obj.TxBuf[5]},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_07, 0, &Obj.TxBuf[6]},
  {0x08, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_08, 0, &Obj.TxBuf[7]},
  {0x09, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_09, 0, &Obj.TxBuf[8]},
  {0x0A, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_0A, 0, &Obj.TxBuf[9]},
  {0x0B, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_0B, 0, &Obj.TxBuf[10]},
  {0x0C, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_0C, 0, &Obj.TxBuf[11]},
  {0x0D, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_0D, 0, &Obj.TxBuf[12]},
  {0x0E, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_0E, 0, &Obj.TxBuf[13]},
  {0x0F, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_0F, 0, &Obj.TxBuf[14]},
  {0x10, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_10, 0, &Obj.TxBuf[15]},
  {0x11, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_11, 0, &Obj.TxBuf[16]},
  {0x12, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_12, 0, &Obj.TxBuf[17]},
  {0x13, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_13, 0, &Obj.TxBuf[18]},
  {0x14, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_14, 0, &Obj.TxBuf[19]},
  {0x15, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_15, 0, &Obj.TxBuf[20]},
  {0x16, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_16, 0, &Obj.TxBuf[21]},
  {0x17, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_17, 0, &Obj.TxBuf[22]},
  {0x18, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_18, 0, &Obj.TxBuf[23]},
  {0x19, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_19, 0, &Obj.TxBuf[24]},
  {0x1A, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_1A, 0, &Obj.TxBuf[25]},
  {0x1B, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_1B, 0, &Obj.TxBuf[26]},
  {0x1C, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_1C, 0, &Obj.TxBuf[27]},
  {0x1D, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_1D, 0, &Obj.TxBuf[28]},
  {0x1E, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_1E, 0, &Obj.TxBuf[29]},
  {0x1F, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_1F, 0, &Obj.TxBuf[30]},
  {0x20, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_20, 0, &Obj.TxBuf[31]},
  {0x21, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_21, 0, &Obj.TxBuf[32]},
  {0x22, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_22, 0, &Obj.TxBuf[33]},
  {0x23, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_23, 0, &Obj.TxBuf[34]},
  {0x24, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_24, 0, &Obj.TxBuf[35]},
  {0x25, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_25, 0, &Obj.TxBuf[36]},
  {0x26, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_26, 0, &Obj.TxBuf[37]},
  {0x27, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_27, 0, &Obj.TxBuf[38]},
  {0x28, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_28, 0, &Obj.TxBuf[39]},
  {0x29, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_29, 0, &Obj.TxBuf[40]},
  {0x2A, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_2A, 0, &Obj.TxBuf[41]},
  {0x2B, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_2B, 0, &Obj.TxBuf[42]},
  {0x2C, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_2C, 0, &Obj.TxBuf[43]},
  {0x2D, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_2D, 0, &Obj.TxBuf[44]},
  {0x2E, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_2E, 0, &Obj.TxBuf[45]},
  {0x2F, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_2F, 0, &Obj.TxBuf[46]},
  {0x30, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_TXPDO, acName6009_30, 0, &Obj.TxBuf[47]},
};
const _objd SDO7000[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7000_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7000_01, 0, &Obj.Motor1_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7000_02, 0, &Obj.Motor1_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7000_03, 0x00000000, &Obj.Motor1_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7000_04, 0x00000000, &Obj.Motor1_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7000_05, 0x00000000, &Obj.Motor1_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7000_06, 0x00000000, &Obj.Motor1_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7000_07, 0x00000000, &Obj.Motor1_Set.SetCurrentLimit},
};
const _objd SDO7001[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7001_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7001_01, 0, &Obj.Motor2_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7001_02, 0, &Obj.Motor2_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7001_03, 0x00000000, &Obj.Motor2_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7001_04, 0x00000000, &Obj.Motor2_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7001_05, 0x00000000, &Obj.Motor2_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7001_06, 0x00000000, &Obj.Motor2_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7001_07, 0x00000000, &Obj.Motor2_Set.SetCurrentLimit},
};
const _objd SDO7002[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7002_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7002_01, 0, &Obj.Motor3_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7002_02, 0, &Obj.Motor3_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7002_03, 0x00000000, &Obj.Motor3_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7002_04, 0x00000000, &Obj.Motor3_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7002_05, 0x00000000, &Obj.Motor3_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7002_06, 0x00000000, &Obj.Motor3_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7002_07, 0x00000000, &Obj.Motor3_Set.SetCurrentLimit},
};
const _objd SDO7003[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7003_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7003_01, 0, &Obj.Motor4_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7003_02, 0, &Obj.Motor4_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7003_03, 0x00000000, &Obj.Motor4_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7003_04, 0x00000000, &Obj.Motor4_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7003_05, 0x00000000, &Obj.Motor4_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7003_06, 0x00000000, &Obj.Motor4_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7003_07, 0x00000000, &Obj.Motor4_Set.SetCurrentLimit},
};
const _objd SDO7004[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7004_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7004_01, 0, &Obj.Motor5_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7004_02, 0, &Obj.Motor5_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7004_03, 0x00000000, &Obj.Motor5_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7004_04, 0x00000000, &Obj.Motor5_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7004_05, 0x00000000, &Obj.Motor5_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7004_06, 0x00000000, &Obj.Motor5_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7004_07, 0x00000000, &Obj.Motor5_Set.SetCurrentLimit},
};
const _objd SDO7005[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7005_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7005_01, 0, &Obj.Motor6_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7005_02, 0, &Obj.Motor6_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7005_03, 0x00000000, &Obj.Motor6_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7005_04, 0x00000000, &Obj.Motor6_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7005_05, 0x00000000, &Obj.Motor6_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7005_06, 0x00000000, &Obj.Motor6_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7005_07, 0x00000000, &Obj.Motor6_Set.SetCurrentLimit},
};
const _objd SDO7006[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7006_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7006_01, 0, &Obj.Motor7_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7006_02, 0, &Obj.Motor7_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7006_03, 0x00000000, &Obj.Motor7_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7006_04, 0x00000000, &Obj.Motor7_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7006_05, 0x00000000, &Obj.Motor7_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7006_06, 0x00000000, &Obj.Motor7_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7006_07, 0x00000000, &Obj.Motor7_Set.SetCurrentLimit},
};
const _objd SDO7007[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7007_00, 7, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7007_01, 0, &Obj.Motor8_Set.Enable},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7007_02, 0, &Obj.Motor8_Set.Mode},
  {0x03, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7007_03, 0x00000000, &Obj.Motor8_Set.IqSet},
  {0x04, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7007_04, 0x00000000, &Obj.Motor8_Set.SetSpeed},
  {0x05, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7007_05, 0x00000000, &Obj.Motor8_Set.SetRawAngle},
  {0x06, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7007_06, 0x00000000, &Obj.Motor8_Set.SetTrajectoryAngle},
  {0x07, DTYPE_REAL32, 32, ATYPE_RO | ATYPE_RXPDO, acName7007_07, 0x00000000, &Obj.Motor8_Set.SetCurrentLimit},
};
const _objd SDO7008[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, acName7008_00, 48, NULL},
  {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_01, 0, &Obj.RxBuf[0]},
  {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_02, 0, &Obj.RxBuf[1]},
  {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_03, 0, &Obj.RxBuf[2]},
  {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_04, 0, &Obj.RxBuf[3]},
  {0x05, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_05, 0, &Obj.RxBuf[4]},
  {0x06, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_06, 0, &Obj.RxBuf[5]},
  {0x07, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_07, 0, &Obj.RxBuf[6]},
  {0x08, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_08, 0, &Obj.RxBuf[7]},
  {0x09, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_09, 0, &Obj.RxBuf[8]},
  {0x0A, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_0A, 0, &Obj.RxBuf[9]},
  {0x0B, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_0B, 0, &Obj.RxBuf[10]},
  {0x0C, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_0C, 0, &Obj.RxBuf[11]},
  {0x0D, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_0D, 0, &Obj.RxBuf[12]},
  {0x0E, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_0E, 0, &Obj.RxBuf[13]},
  {0x0F, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_0F, 0, &Obj.RxBuf[14]},
  {0x10, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_10, 0, &Obj.RxBuf[15]},
  {0x11, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_11, 0, &Obj.RxBuf[16]},
  {0x12, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_12, 0, &Obj.RxBuf[17]},
  {0x13, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_13, 0, &Obj.RxBuf[18]},
  {0x14, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_14, 0, &Obj.RxBuf[19]},
  {0x15, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_15, 0, &Obj.RxBuf[20]},
  {0x16, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_16, 0, &Obj.RxBuf[21]},
  {0x17, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_17, 0, &Obj.RxBuf[22]},
  {0x18, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_18, 0, &Obj.RxBuf[23]},
  {0x19, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_19, 0, &Obj.RxBuf[24]},
  {0x1A, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_1A, 0, &Obj.RxBuf[25]},
  {0x1B, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_1B, 0, &Obj.RxBuf[26]},
  {0x1C, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_1C, 0, &Obj.RxBuf[27]},
  {0x1D, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_1D, 0, &Obj.RxBuf[28]},
  {0x1E, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_1E, 0, &Obj.RxBuf[29]},
  {0x1F, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_1F, 0, &Obj.RxBuf[30]},
  {0x20, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_20, 0, &Obj.RxBuf[31]},
  {0x21, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_21, 0, &Obj.RxBuf[32]},
  {0x22, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_22, 0, &Obj.RxBuf[33]},
  {0x23, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_23, 0, &Obj.RxBuf[34]},
  {0x24, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_24, 0, &Obj.RxBuf[35]},
  {0x25, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_25, 0, &Obj.RxBuf[36]},
  {0x26, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_26, 0, &Obj.RxBuf[37]},
  {0x27, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_27, 0, &Obj.RxBuf[38]},
  {0x28, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_28, 0, &Obj.RxBuf[39]},
  {0x29, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_29, 0, &Obj.RxBuf[40]},
  {0x2A, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_2A, 0, &Obj.RxBuf[41]},
  {0x2B, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_2B, 0, &Obj.RxBuf[42]},
  {0x2C, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_2C, 0, &Obj.RxBuf[43]},
  {0x2D, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_2D, 0, &Obj.RxBuf[44]},
  {0x2E, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_2E, 0, &Obj.RxBuf[45]},
  {0x2F, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_2F, 0, &Obj.RxBuf[46]},
  {0x30, DTYPE_UNSIGNED8, 8, ATYPE_RO | ATYPE_RXPDO, acName7008_30, 0, &Obj.RxBuf[47]},
};

const _objectlist SDOobjects[] =
{
  {0x1000, OTYPE_VAR, 0, 0, acName1000, SDO1000},
  {0x1008, OTYPE_VAR, 0, 0, acName1008, SDO1008},
  {0x1009, OTYPE_VAR, 0, 0, acName1009, SDO1009},
  {0x100A, OTYPE_VAR, 0, 0, acName100A, SDO100A},
  {0x1018, OTYPE_RECORD, 4, 0, acName1018, SDO1018},
  {0x1600, OTYPE_RECORD, 7, 0, acName1600, SDO1600},
  {0x1601, OTYPE_RECORD, 7, 0, acName1601, SDO1601},
  {0x1602, OTYPE_RECORD, 7, 0, acName1602, SDO1602},
  {0x1603, OTYPE_RECORD, 7, 0, acName1603, SDO1603},
  {0x1604, OTYPE_RECORD, 7, 0, acName1604, SDO1604},
  {0x1605, OTYPE_RECORD, 7, 0, acName1605, SDO1605},
  {0x1606, OTYPE_RECORD, 7, 0, acName1606, SDO1606},
  {0x1607, OTYPE_RECORD, 7, 0, acName1607, SDO1607},
  {0x1608, OTYPE_RECORD, 48, 0, acName1608, SDO1608},
  {0x1A00, OTYPE_RECORD, 5, 0, acName1A00, SDO1A00},
  {0x1A01, OTYPE_RECORD, 16, 0, acName1A01, SDO1A01},
  {0x1A02, OTYPE_RECORD, 16, 0, acName1A02, SDO1A02},
  {0x1A03, OTYPE_RECORD, 16, 0, acName1A03, SDO1A03},
  {0x1A04, OTYPE_RECORD, 16, 0, acName1A04, SDO1A04},
  {0x1A05, OTYPE_RECORD, 16, 0, acName1A05, SDO1A05},
  {0x1A06, OTYPE_RECORD, 16, 0, acName1A06, SDO1A06},
  {0x1A07, OTYPE_RECORD, 16, 0, acName1A07, SDO1A07},
  {0x1A08, OTYPE_RECORD, 16, 0, acName1A08, SDO1A08},
  {0x1A09, OTYPE_RECORD, 48, 0, acName1A09, SDO1A09},
  {0x1C00, OTYPE_ARRAY, 4, 0, acName1C00, SDO1C00},
  {0x1C12, OTYPE_ARRAY, 9, 0, acName1C12, SDO1C12},
  {0x1C13, OTYPE_ARRAY, 10, 0, acName1C13, SDO1C13},
  {0x6000, OTYPE_RECORD, 5, 0, acName6000, SDO6000},
  {0x6001, OTYPE_RECORD, 16, 0, acName6001, SDO6001},
  {0x6002, OTYPE_RECORD, 16, 0, acName6002, SDO6002},
  {0x6003, OTYPE_RECORD, 16, 0, acName6003, SDO6003},
  {0x6004, OTYPE_RECORD, 16, 0, acName6004, SDO6004},
  {0x6005, OTYPE_RECORD, 16, 0, acName6005, SDO6005},
  {0x6006, OTYPE_RECORD, 16, 0, acName6006, SDO6006},
  {0x6007, OTYPE_RECORD, 16, 0, acName6007, SDO6007},
  {0x6008, OTYPE_RECORD, 16, 0, acName6008, SDO6008},
  {0x6009, OTYPE_ARRAY, 48, 0, acName6009, SDO6009},
  {0x7000, OTYPE_RECORD, 7, 0, acName7000, SDO7000},
  {0x7001, OTYPE_RECORD, 7, 0, acName7001, SDO7001},
  {0x7002, OTYPE_RECORD, 7, 0, acName7002, SDO7002},
  {0x7003, OTYPE_RECORD, 7, 0, acName7003, SDO7003},
  {0x7004, OTYPE_RECORD, 7, 0, acName7004, SDO7004},
  {0x7005, OTYPE_RECORD, 7, 0, acName7005, SDO7005},
  {0x7006, OTYPE_RECORD, 7, 0, acName7006, SDO7006},
  {0x7007, OTYPE_RECORD, 7, 0, acName7007, SDO7007},
  {0x7008, OTYPE_ARRAY, 48, 0, acName7008, SDO7008},
  {0xffff, 0xff, 0xff, 0xff, NULL, NULL}
};
