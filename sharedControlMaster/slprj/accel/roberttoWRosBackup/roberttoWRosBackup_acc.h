#include "__cf_roberttoWRosBackup.h"
#ifndef RTW_HEADER_roberttoWRosBackup_acc_h_
#define RTW_HEADER_roberttoWRosBackup_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef roberttoWRosBackup_acc_COMMON_INCLUDES_
#define roberttoWRosBackup_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "roberttoWRosBackup_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16State B_9_0_0 ;
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16State B_8_0_0 ;
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16State B_7_0_1 ;
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16ActuatorInputs B_10_0_0 ;
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16ActuatorInputs B_10_59_0 ; real_T
B_10_3_0 ; real_T B_10_5_0 ; real_T B_10_7_0 ; real_T B_10_9_0 ; real_T
B_10_10_0 ; real_T B_10_11_0 ; real_T B_10_12_0 ; real_T B_10_13_0 ; real_T
B_10_14_0 ; real_T B_10_15_0 ; real_T B_10_16_0 ; real_T B_10_17_0 ; real_T
B_10_18_0 ; real_T B_10_19_0 ; real_T B_10_20_0 ; real_T B_10_21_0 ; real_T
B_10_22_0 ; real_T B_10_23_0 ; real_T B_10_24_0 ; real_T B_10_25_0 ; real_T
B_10_26_0 ; real_T B_10_27_0 ; real_T B_10_28_0 ; real_T B_10_29_0 ; real_T
B_10_30_0 ; real_T B_10_32_0 ; real_T B_10_33_0 ; real_T B_10_34_0 ; real_T
B_10_35_0 ; real_T B_10_36_0 ; real_T B_10_37_0 ; real_T B_10_39_0 ; real_T
B_10_40_0 ; real_T B_10_41_0 ; real_T B_10_42_0 ; real_T B_10_45_0 ; real_T
B_10_47_0 ; real_T B_10_49_0 [ 2 ] ; real_T B_10_50_0 ; real_T B_10_51_0 ;
real_T B_10_52_0 ; real_T B_10_53_0 ; real_T B_10_54_0 ; real_T B_10_55_0 ;
real_T B_10_56_0 ; real_T B_10_57_0 ; real_T B_10_64_0 ; real_T B_10_65_0 ;
real_T B_10_66_0 ; real_T B_10_67_0 ; real_T B_4_0_0 ; real_T B_4_1_0 ;
real_T B_4_3_0 ; real_T B_3_0_0 ; real_T B_3_2_0 [ 2 ] ; real_T B_2_0_0 [ 2 ]
; real_T B_10_4_0 [ 8 ] ; boolean_T B_10_4_1 [ 13 ] ; boolean_T B_7_0_0 ;
char_T pad_B_7_0_0 [ 2 ] ; } B_roberttoWRosBackup_T ; typedef struct { real_T
Memory_PreviousInput ; real_T Memory1_PreviousInput ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_l ; void * JoystickInput1_PWORK ; void * Scope_PWORK [ 2
] ; void * Scope1_PWORK [ 3 ] ; void * Scope_PWORK_o [ 2 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay_PWORK_g ; int32_T Subscribe_sysIdxToRun ; int32_T
EnabledSubsystem_sysIdxToRun ; int32_T SourceBlock_sysIdxToRun ; int32_T
Publish1_sysIdxToRun ; int32_T SinkBlock_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtKw_dasdelta2K00Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport3_sysIdxToRun ; int_T JoystickInput1_IWORK [ 14
] ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_o ; int_T Saturation2_MODE ; int_T Saturation1_MODE ;
int_T Saturation3_MODE ; int8_T EnabledSubsystem_SubsysRanBC ; boolean_T
InitialYd_FirstOutputTime ; boolean_T
Initialt_last_lane_change_FirstOutputTime ; boolean_T c_Mode ; boolean_T
c2_Mode ; boolean_T das_Mode ; boolean_T Switch_Mode ; boolean_T
Switch_Mode_c ; char_T pad_Switch_Mode_c [ 4 ] ; } DW_roberttoWRosBackup_T ;
typedef struct { real_T Integrator_CSTATE ; real_T Integrator1_CSTATE ;
real_T Integrator_CSTATE_c ; real_T Integrator1_CSTATE_g ; real_T
DsLead_CSTATE ; } X_roberttoWRosBackup_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator1_CSTATE ; real_T Integrator_CSTATE_c ;
real_T Integrator1_CSTATE_g ; real_T DsLead_CSTATE ; }
XDot_roberttoWRosBackup_T ; typedef struct { boolean_T Integrator_CSTATE ;
boolean_T Integrator1_CSTATE ; boolean_T Integrator_CSTATE_c ; boolean_T
Integrator1_CSTATE_g ; boolean_T DsLead_CSTATE ; } XDis_roberttoWRosBackup_T
; typedef struct { real_T Integrator_CSTATE ; real_T Integrator1_CSTATE ;
real_T Integrator_CSTATE_c ; real_T Integrator1_CSTATE_g ; real_T
DsLead_CSTATE ; } CStateAbsTol_roberttoWRosBackup_T ; typedef struct { real_T
c_SwitchCond_ZC ; real_T c2_SwitchCond_ZC ; real_T das_SwitchCond_ZC ; real_T
Switch_SwitchCond_ZC ; real_T Switch_SwitchCond_ZC_j ; real_T
Saturation2_UprLim_ZC ; real_T Saturation2_LwrLim_ZC ; real_T
Saturation1_UprLim_ZC ; real_T Saturation1_LwrLim_ZC ; real_T
Saturation3_UprLim_ZC ; real_T Saturation3_LwrLim_ZC ; }
ZCV_roberttoWRosBackup_T ; typedef struct { ZCSigState c_SwitchCond_ZCE ;
ZCSigState c2_SwitchCond_ZCE ; ZCSigState das_SwitchCond_ZCE ; ZCSigState
Switch_SwitchCond_ZCE ; ZCSigState Switch_SwitchCond_ZCE_c ; ZCSigState
Saturation2_UprLim_ZCE ; ZCSigState Saturation2_LwrLim_ZCE ; ZCSigState
Saturation1_UprLim_ZCE ; ZCSigState Saturation1_LwrLim_ZCE ; ZCSigState
Saturation3_UprLim_ZCE ; ZCSigState Saturation3_LwrLim_ZCE ; }
PrevZCX_roberttoWRosBackup_T ; struct P_roberttoWRosBackup_T_ {
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16State P_0 ;
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16State P_1 ;
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16ActuatorInputs P_2 ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 [ 2 ] ; real_T P_7 ; real_T P_8 [ 2 ] ;
real_T P_9 ; real_T P_10 [ 2 ] ; real_T P_11 ; real_T P_12 ; real_T P_13 ;
real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T
P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ;
real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T
P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ;
real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T
P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ;
real_T P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T
P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ;
real_T P_58 ; real_T P_59 ; real_T P_60 ; } ; extern P_roberttoWRosBackup_T
roberttoWRosBackup_rtDefaultP ;
#endif
