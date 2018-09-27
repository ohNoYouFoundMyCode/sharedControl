#include "__cf_robertoWRosTestedIssues.h"
#ifndef RTW_HEADER_robertoWRosTestedIssues_acc_h_
#define RTW_HEADER_robertoWRosTestedIssues_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef robertoWRosTestedIssues_acc_COMMON_INCLUDES_
#define robertoWRosTestedIssues_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "robertoWRosTestedIssues_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_defines.h"
typedef struct { SL_Bus_robertoWRosTestedIssues_Usv16ActuatorInputs_3cvjf5
B_7_16_0 ; SL_Bus_robertoWRosTestedIssues_Usv16ActuatorInputs_3cvjf5 B_7_62_0
; real_T B_7_0_0 ; real_T B_7_1_0 ; real_T B_7_2_0 ; real_T B_7_3_0 ; real_T
B_7_4_0 ; real_T B_7_5_0 ; real_T B_7_6_0 ; real_T B_7_7_0 ; real_T B_7_8_0 ;
real_T B_7_9_0 ; real_T B_7_10_0 ; real_T B_7_11_0 ; real_T B_7_12_0 ; real_T
B_7_13_0 ; real_T B_7_14_0 ; real_T B_7_19_0 ; real_T B_7_21_0 ; real_T
B_7_23_0 ; real_T B_7_25_0 ; real_T B_7_26_0 ; real_T B_7_27_0 ; real_T
B_7_28_0 ; real_T B_7_29_0 ; real_T B_7_30_0 ; real_T B_7_31_0 ; real_T
B_7_33_0 ; real_T B_7_34_0 ; real_T B_7_35_0 ; real_T B_7_36_0 ; real_T
B_7_37_0 ; real_T B_7_38_0 ; real_T B_7_39_0 ; real_T B_7_41_0 ; real_T
B_7_42_0 ; real_T B_7_43_0 ; real_T B_7_44_0 ; real_T B_7_45_0 ; real_T
B_7_48_0 ; real_T B_7_50_0 ; real_T B_7_52_0 [ 2 ] ; real_T B_7_53_0 ; real_T
B_7_54_0 ; real_T B_7_55_0 ; real_T B_7_56_0 ; real_T B_7_57_0 ; real_T
B_7_58_0 ; real_T B_7_59_0 ; real_T B_7_60_0 ; real_T B_7_61_0 ; real_T
B_7_71_0 ; real_T B_7_74_0 ; real_T B_7_75_0 ; real_T B_7_76_0 ; real_T
B_7_77_0 ; real_T B_7_78_0 ; real_T B_7_79_0 ; real_T B_4_0_0 ; real_T
B_4_1_0 ; real_T B_4_3_0 ; real_T B_3_1_0 [ 2 ] ; real_T B_2_0_0 [ 2 ] ;
real_T B_7_20_0 [ 8 ] ; boolean_T B_7_20_1 [ 13 ] ; char_T pad_B_7_20_1 [ 3 ]
; } B_robertoWRosTestedIssues_T ; typedef struct { real_T
Memory2_PreviousInput ; real_T Memory4_PreviousInput ; real_T
Memory5_PreviousInput ; real_T TimeStampA ; real_T LastUAtTimeA ; real_T
TimeStampB ; real_T LastUAtTimeB ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay_RWORK_g
; void * JoystickInput2_PWORK ; void * Scope5_PWORK ; void * Scope6_PWORK ;
void * Scope7_PWORK [ 2 ] ; void * error_PWORK ; void * yvy_ref_PWORK [ 2 ] ;
void * Scope_PWORK ; void * Scope_PWORK_l ; void * Scope_PWORK_d [ 2 ] ; void
* Scope1_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK
; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_i ; int32_T
Publish2_sysIdxToRun ; int32_T SinkBlock_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtKw_dasdelta2K00Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAty_dot0Inport3_sysIdxToRun ; int_T JoystickInput2_IWORK [ 14
] ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_j ; int_T Saturation5_MODE ; int_T Saturation4_MODE ;
int_T Saturation6_MODE ; boolean_T c_Mode ; boolean_T c2_Mode ; boolean_T
das_Mode ; boolean_T InitialYd1_FirstOutputTime ; boolean_T
Initialt_last_lane_change1_FirstOutputTime ; boolean_T Switch_Mode ;
boolean_T InitialYdot1_FirstOutputTime ; boolean_T Switch_Mode_o ; }
DW_robertoWRosTestedIssues_T ; typedef struct { real_T Integrator_CSTATE ;
real_T Integrator1_CSTATE ; real_T Integrator_CSTATE_p ; real_T
Integrator1_CSTATE_o ; real_T USV1_CSTATE [ 3 ] ; real_T DsLead1_CSTATE ; }
X_robertoWRosTestedIssues_T ; typedef struct { real_T Integrator_CSTATE ;
real_T Integrator1_CSTATE ; real_T Integrator_CSTATE_p ; real_T
Integrator1_CSTATE_o ; real_T USV1_CSTATE [ 3 ] ; real_T DsLead1_CSTATE ; }
XDot_robertoWRosTestedIssues_T ; typedef struct { boolean_T Integrator_CSTATE
; boolean_T Integrator1_CSTATE ; boolean_T Integrator_CSTATE_p ; boolean_T
Integrator1_CSTATE_o ; boolean_T USV1_CSTATE [ 3 ] ; boolean_T DsLead1_CSTATE
; } XDis_robertoWRosTestedIssues_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator1_CSTATE ; real_T Integrator_CSTATE_p ;
real_T Integrator1_CSTATE_o ; real_T USV1_CSTATE [ 3 ] ; real_T
DsLead1_CSTATE ; } CStateAbsTol_robertoWRosTestedIssues_T ; typedef struct {
real_T c_SwitchCond_ZC ; real_T c2_SwitchCond_ZC ; real_T das_SwitchCond_ZC ;
real_T Switch_SwitchCond_ZC ; real_T Switch_SwitchCond_ZC_k ; real_T
Saturation5_UprLim_ZC ; real_T Saturation5_LwrLim_ZC ; real_T
Saturation4_UprLim_ZC ; real_T Saturation4_LwrLim_ZC ; real_T
Saturation6_UprLim_ZC ; real_T Saturation6_LwrLim_ZC ; }
ZCV_robertoWRosTestedIssues_T ; typedef struct { ZCSigState c_SwitchCond_ZCE
; ZCSigState c2_SwitchCond_ZCE ; ZCSigState das_SwitchCond_ZCE ; ZCSigState
Switch_SwitchCond_ZCE ; ZCSigState Switch_SwitchCond_ZCE_f ; ZCSigState
Saturation5_UprLim_ZCE ; ZCSigState Saturation5_LwrLim_ZCE ; ZCSigState
Saturation4_UprLim_ZCE ; ZCSigState Saturation4_LwrLim_ZCE ; ZCSigState
Saturation6_UprLim_ZCE ; ZCSigState Saturation6_LwrLim_ZCE ; }
PrevZCX_robertoWRosTestedIssues_T ; struct P_robertoWRosTestedIssues_T_ {
SL_Bus_robertoWRosTestedIssues_Usv16ActuatorInputs_3cvjf5 P_0 ; real_T P_1 ;
real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ;
real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T
P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 [ 2 ] ; real_T
P_18 ; real_T P_19 [ 2 ] ; real_T P_20 ; real_T P_21 [ 2 ] ; real_T P_22 ;
real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T
P_28 ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ;
real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T
P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ;
real_T P_45 ; real_T P_46 [ 3 ] ; real_T P_47 ; real_T P_48 ; real_T P_49 ;
real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T
P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ; real_T P_60 ;
real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; } ;
extern P_robertoWRosTestedIssues_T robertoWRosTestedIssues_rtDefaultP ;
#endif
