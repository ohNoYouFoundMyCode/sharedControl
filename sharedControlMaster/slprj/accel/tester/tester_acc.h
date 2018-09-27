#include "__cf_tester.h"
#ifndef RTW_HEADER_tester_acc_h_
#define RTW_HEADER_tester_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef tester_acc_COMMON_INCLUDES_
#define tester_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "tester_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { SL_Bus_tester_usv16_msgs_Usv16State B_11_0_0 ;
SL_Bus_tester_usv16_msgs_Usv16State B_10_0_0 ;
SL_Bus_tester_usv16_msgs_Usv16State B_9_0_1 ;
SL_Bus_tester_usv16_msgs_Usv16ActuatorInputs B_12_59_0 ;
SL_Bus_tester_usv16_msgs_Usv16ActuatorInputs B_12_64_0 ; real_T B_12_0_0 ;
real_T B_12_2_0 ; real_T B_12_3_0 ; real_T B_12_5_0 ; real_T B_12_6_0 ;
real_T B_12_7_0 ; real_T B_12_8_0 ; real_T B_12_9_0 ; real_T B_12_11_0 ;
real_T B_12_12_0 ; real_T B_12_16_0 ; real_T B_12_17_0 ; real_T B_12_18_0 ;
real_T B_12_21_0 ; real_T B_12_25_0 ; real_T B_12_27_0 ; real_T B_12_28_0 ;
real_T B_12_29_0 ; real_T B_12_30_0 ; real_T B_12_32_0 ; real_T B_12_33_0 ;
real_T B_12_36_0 ; real_T B_12_37_0 ; real_T B_12_38_0 ; real_T B_12_39_0 ;
real_T B_12_40_0 ; real_T B_12_41_0 ; real_T B_12_43_0 ; real_T B_12_44_0 ;
real_T B_12_45_0 ; real_T B_12_46_0 ; real_T B_12_47_0 ; real_T B_12_50_0 ;
real_T B_12_54_0 [ 2 ] ; real_T B_12_57_0 ; real_T B_12_61_0 ; real_T
B_12_62_0 ; real_T B_12_71_0 ; real_T B_12_76_0 ; real_T B_12_77_0 ; real_T
B_12_78_0 ; real_T B_12_80_0 ; real_T B_12_86_0 [ 2 ] ; real_T B_12_90_0 ;
real_T B_12_91_0 ; real_T B_12_94_0 ; real_T B_12_4_0 [ 6 ] ; boolean_T
B_12_4_1 [ 12 ] ; boolean_T B_9_0_0 ; char_T pad_B_9_0_0 [ 3 ] ; } B_tester_T
; typedef struct { real_T DiscreteTimeIntegrator_DSTATE ; real_T
DiscreteTimeIntegrator1_DSTATE ; real_T DiscreteTimeIntegrator_DSTATE_b ;
real_T DiscreteTimeIntegrator1_DSTATE_c ; real_T
FilterDifferentiatorTF_states ; real_T Integrator_DSTATE ; real_T TimeStampA
; real_T LastUAtTimeA ; real_T TimeStampB ; real_T LastUAtTimeB ; real_T
Memory_PreviousInput ; real_T Memory1_PreviousInput ; real_T
Memory3_PreviousInput ; real_T FilterDifferentiatorTF_tmp ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_h ; void * JoystickInput1_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * AQHandles ;
void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK ; void *
Scope_PWORK ; void * Scope1_PWORK ; void * Scope2_PWORK ; void * Scope3_PWORK
[ 2 ] ; void * Scope4_PWORK ; void * yvy_ref_PWORK [ 2 ] ; void *
Scope_PWORK_b ; void * w_cvsw_das_PWORK [ 2 ] ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay_PWORK_l ; int32_T Subscribe1_sysIdxToRun ; int32_T
EnabledSubsystem_sysIdxToRun ; int32_T SourceBlock_sysIdxToRun ; int32_T
Publish2_sysIdxToRun ; int32_T SinkBlock_sysIdxToRun ; int32_T
TmpAtomicSubsysAtdasInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtdasInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtKw_dasdelta2K00Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport3_sysIdxToRun ; int_T JoystickInput1_IWORK [ 14
] ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_d ; int8_T EnabledSubsystem_SubsysRanBC ; boolean_T
InitialYd_FirstOutputTime ; boolean_T
Initialt_last_lane_change_FirstOutputTime ; boolean_T
InitialYdot_FirstOutputTime ; char_T pad_InitialYdot_FirstOutputTime [ 4 ] ;
} DW_tester_T ; typedef struct { real_T TransferFcn_CSTATE ; } X_tester_T ;
typedef struct { real_T TransferFcn_CSTATE ; } XDot_tester_T ; typedef struct
{ boolean_T TransferFcn_CSTATE ; } XDis_tester_T ; struct P_tester_T_ {
SL_Bus_tester_usv16_msgs_Usv16State P_0 ; SL_Bus_tester_usv16_msgs_Usv16State
P_1 ; SL_Bus_tester_usv16_msgs_Usv16ActuatorInputs P_2 ; real_T P_3 ; real_T
P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 [ 2 ] ; real_T P_8 ; real_T P_9 [
2 ] ; real_T P_10 ; real_T P_11 [ 2 ] ; real_T P_12 ; real_T P_13 ; real_T
P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ;
real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T
P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T P_30 ;
real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ; real_T
P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T P_41 ;
real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T
P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ;
real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T
P_58 ; real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ;
real_T P_64 ; real_T P_65 ; real_T P_66 [ 2 ] ; real_T P_67 ; real_T P_68 ;
real_T P_69 ; real_T P_70 ; real_T P_71 ; real_T P_72 ; real_T P_73 ; real_T
P_74 ; } ; extern P_tester_T tester_rtDefaultP ;
#endif
