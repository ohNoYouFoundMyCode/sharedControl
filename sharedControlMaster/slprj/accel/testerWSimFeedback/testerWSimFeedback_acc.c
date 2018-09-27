#include "__cf_testerWSimFeedback.h"
#include <math.h>
#include "testerWSimFeedback_acc.h"
#include "testerWSimFeedback_acc_private.h"
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
boolean_T testerWSimFeedback_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T testerWSimFeedback_acc_rt_TDelayInterpolate (
real_T tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T
bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput
, boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
SimStruct * S , void * diag ) { if ( ! _ssIsErrorStatusAslErrMsg ( S ) ) {
_ssSet_slErrMsg ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T * lastU ;
real_T rtb_B_9_34_0 ; int32_T isHit ; B_testerWSimFeedback_T * _rtB ;
P_testerWSimFeedback_T * _rtP ; X_testerWSimFeedback_T * _rtX ;
DW_testerWSimFeedback_T * _rtDW ; _rtDW = ( ( DW_testerWSimFeedback_T * )
ssGetRootDWork ( S ) ) ; _rtX = ( ( X_testerWSimFeedback_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_testerWSimFeedback_T * ) ssGetModelRtp
( S ) ) ; _rtB = ( ( B_testerWSimFeedback_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtB -> B_9_1_0 = 0.0 ; _rtB -> B_9_1_0 += _rtP -> P_7 * _rtX ->
ZeroPole_CSTATE [ 2 ] ; if ( ( _rtDW -> TimeStampA >= ssGetT ( S ) ) && (
_rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB -> B_9_2_0 = 0.0 ; } else {
rtb_B_9_34_0 = _rtDW -> TimeStampA ; lastU = & _rtDW -> LastUAtTimeA ; if (
_rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if ( _rtDW -> TimeStampB <
ssGetT ( S ) ) { rtb_B_9_34_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S ) ) {
rtb_B_9_34_0 = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } }
_rtB -> B_9_2_0 = ( _rtB -> B_9_1_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_9_34_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 9 , 3 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_9_4_0 =
_rtP -> P_14 * _rtB -> B_9_3_0 [ 3 ] ; } _rtB -> B_9_5_0 = _rtB -> B_9_2_0 *
_rtB -> B_9_4_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_9_6_0 = _rtP -> P_15 * _rtB -> B_9_5_0 + _rtDW ->
DiscreteTimeIntegrator_DSTATE ; } { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_17 ; _rtB
-> B_9_7_0 = testerWSimFeedback_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_18 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_9_8_0 = _rtP -> P_19 * _rtB -> B_9_7_0 + _rtDW ->
DiscreteTimeIntegrator1_DSTATE ; _rtB -> B_9_10_0 = ( _rtB -> B_9_6_0 - _rtB
-> B_9_8_0 ) * _rtP -> P_21 ; _rtB -> B_9_15_0 = ( _rtDW ->
DiscreteTimeIntegrator_DSTATE_g - _rtDW -> DiscreteTimeIntegrator1_DSTATE_i )
* _rtP -> P_27 ; if ( _rtB -> B_9_15_0 >= _rtP -> P_30 ) { if ( _rtB ->
B_9_10_0 >= _rtP -> P_3 ) { _rtB -> B_9_20_0 = _rtB -> B_9_0_0 ; } else {
_rtB -> B_9_20_0 = _rtB -> B_9_11_0 ; } } else if ( _rtB -> B_9_10_0 >= _rtP
-> P_2 ) { _rtB -> B_9_20_0 = _rtB -> B_9_16_0 ; } else { _rtB -> B_9_20_0 =
_rtB -> B_9_17_0 ; } ssCallAccelRunBlock ( S , 9 , 21 , SS_CALL_MDL_OUTPUTS )
; { if ( ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK . AQHandles ||
_rtDW -> HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK .
SlioLTF ) && ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Derivative_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_9_2_0 ) ; } }
if ( _rtDW -> InitialYd_FirstOutputTime ) { _rtDW ->
InitialYd_FirstOutputTime = false ; _rtB -> B_9_24_0 = _rtP -> P_32 ; } else
{ _rtB -> B_9_24_0 = _rtDW -> Memory_PreviousInput ; } if ( _rtDW ->
Initialt_last_lane_change_FirstOutputTime ) { _rtDW ->
Initialt_last_lane_change_FirstOutputTime = false ; _rtB -> B_9_26_0 = _rtP
-> P_34 ; } else { _rtB -> B_9_26_0 = _rtDW -> Memory1_PreviousInput ; } if (
_rtB -> B_9_20_0 - _rtB -> B_9_29_0 != 0.0 ) { rtb_B_9_34_0 = _rtB ->
B_9_28_0 ; } else { rtb_B_9_34_0 = 1.0 / ( muDoubleScalarExp ( _rtB ->
B_9_32_0 - _rtB -> B_9_15_0 * _rtB -> B_9_31_0 ) + 1.0 ) ; } _rtB -> B_9_35_0
= _rtP -> P_40 * rtb_B_9_34_0 ; _rtB -> B_9_36_0 = _rtB -> B_9_35_0 - _rtB ->
B_9_27_0 ; if ( _rtDW -> InitialYdot_FirstOutputTime ) { _rtDW ->
InitialYdot_FirstOutputTime = false ; _rtB -> B_9_42_0 = _rtP -> P_46 ; }
else { _rtB -> B_9_42_0 = _rtDW -> Memory3_PreviousInput ; } if ( _rtB ->
B_9_42_0 > _rtP -> P_51 ) { _rtB -> B_9_49_0 = ( ( ( _rtB -> B_9_24_0 + _rtB
-> B_9_37_0 ) + _rtB -> B_9_38_0 ) + _rtB -> B_9_39_0 ) + _rtB -> B_9_40_0 ;
} else { _rtB -> B_9_49_0 = ( ( ( _rtB -> B_9_24_0 - _rtB -> B_9_43_0 ) -
_rtB -> B_9_44_0 ) - _rtB -> B_9_45_0 ) - _rtB -> B_9_46_0 ; } } rtb_B_9_34_0
= ssGetT ( S ) ; if ( rtb_B_9_34_0 - _rtB -> B_9_26_0 > _rtP -> P_52 ) { if (
_rtB -> B_9_36_0 > _rtP -> P_1 ) { _rtB -> B_9_53_0 [ 0 ] = _rtB -> B_9_24_0
; _rtB -> B_9_53_0 [ 1 ] = _rtB -> B_9_26_0 ; } else if ( _rtB -> B_9_42_0 !=
0.0 ) { _rtB -> B_9_53_0 [ 0 ] = _rtB -> B_9_49_0 ; _rtB -> B_9_53_0 [ 1 ] =
rtb_B_9_34_0 ; } else { _rtB -> B_9_53_0 [ 0 ] = _rtB -> B_9_24_0 ; _rtB ->
B_9_53_0 [ 1 ] = _rtB -> B_9_26_0 ; } } else { _rtB -> B_9_53_0 [ 0 ] = _rtB
-> B_9_24_0 ; _rtB -> B_9_53_0 [ 1 ] = _rtB -> B_9_26_0 ; } rtb_B_9_34_0 = (
_rtB -> B_9_53_0 [ 0 ] - _rtB -> B_9_1_0 ) * _rtB -> B_9_35_0 ; if (
rtb_B_9_34_0 > _rtP -> P_53 ) { _rtB -> B_9_56_0 = _rtP -> P_53 ; } else if (
rtb_B_9_34_0 < _rtP -> P_54 ) { _rtB -> B_9_56_0 = _rtP -> P_54 ; } else {
_rtB -> B_9_56_0 = rtb_B_9_34_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { { if ( ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK . AQHandles ||
_rtDW -> HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK .
SlioLTF ) && ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Saturation2_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_9_56_0 ) ; } }
_rtB -> B_9_58_0 = _rtP -> P_0 ; } _rtB -> B_9_61_0 = 0.0 ; _rtB -> B_9_61_0
+= _rtP -> P_57 * _rtX -> TransferFcn_CSTATE ; rtb_B_9_34_0 = _rtP -> P_58 *
_rtB -> B_9_61_0 ; _rtB -> B_9_63_0 = _rtB -> B_9_58_0 ; _rtB -> B_9_63_0 .
ActuatorInputs [ 0 ] = _rtB -> B_9_60_0 ; _rtB -> B_9_63_0 . ActuatorInputs [
1 ] = rtb_B_9_34_0 ; _rtB -> B_9_63_0 . ActuatorInputs [ 2 ] = _rtB ->
B_9_60_0 ; _rtB -> B_9_63_0 . ActuatorInputs [ 3 ] = rtb_B_9_34_0 ;
ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 9
, 65 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 9 , 66 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 9 , 67 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 9 , 68 ,
SS_CALL_MDL_OUTPUTS ) ; } rtb_B_9_34_0 = _rtB -> B_9_4_0 + _rtB -> B_9_56_0 ;
if ( rtb_B_9_34_0 > _rtP -> P_59 ) { _rtB -> B_9_70_0 = _rtP -> P_59 ; } else
if ( rtb_B_9_34_0 < _rtP -> P_60 ) { _rtB -> B_9_70_0 = _rtP -> P_60 ; } else
{ _rtB -> B_9_70_0 = rtb_B_9_34_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 9 , 71 , SS_CALL_MDL_OUTPUTS )
; ssCallAccelRunBlock ( S , 9 , 72 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 9 , 73 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 9 , 74 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_9_75_0
= _rtB -> B_9_2_0 * _rtB -> B_9_56_0 ; { real_T * * uBuffer = ( real_T * * )
& _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_61 ;
_rtB -> B_9_76_0 = testerWSimFeedback_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_l .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_l . Last , _rtDW ->
TransportDelay_IWORK_l . Tail , _rtDW -> TransportDelay_IWORK_l . Head , _rtP
-> P_62 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_9_80_0 = (
_rtP -> P_63 * _rtB -> B_9_70_0 - _rtX -> Filter_CSTATE ) * _rtP -> P_65 ;
_rtB -> B_9_81_0 = _rtP -> P_66 * _rtB -> B_9_70_0 ; rtb_B_9_34_0 = ( _rtP ->
P_68 * _rtB -> B_9_70_0 + _rtX -> Integrator_CSTATE ) + _rtB -> B_9_80_0 ; if
( rtb_B_9_34_0 > _rtP -> P_69 ) { _rtB -> B_9_85_0 = _rtP -> P_69 ; } else if
( rtb_B_9_34_0 < _rtP -> P_70 ) { _rtB -> B_9_85_0 = _rtP -> P_70 ; } else {
_rtB -> B_9_85_0 = rtb_B_9_34_0 ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID2 ( SimStruct * S , int_T tid ) { B_testerWSimFeedback_T * _rtB
; P_testerWSimFeedback_T * _rtP ; _rtP = ( ( P_testerWSimFeedback_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_testerWSimFeedback_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_9_0_0 = _rtP -> P_4 ; _rtB -> B_9_11_0
= _rtP -> P_22 ; _rtB -> B_9_16_0 = _rtP -> P_28 ; _rtB -> B_9_17_0 = _rtP ->
P_29 ; _rtB -> B_9_27_0 = _rtP -> P_35 ; _rtB -> B_9_28_0 = _rtP -> P_36 ;
_rtB -> B_9_29_0 = _rtP -> P_37 ; _rtB -> B_9_31_0 = _rtP -> P_38 ; _rtB ->
B_9_32_0 = _rtP -> P_39 ; _rtB -> B_9_37_0 = _rtP -> P_41 ; _rtB -> B_9_38_0
= _rtP -> P_42 ; _rtB -> B_9_39_0 = _rtP -> P_43 ; _rtB -> B_9_40_0 = _rtP ->
P_44 ; _rtB -> B_9_43_0 = _rtP -> P_47 ; _rtB -> B_9_44_0 = _rtP -> P_48 ;
_rtB -> B_9_45_0 = _rtP -> P_49 ; _rtB -> B_9_46_0 = _rtP -> P_50 ; _rtB ->
B_9_60_0 = _rtP -> P_55 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_testerWSimFeedback_T * _rtB ; P_testerWSimFeedback_T * _rtP
; DW_testerWSimFeedback_T * _rtDW ; _rtDW = ( ( DW_testerWSimFeedback_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_testerWSimFeedback_T * ) ssGetModelRtp
( S ) ) ; _rtB = ( ( B_testerWSimFeedback_T * ) _ssGetModelBlockIO ( S ) ) ;
if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == (
rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) {
_rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else
{ _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } *
lastU = _rtB -> B_9_1_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { _rtDW -> DiscreteTimeIntegrator_DSTATE = _rtP -> P_15 * _rtB -> B_9_5_0
+ _rtB -> B_9_6_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! testerWSimFeedback_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Tail , & _rtDW -> TransportDelay_IWORK . Head , &
_rtDW -> TransportDelay_IWORK . Last , simTime - _rtP -> P_17 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_9_5_0 ; } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> DiscreteTimeIntegrator1_DSTATE =
_rtP -> P_19 * _rtB -> B_9_7_0 + _rtB -> B_9_8_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE_g += _rtP -> P_23 * _rtB -> B_9_75_0 ; _rtDW ->
DiscreteTimeIntegrator1_DSTATE_i += _rtP -> P_25 * _rtB -> B_9_76_0 ; _rtDW
-> Memory_PreviousInput = _rtB -> B_9_53_0 [ 0 ] ; _rtDW ->
Memory1_PreviousInput = _rtB -> B_9_53_0 [ 1 ] ; _rtDW ->
Memory3_PreviousInput = _rtB -> B_9_2_0 ; } { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; boolean_T bufferisfull = false ; _rtDW ->
TransportDelay_IWORK_l . Head = ( ( _rtDW -> TransportDelay_IWORK_l . Head <
( _rtDW -> TransportDelay_IWORK_l . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_l . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_l . Head == _rtDW -> TransportDelay_IWORK_l . Tail ) {
bufferisfull = true ; if ( !
testerWSimFeedback_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_l . CircularBufSize , & _rtDW -> TransportDelay_IWORK_l
. Tail , & _rtDW -> TransportDelay_IWORK_l . Head , & _rtDW ->
TransportDelay_IWORK_l . Last , simTime - _rtP -> P_61 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 1 , false , & _rtDW -> TransportDelay_IWORK_l .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_l . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_l . Head ] = _rtB ->
B_9_75_0 ; if ( bufferisfull ) { ssSetBlockStateForSolverChangedAtMajorStep (
S ) ; ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_testerWSimFeedback_T * _rtB
; P_testerWSimFeedback_T * _rtP ; X_testerWSimFeedback_T * _rtX ;
XDot_testerWSimFeedback_T * _rtXdot ; _rtXdot = ( ( XDot_testerWSimFeedback_T
* ) ssGetdX ( S ) ) ; _rtX = ( ( X_testerWSimFeedback_T * ) ssGetContStates (
S ) ) ; _rtP = ( ( P_testerWSimFeedback_T * ) ssGetModelRtp ( S ) ) ; _rtB =
( ( B_testerWSimFeedback_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
ZeroPole_CSTATE [ 0 ] = 0.0 ; _rtXdot -> ZeroPole_CSTATE [ 1 ] = 0.0 ;
_rtXdot -> ZeroPole_CSTATE [ 2 ] = 0.0 ; _rtXdot -> ZeroPole_CSTATE [ 1 ] +=
_rtP -> P_5 [ 0 ] * _rtX -> ZeroPole_CSTATE [ 0 ] ; _rtXdot ->
ZeroPole_CSTATE [ 1 ] += _rtP -> P_5 [ 1 ] * _rtX -> ZeroPole_CSTATE [ 1 ] ;
_rtXdot -> ZeroPole_CSTATE [ 2 ] += _rtP -> P_5 [ 2 ] * _rtX ->
ZeroPole_CSTATE [ 1 ] ; _rtXdot -> ZeroPole_CSTATE [ 0 ] += _rtP -> P_6 *
_rtB -> B_9_61_0 ; _rtXdot -> TransferFcn_CSTATE = 0.0 ; _rtXdot ->
TransferFcn_CSTATE += _rtP -> P_56 * _rtX -> TransferFcn_CSTATE ; _rtXdot ->
TransferFcn_CSTATE += _rtB -> B_9_85_0 ; _rtXdot -> Filter_CSTATE = _rtB ->
B_9_80_0 ; _rtXdot -> Integrator_CSTATE = _rtB -> B_9_81_0 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 2788771668U
) ; ssSetChecksumVal ( S , 1 , 994552695U ) ; ssSetChecksumVal ( S , 2 ,
3597040287U ) ; ssSetChecksumVal ( S , 3 , 3715539389U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "9.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_testerWSimFeedback_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_testerWSimFeedback_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_testerWSimFeedback_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & testerWSimFeedback_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T ) )
; } static void mdlInitializeSampleTimes ( SimStruct * S ) {
slAccRegPrmChangeFcn ( S , mdlOutputsTID2 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
