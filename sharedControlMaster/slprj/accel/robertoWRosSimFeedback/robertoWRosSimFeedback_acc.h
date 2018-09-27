#include "__cf_robertoWRosSimFeedback.h"
#ifndef RTW_HEADER_robertoWRosSimFeedback_acc_h_
#define RTW_HEADER_robertoWRosSimFeedback_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef robertoWRosSimFeedback_acc_COMMON_INCLUDES_
#define robertoWRosSimFeedback_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "robertoWRosSimFeedback_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { SL_Bus_robertoWRosSimFeedback_usv16_msgs_Usv16State B_11_0_0
; SL_Bus_robertoWRosSimFeedback_usv16_msgs_Usv16State B_10_0_0 ;
SL_Bus_robertoWRosSimFeedback_usv16_msgs_Usv16State B_9_0_1 ;
SL_Bus_robertoWRosSimFeedback_Usv16ActuatorInputs_mxh9m6 B_12_16_0 ;
SL_Bus_robertoWRosSimFeedback_Usv16ActuatorInputs_mxh9m6 B_12_64_0 ; real_T
B_12_0_0 ; real_T B_12_1_0 ; real_T B_12_2_0 ; real_T B_12_3_0 ; real_T
B_12_4_0 ; real_T B_12_5_0 ; real_T B_12_6_0 ; real_T B_12_7_0 ; real_T
B_12_8_0 ; real_T B_12_9_0 ; real_T B_12_10_0 ; real_T B_12_11_0 ; real_T
B_12_14_0 ; real_T B_12_19_0 ; real_T B_12_21_0 ; real_T B_12_23_0 ; real_T
B_12_25_0 ; real_T B_12_26_0 ; real_T B_12_27_0 ; real_T B_12_28_0 ; real_T
B_12_29_0 ; real_T B_12_30_0 ; real_T B_12_31_0 ; real_T B_12_33_0 ; real_T
B_12_34_0 ; real_T B_12_35_0 ; real_T B_12_36_0 ; real_T B_12_37_0 ; real_T
B_12_38_0 ; real_T B_12_39_0 ; real_T B_12_41_0 ; real_T B_12_42_0 ; real_T
B_12_43_0 ; real_T B_12_44_0 ; real_T B_12_45_0 ; real_T B_12_48_0 ; real_T
B_12_50_0 ; real_T B_12_52_0 [ 2 ] ; real_T B_12_54_0 ; real_T B_12_55_0 ;
real_T B_12_56_0 ; real_T B_12_57_0 ; real_T B_12_58_0 ; real_T B_12_59_0 ;
real_T B_12_60_0 ; real_T B_12_61_0 ; real_T B_12_62_0 ; real_T B_12_63_0 ;
real_T B_12_73_0 ; real_T B_12_76_0 ; real_T B_12_77_0 ; real_T B_12_78_0 ;
real_T B_12_79_0 ; real_T B_6_0_0 ; real_T B_5_0_0 ; real_T B_4_0_0 ; real_T
B_4_1_0 ; real_T B_3_1_0 [ 2 ] ; real_T B_2_0_0 [ 2 ] ; real_T B_12_20_0 [ 8
] ; boolean_T B_12_20_1 [ 13 ] ; boolean_T B_9_0_0 ; char_T pad_B_9_0_0 [ 2 ]
; } B_robertoWRosSimFeedback_T ; typedef struct { real_T
Memory2_PreviousInput ; real_T Memory4_PreviousInput ; real_T
Memory5_PreviousInput ; real_T PrevYA ; real_T PrevYB ; real_T LastMajorTimeA
; real_T LastMajorTimeB ; real_T TimeStampA ; real_T LastUAtTimeA ; real_T
TimeStampB ; real_T LastUAtTimeB ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay_RWORK_g
; void * JoystickInput2_PWORK ; void * Scope5_PWORK ; void * Scope6_PWORK ;
void * Scope7_PWORK [ 2 ] ; void * error_PWORK ; void * yvy_ref_PWORK [ 2 ] ;
void * Scope_PWORK ; void * Scope_PWORK_l ; void * Scope_PWORK_d [ 2 ] ; void
* Scope1_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK
; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_i ; int32_T
Subscribe1_sysIdxToRun ; int32_T EnabledSubsystem_sysIdxToRun ; int32_T
SourceBlock_sysIdxToRun ; int32_T Publish2_sysIdxToRun ; int32_T
SinkBlock_sysIdxToRun ; int32_T TmpAtomicSubsysAtdasInport1_sysIdxToRun ;
int32_T TmpAtomicSubsysAtdasInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtKw_dasdelta2K00Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport3_sysIdxToRun ; int_T JoystickInput2_IWORK [ 14
] ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_j ; int8_T EnabledSubsystem_SubsysRanBC ; boolean_T
InitialYd1_FirstOutputTime ; boolean_T
Initialt_last_lane_change1_FirstOutputTime ; boolean_T
InitialYdot1_FirstOutputTime ; char_T pad_InitialYdot1_FirstOutputTime [ 4 ]
; } DW_robertoWRosSimFeedback_T ; typedef struct { real_T Integrator_CSTATE ;
real_T Integrator1_CSTATE ; real_T Integrator_CSTATE_p ; real_T
Integrator1_CSTATE_o ; real_T DsLead1_CSTATE ; } X_robertoWRosSimFeedback_T ;
typedef struct { real_T Integrator_CSTATE ; real_T Integrator1_CSTATE ;
real_T Integrator_CSTATE_p ; real_T Integrator1_CSTATE_o ; real_T
DsLead1_CSTATE ; } XDot_robertoWRosSimFeedback_T ; typedef struct { boolean_T
Integrator_CSTATE ; boolean_T Integrator1_CSTATE ; boolean_T
Integrator_CSTATE_p ; boolean_T Integrator1_CSTATE_o ; boolean_T
DsLead1_CSTATE ; } XDis_robertoWRosSimFeedback_T ; struct
P_robertoWRosSimFeedback_T_ {
SL_Bus_robertoWRosSimFeedback_usv16_msgs_Usv16State P_0 ;
SL_Bus_robertoWRosSimFeedback_usv16_msgs_Usv16State P_1 ;
SL_Bus_robertoWRosSimFeedback_Usv16ActuatorInputs_mxh9m6 P_2 ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9 ;
real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ; real_T
P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 [ 2 ] ; real_T
P_20 ; real_T P_21 [ 2 ] ; real_T P_22 ; real_T P_23 [ 2 ] ; real_T P_24 ;
real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T
P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ;
real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T
P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ;
real_T P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T
P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ;
real_T P_58 ; real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T
P_63 ; real_T P_64 ; } ; extern P_robertoWRosSimFeedback_T
robertoWRosSimFeedback_rtDefaultP ;
#endif
