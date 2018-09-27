#include "__cf_testerWSimFeedbackLAG.h"
#ifndef RTW_HEADER_testerWSimFeedbackLAG_acc_h_
#define RTW_HEADER_testerWSimFeedbackLAG_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef testerWSimFeedbackLAG_acc_COMMON_INCLUDES_
#define testerWSimFeedbackLAG_acc_COMMON_INCLUDES_
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
#include "testerWSimFeedbackLAG_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { SL_Bus_testerWSimFeedbackLAG_usv16_msgs_Usv16ActuatorInputs
B_9_58_0 ; SL_Bus_testerWSimFeedbackLAG_usv16_msgs_Usv16ActuatorInputs
B_9_66_0 ; real_T B_9_0_0 ; real_T B_9_1_0 ; real_T B_9_2_0 ; real_T B_9_4_0
; real_T B_9_5_0 ; real_T B_9_6_0 ; real_T B_9_7_0 ; real_T B_9_8_0 ; real_T
B_9_10_0 ; real_T B_9_11_0 ; real_T B_9_15_0 ; real_T B_9_16_0 ; real_T
B_9_17_0 ; real_T B_9_20_0 ; real_T B_9_24_0 ; real_T B_9_26_0 ; real_T
B_9_27_0 ; real_T B_9_28_0 ; real_T B_9_29_0 ; real_T B_9_31_0 ; real_T
B_9_32_0 ; real_T B_9_35_0 ; real_T B_9_36_0 ; real_T B_9_37_0 ; real_T
B_9_38_0 ; real_T B_9_39_0 ; real_T B_9_40_0 ; real_T B_9_42_0 ; real_T
B_9_43_0 ; real_T B_9_44_0 ; real_T B_9_45_0 ; real_T B_9_46_0 ; real_T
B_9_49_0 ; real_T B_9_53_0 [ 2 ] ; real_T B_9_56_0 ; real_T B_9_60_0 ; real_T
B_9_62_0 ; real_T B_9_64_0 ; real_T B_9_76_0 ; real_T B_9_77_0 ; real_T
B_9_3_0 [ 6 ] ; boolean_T B_9_3_1 [ 12 ] ; char_T pad_B_9_3_1 [ 4 ] ; }
B_testerWSimFeedbackLAG_T ; typedef struct { real_T
DiscreteTimeIntegrator_DSTATE ; real_T DiscreteTimeIntegrator1_DSTATE ;
real_T DiscreteTimeIntegrator_DSTATE_g ; real_T
DiscreteTimeIntegrator1_DSTATE_i ; real_T TimeStampA ; real_T LastUAtTimeA ;
real_T TimeStampB ; real_T LastUAtTimeB ; real_T Memory_PreviousInput ;
real_T Memory1_PreviousInput ; real_T Memory3_PreviousInput ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_p ; void * JoystickInput1_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * AQHandles ;
void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK ; void *
Scope_PWORK ; void * Scope1_PWORK ; void * Scope2_PWORK ; void * Scope3_PWORK
[ 2 ] ; void * Scope4_PWORK ; void * yvy_ref_PWORK [ 2 ] ; void *
Scope_PWORK_j ; void * w_cvsw_das_PWORK [ 2 ] ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay_PWORK_h ; int32_T Publish2_sysIdxToRun ; int32_T
SinkBlock_sysIdxToRun ; int32_T TmpAtomicSubsysAtdasInport1_sysIdxToRun ;
int32_T TmpAtomicSubsysAtdasInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtKw_dasdelta2K00Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport3_sysIdxToRun ; int_T JoystickInput1_IWORK [ 14
] ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_l ; boolean_T InitialYd_FirstOutputTime ; boolean_T
Initialt_last_lane_change_FirstOutputTime ; boolean_T
InitialYdot_FirstOutputTime ; char_T pad_InitialYdot_FirstOutputTime [ 1 ] ;
} DW_testerWSimFeedbackLAG_T ; typedef struct { real_T ZeroPole_CSTATE [ 3 ]
; real_T DsLead_CSTATE ; } X_testerWSimFeedbackLAG_T ; typedef struct {
real_T ZeroPole_CSTATE [ 3 ] ; real_T DsLead_CSTATE ; }
XDot_testerWSimFeedbackLAG_T ; typedef struct { boolean_T ZeroPole_CSTATE [ 3
] ; boolean_T DsLead_CSTATE ; } XDis_testerWSimFeedbackLAG_T ; struct
P_testerWSimFeedbackLAG_T_ {
SL_Bus_testerWSimFeedbackLAG_usv16_msgs_Usv16ActuatorInputs P_0 ; real_T P_1
; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 [ 3 ] ; real_T P_6 ;
real_T P_7 ; real_T P_8 [ 2 ] ; real_T P_9 ; real_T P_10 [ 2 ] ; real_T P_11
; real_T P_12 [ 2 ] ; real_T P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ;
real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T
P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ;
real_T P_28 ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T
P_33 ; real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ;
real_T P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T P_43 ; real_T
P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T P_49 ;
real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T
P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ; real_T P_60 ;
real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; real_T
P_66 ; } ; extern P_testerWSimFeedbackLAG_T testerWSimFeedbackLAG_rtDefaultP
;
#endif
