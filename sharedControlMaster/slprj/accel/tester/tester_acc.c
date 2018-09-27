#include "__cf_tester.h"
#include <math.h>
#include "tester_acc.h"
#include "tester_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T tester_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T
* tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T *
* tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf ,
boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T
tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * tBufPtr ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail < ( bufSz - 1 ) ) ? (
tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) {
int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ;
real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > *
maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * )
utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL
) ) { return ( false ) ; } tempT = tempU + newBufSz ; if ( istransportdelay )
tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j -
tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay
) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT
[ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ;
if ( istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( *
lastPtr > tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail )
; } * tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr =
newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) *
xBufPtr = tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
tester_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T
* tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay > tStart ) )
return initOutput ; if ( tMinusDelay <= tStart ) return initOutput ; if ( (
tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [
oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx ==
bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ;
u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if (
tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 =
( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 +
f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput ) { if (
newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; } newIdx -- ;
} else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; } newIdx =
bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) { while (
tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < ( bufSz - 1
) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay ) { i = (
i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0
; } * lastIdx = i ; if ( discrete ) { double tempEps = ( DBL_EPSILON ) *
128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf [ i ] ) ; if (
tempEps > localEps ) { localEps = tempEps ; } localEps = localEps / 2.0 ; if
( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout = uBuf [ i ] ; } else {
if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ;
} } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1
] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ;
u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; }
else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 )
; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } } return ( yout ) ; }
void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T
* * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { if ( !
_ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( SimStruct * S , void * diag ) {
_ssReportDiagnosticAsWarning ( S , diag ) ; } static void mdlOutputs (
SimStruct * S , int_T tid ) { real_T * lastU ; real_T rtb_B_12_35_0 ; real_T
rtb_B_12_81_0 ; int32_T isHit ; B_tester_T * _rtB ; P_tester_T * _rtP ;
X_tester_T * _rtX ; DW_tester_T * _rtDW ; _rtDW = ( ( DW_tester_T * )
ssGetRootDWork ( S ) ) ; _rtX = ( ( X_tester_T * ) ssGetContStates ( S ) ) ;
_rtP = ( ( P_tester_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_tester_T * )
_ssGetModelBlockIO ( S ) ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_11_0_0 = _rtP -> P_1 ; ssCallAccelRunBlock ( S , 9 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; if ( _rtB -> B_9_0_0 ) { _rtB -> B_10_0_0 = _rtB ->
B_9_0_1 ; srUpdateBC ( _rtDW -> EnabledSubsystem_SubsysRanBC ) ; } _rtB ->
B_12_2_0 = _rtB -> B_10_0_0 . Pose . X ; } if ( ( _rtDW -> TimeStampA >=
ssGetT ( S ) ) && ( _rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB ->
B_12_3_0 = 0.0 ; } else { rtb_B_12_35_0 = _rtDW -> TimeStampA ; lastU = &
_rtDW -> LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if
( _rtDW -> TimeStampB < ssGetT ( S ) ) { rtb_B_12_35_0 = _rtDW -> TimeStampB
; lastU = & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >=
ssGetT ( S ) ) { rtb_B_12_35_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } _rtB -> B_12_3_0 = ( _rtB -> B_12_2_0 - * lastU ) / (
ssGetT ( S ) - rtb_B_12_35_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { ssCallAccelRunBlock ( S , 12 , 4 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> B_12_5_0 = _rtP -> P_13 * _rtB -> B_12_4_0 [ 3 ] ; } _rtB -> B_12_6_0
= _rtB -> B_12_3_0 * _rtB -> B_12_5_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_12_7_0 = _rtP -> P_14 * _rtB -> B_12_6_0 +
_rtDW -> DiscreteTimeIntegrator_DSTATE ; } { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_16 ;
_rtB -> B_12_8_0 = tester_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_17 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_12_9_0 = _rtP -> P_18 * _rtB -> B_12_8_0 + _rtDW ->
DiscreteTimeIntegrator1_DSTATE ; _rtB -> B_12_11_0 = ( _rtB -> B_12_7_0 -
_rtB -> B_12_9_0 ) * _rtP -> P_20 ; _rtB -> B_12_16_0 = ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_b - _rtDW -> DiscreteTimeIntegrator1_DSTATE_c )
* _rtP -> P_26 ; if ( _rtB -> B_12_16_0 >= _rtP -> P_29 ) { if ( _rtB ->
B_12_11_0 >= _rtP -> P_5 ) { _rtB -> B_12_21_0 = _rtB -> B_12_0_0 ; } else {
_rtB -> B_12_21_0 = _rtB -> B_12_12_0 ; } } else if ( _rtB -> B_12_11_0 >=
_rtP -> P_4 ) { _rtB -> B_12_21_0 = _rtB -> B_12_17_0 ; } else { _rtB ->
B_12_21_0 = _rtB -> B_12_18_0 ; } ssCallAccelRunBlock ( S , 12 , 22 ,
SS_CALL_MDL_OUTPUTS ) ; { if ( ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK . AQHandles ||
_rtDW -> HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK .
SlioLTF ) && ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_12_3_0 ) ; } }
if ( _rtDW -> InitialYd_FirstOutputTime ) { _rtDW ->
InitialYd_FirstOutputTime = false ; _rtB -> B_12_25_0 = _rtP -> P_31 ; } else
{ _rtB -> B_12_25_0 = _rtDW -> Memory_PreviousInput ; } if ( _rtDW ->
Initialt_last_lane_change_FirstOutputTime ) { _rtDW ->
Initialt_last_lane_change_FirstOutputTime = false ; _rtB -> B_12_27_0 = _rtP
-> P_33 ; } else { _rtB -> B_12_27_0 = _rtDW -> Memory1_PreviousInput ; } if
( _rtB -> B_12_21_0 - _rtB -> B_12_30_0 != 0.0 ) { rtb_B_12_35_0 = _rtB ->
B_12_29_0 ; } else { rtb_B_12_35_0 = 1.0 / ( muDoubleScalarExp ( _rtB ->
B_12_33_0 - _rtB -> B_12_16_0 * _rtB -> B_12_32_0 ) + 1.0 ) ; } _rtB ->
B_12_36_0 = _rtP -> P_39 * rtb_B_12_35_0 ; _rtB -> B_12_37_0 = _rtB ->
B_12_36_0 - _rtB -> B_12_28_0 ; if ( _rtDW -> InitialYdot_FirstOutputTime ) {
_rtDW -> InitialYdot_FirstOutputTime = false ; _rtB -> B_12_43_0 = _rtP ->
P_45 ; } else { _rtB -> B_12_43_0 = _rtDW -> Memory3_PreviousInput ; } if (
_rtB -> B_12_43_0 > _rtP -> P_50 ) { _rtB -> B_12_50_0 = ( ( ( _rtB ->
B_12_25_0 + _rtB -> B_12_38_0 ) + _rtB -> B_12_39_0 ) + _rtB -> B_12_40_0 ) +
_rtB -> B_12_41_0 ; } else { _rtB -> B_12_50_0 = ( ( ( _rtB -> B_12_25_0 -
_rtB -> B_12_44_0 ) - _rtB -> B_12_45_0 ) - _rtB -> B_12_46_0 ) - _rtB ->
B_12_47_0 ; } } rtb_B_12_35_0 = ssGetT ( S ) ; if ( rtb_B_12_35_0 - _rtB ->
B_12_27_0 > _rtP -> P_51 ) { if ( _rtB -> B_12_37_0 > _rtP -> P_3 ) { _rtB ->
B_12_54_0 [ 0 ] = _rtB -> B_12_25_0 ; _rtB -> B_12_54_0 [ 1 ] = _rtB ->
B_12_27_0 ; } else if ( _rtB -> B_12_43_0 != 0.0 ) { _rtB -> B_12_54_0 [ 0 ]
= _rtB -> B_12_50_0 ; _rtB -> B_12_54_0 [ 1 ] = rtb_B_12_35_0 ; } else { _rtB
-> B_12_54_0 [ 0 ] = _rtB -> B_12_25_0 ; _rtB -> B_12_54_0 [ 1 ] = _rtB ->
B_12_27_0 ; } } else { _rtB -> B_12_54_0 [ 0 ] = _rtB -> B_12_25_0 ; _rtB ->
B_12_54_0 [ 1 ] = _rtB -> B_12_27_0 ; } rtb_B_12_35_0 = ( _rtB -> B_12_54_0 [
0 ] - _rtB -> B_12_2_0 ) * _rtB -> B_12_36_0 ; if ( rtb_B_12_35_0 > _rtP ->
P_52 ) { _rtB -> B_12_57_0 = _rtP -> P_52 ; } else if ( rtb_B_12_35_0 < _rtP
-> P_53 ) { _rtB -> B_12_57_0 = _rtP -> P_53 ; } else { _rtB -> B_12_57_0 =
rtb_B_12_35_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { {
if ( ( _rtDW -> HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK
. AQHandles || _rtDW ->
HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK . SlioLTF ) &&
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_12_57_0 ) ; }
} _rtB -> B_12_59_0 = _rtP -> P_2 ; } _rtB -> B_12_62_0 = 0.0 ; _rtB ->
B_12_62_0 += _rtP -> P_56 * _rtX -> TransferFcn_CSTATE ; rtb_B_12_35_0 = _rtP
-> P_57 * _rtB -> B_12_62_0 ; _rtB -> B_12_64_0 = _rtB -> B_12_59_0 ; _rtB ->
B_12_64_0 . ActuatorInputs [ 0 ] = _rtB -> B_12_61_0 ; _rtB -> B_12_64_0 .
ActuatorInputs [ 1 ] = rtb_B_12_35_0 ; _rtB -> B_12_64_0 . ActuatorInputs [ 2
] = _rtB -> B_12_61_0 ; _rtB -> B_12_64_0 . ActuatorInputs [ 3 ] =
rtb_B_12_35_0 ; ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 12 , 66 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 67 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 68 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 69 ,
SS_CALL_MDL_OUTPUTS ) ; } rtb_B_12_35_0 = _rtB -> B_12_5_0 + _rtB ->
B_12_57_0 ; if ( rtb_B_12_35_0 > _rtP -> P_58 ) { _rtB -> B_12_71_0 = _rtP ->
P_58 ; } else if ( rtb_B_12_35_0 < _rtP -> P_59 ) { _rtB -> B_12_71_0 = _rtP
-> P_59 ; } else { _rtB -> B_12_71_0 = rtb_B_12_35_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
12 , 72 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 73 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 74 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 75 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_12_76_0 = _rtB -> B_12_3_0 * _rtB ->
B_12_57_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_60 ; _rtB ->
B_12_77_0 = tester_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay_IWORK_d . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_d . Last , _rtDW -> TransportDelay_IWORK_d . Tail ,
_rtDW -> TransportDelay_IWORK_d . Head , _rtP -> P_61 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_12_78_0 = _rtP -> P_62 * _rtB -> B_12_71_0 ; rtb_B_12_81_0 = _rtB ->
B_12_80_0 * _rtP -> P_65 ; rtb_B_12_35_0 = 1.0 / ( _rtP -> P_63 +
rtb_B_12_81_0 ) ; _rtB -> B_12_86_0 [ 0 ] = _rtP -> P_63 ; _rtB -> B_12_86_0
[ 1 ] = ( rtb_B_12_81_0 - _rtP -> P_63 ) * rtb_B_12_35_0 ; _rtDW ->
FilterDifferentiatorTF_tmp = _rtB -> B_12_78_0 - _rtB -> B_12_86_0 [ 1 ] *
_rtDW -> FilterDifferentiatorTF_states ; _rtB -> B_12_90_0 = _rtP -> P_69 *
_rtB -> B_12_71_0 ; _rtB -> B_12_91_0 = _rtP -> P_70 * _rtB -> B_12_90_0 +
_rtDW -> Integrator_DSTATE ; rtb_B_12_35_0 = ( _rtP -> P_66 [ 0 ] * _rtDW ->
FilterDifferentiatorTF_tmp + _rtP -> P_66 [ 1 ] * _rtDW ->
FilterDifferentiatorTF_states ) * rtb_B_12_35_0 * _rtP -> P_68 + ( _rtP ->
P_72 * _rtB -> B_12_71_0 + _rtB -> B_12_91_0 ) ; if ( rtb_B_12_35_0 > _rtP ->
P_73 ) { _rtB -> B_12_94_0 = _rtP -> P_73 ; } else if ( rtb_B_12_35_0 < _rtP
-> P_74 ) { _rtB -> B_12_94_0 = _rtP -> P_74 ; } else { _rtB -> B_12_94_0 =
rtb_B_12_35_0 ; } } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID2 (
SimStruct * S , int_T tid ) { B_tester_T * _rtB ; P_tester_T * _rtP ; _rtP =
( ( P_tester_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_tester_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_12_0_0 = _rtP -> P_6 ; _rtB ->
B_12_12_0 = _rtP -> P_21 ; _rtB -> B_12_17_0 = _rtP -> P_27 ; _rtB ->
B_12_18_0 = _rtP -> P_28 ; _rtB -> B_12_28_0 = _rtP -> P_34 ; _rtB ->
B_12_29_0 = _rtP -> P_35 ; _rtB -> B_12_30_0 = _rtP -> P_36 ; _rtB ->
B_12_32_0 = _rtP -> P_37 ; _rtB -> B_12_33_0 = _rtP -> P_38 ; _rtB ->
B_12_38_0 = _rtP -> P_40 ; _rtB -> B_12_39_0 = _rtP -> P_41 ; _rtB ->
B_12_40_0 = _rtP -> P_42 ; _rtB -> B_12_41_0 = _rtP -> P_43 ; _rtB ->
B_12_44_0 = _rtP -> P_46 ; _rtB -> B_12_45_0 = _rtP -> P_47 ; _rtB ->
B_12_46_0 = _rtP -> P_48 ; _rtB -> B_12_47_0 = _rtP -> P_49 ; _rtB ->
B_12_61_0 = _rtP -> P_54 ; _rtB -> B_12_80_0 = _rtP -> P_64 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_tester_T * _rtB ; P_tester_T * _rtP ; DW_tester_T * _rtDW ;
_rtDW = ( ( DW_tester_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_tester_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_tester_T * ) _ssGetModelBlockIO ( S )
) ; if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA = ssGetT (
S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == (
rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) {
_rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else
{ _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } *
lastU = _rtB -> B_12_2_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { _rtDW -> DiscreteTimeIntegrator_DSTATE = _rtP -> P_14 * _rtB ->
B_12_6_0 + _rtB -> B_12_7_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! tester_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_16 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_12_6_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> DiscreteTimeIntegrator1_DSTATE = _rtP -> P_18 * _rtB -> B_12_8_0 + _rtB ->
B_12_9_0 ; _rtDW -> DiscreteTimeIntegrator_DSTATE_b += _rtP -> P_22 * _rtB ->
B_12_76_0 ; _rtDW -> DiscreteTimeIntegrator1_DSTATE_c += _rtP -> P_24 * _rtB
-> B_12_77_0 ; _rtDW -> Memory_PreviousInput = _rtB -> B_12_54_0 [ 0 ] ;
_rtDW -> Memory1_PreviousInput = _rtB -> B_12_54_0 [ 1 ] ; _rtDW ->
Memory3_PreviousInput = _rtB -> B_12_3_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; boolean_T bufferisfull = false ; _rtDW ->
TransportDelay_IWORK_d . Head = ( ( _rtDW -> TransportDelay_IWORK_d . Head <
( _rtDW -> TransportDelay_IWORK_d . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_d . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_d . Head == _rtDW -> TransportDelay_IWORK_d . Tail ) {
bufferisfull = true ; if ( ! tester_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> TransportDelay_IWORK_d . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_d . Tail , & _rtDW -> TransportDelay_IWORK_d . Head , &
_rtDW -> TransportDelay_IWORK_d . Last , simTime - _rtP -> P_60 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 1 , false , & _rtDW ->
TransportDelay_IWORK_d . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_d . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_d . Head ] = _rtB -> B_12_76_0 ; if ( bufferisfull ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
FilterDifferentiatorTF_states = _rtDW -> FilterDifferentiatorTF_tmp ; _rtDW
-> Integrator_DSTATE = _rtP -> P_70 * _rtB -> B_12_90_0 + _rtB -> B_12_91_0 ;
} UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_tester_T * _rtB ; P_tester_T
* _rtP ; X_tester_T * _rtX ; XDot_tester_T * _rtXdot ; _rtXdot = ( (
XDot_tester_T * ) ssGetdX ( S ) ) ; _rtX = ( ( X_tester_T * ) ssGetContStates
( S ) ) ; _rtP = ( ( P_tester_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_tester_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot -> TransferFcn_CSTATE =
0.0 ; _rtXdot -> TransferFcn_CSTATE += _rtP -> P_55 * _rtX ->
TransferFcn_CSTATE ; _rtXdot -> TransferFcn_CSTATE += _rtB -> B_12_94_0 ; }
static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
4019845612U ) ; ssSetChecksumVal ( S , 1 , 3931188127U ) ; ssSetChecksumVal (
S , 2 , 1728472806U ) ; ssSetChecksumVal ( S , 3 , 2349322880U ) ; { mxArray
* slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" )
; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat ,
1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "9.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_tester_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_tester_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_tester_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & tester_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn ( S ,
mdlOutputsTID2 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
