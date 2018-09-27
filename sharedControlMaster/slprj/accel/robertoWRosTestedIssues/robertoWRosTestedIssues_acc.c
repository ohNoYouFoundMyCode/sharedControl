#include "__cf_robertoWRosTestedIssues.h"
#include <math.h>
#include "robertoWRosTestedIssues_acc.h"
#include "robertoWRosTestedIssues_acc_private.h"
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
boolean_T robertoWRosTestedIssues_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
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
return ( true ) ; } real_T robertoWRosTestedIssues_acc_rt_TDelayInterpolate (
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
real_T rtb_B_7_49_0 ; int32_T isHit ; B_robertoWRosTestedIssues_T * _rtB ;
P_robertoWRosTestedIssues_T * _rtP ; X_robertoWRosTestedIssues_T * _rtX ;
DW_robertoWRosTestedIssues_T * _rtDW ; _rtDW = ( (
DW_robertoWRosTestedIssues_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( (
X_robertoWRosTestedIssues_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_robertoWRosTestedIssues_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_robertoWRosTestedIssues_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_7_1_0
= _rtX -> Integrator_CSTATE ; _rtB -> B_7_2_0 = _rtX -> Integrator1_CSTATE ;
_rtB -> B_7_3_0 = _rtB -> B_7_1_0 - _rtB -> B_7_2_0 ; _rtB -> B_7_4_0 = _rtP
-> P_5 * _rtB -> B_7_3_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
c_Mode = ( _rtB -> B_7_4_0 >= _rtP -> P_7 ) ; } if ( _rtDW -> c_Mode ) { _rtB
-> B_7_6_0 = _rtB -> B_7_0_0 ; } else { _rtB -> B_7_6_0 = _rtB -> B_7_5_0 ; }
_rtB -> B_7_7_0 = _rtX -> Integrator_CSTATE_p ; _rtB -> B_7_8_0 = _rtX ->
Integrator1_CSTATE_o ; _rtB -> B_7_9_0 = _rtB -> B_7_7_0 - _rtB -> B_7_8_0 ;
_rtB -> B_7_10_0 = _rtP -> P_10 * _rtB -> B_7_9_0 ; if ( ssIsMajorTimeStep (
S ) != 0 ) { _rtDW -> c2_Mode = ( _rtB -> B_7_4_0 >= _rtP -> P_13 ) ; _rtDW
-> das_Mode = ( _rtB -> B_7_10_0 >= _rtP -> P_14 ) ; } if ( _rtDW -> c2_Mode
) { _rtB -> B_7_13_0 = _rtB -> B_7_11_0 ; } else { _rtB -> B_7_13_0 = _rtB ->
B_7_12_0 ; } if ( _rtDW -> das_Mode ) { _rtB -> B_7_14_0 = _rtB -> B_7_6_0 ;
} else { _rtB -> B_7_14_0 = _rtB -> B_7_13_0 ; } ssCallAccelRunBlock ( S , 7
, 15 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_7_62_0 = _rtB -> B_7_16_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 7
, 20 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_7_21_0 = _rtP -> P_23 * _rtB ->
B_7_20_0 [ 0 ] ; if ( _rtDW -> InitialYd1_FirstOutputTime ) { _rtDW ->
InitialYd1_FirstOutputTime = false ; _rtB -> B_7_23_0 = _rtP -> P_25 ; } else
{ _rtB -> B_7_23_0 = _rtDW -> Memory2_PreviousInput ; } if ( _rtDW ->
Initialt_last_lane_change1_FirstOutputTime ) { _rtDW ->
Initialt_last_lane_change1_FirstOutputTime = false ; _rtB -> B_7_25_0 = _rtP
-> P_27 ; } else { _rtB -> B_7_25_0 = _rtDW -> Memory4_PreviousInput ; } }
_rtB -> B_7_29_0 = _rtB -> B_7_14_0 - _rtB -> B_7_28_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Switch_Mode = ( _rtB -> B_7_29_0 !=
0.0 ) ; } if ( _rtDW -> Switch_Mode ) { _rtB -> B_7_33_0 = _rtB -> B_7_27_0 ;
} else { _rtB -> B_4_0_0 = _rtB -> B_7_10_0 * _rtB -> B_7_30_0 ; _rtB ->
B_4_1_0 = _rtB -> B_7_31_0 - _rtB -> B_4_0_0 ; _rtB -> B_4_3_0 = 1.0 / ( 1.0
+ muDoubleScalarExp ( _rtB -> B_4_1_0 ) ) ; _rtB -> B_7_33_0 = _rtB ->
B_4_3_0 ; } _rtB -> B_7_34_0 = _rtP -> P_33 * _rtB -> B_7_33_0 ; _rtB ->
B_7_35_0 = _rtB -> B_7_34_0 - _rtB -> B_7_26_0 ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( _rtDW -> InitialYdot1_FirstOutputTime ) {
_rtDW -> InitialYdot1_FirstOutputTime = false ; _rtB -> B_7_41_0 = _rtP ->
P_39 ; } else { _rtB -> B_7_41_0 = _rtDW -> Memory5_PreviousInput ; } if (
_rtB -> B_7_41_0 > _rtP -> P_44 ) { _rtB -> B_7_48_0 = ( ( ( _rtB -> B_7_23_0
+ _rtB -> B_7_36_0 ) + _rtB -> B_7_37_0 ) + _rtB -> B_7_38_0 ) + _rtB ->
B_7_39_0 ; } else { _rtB -> B_7_48_0 = ( ( ( _rtB -> B_7_23_0 - _rtB ->
B_7_42_0 ) - _rtB -> B_7_43_0 ) - _rtB -> B_7_44_0 ) - _rtB -> B_7_45_0 ; } }
rtb_B_7_49_0 = ssGetT ( S ) ; _rtB -> B_7_50_0 = rtb_B_7_49_0 - _rtB ->
B_7_25_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Switch_Mode_o = (
_rtB -> B_7_50_0 > _rtP -> P_45 ) ; } if ( _rtDW -> Switch_Mode_o ) { if (
_rtB -> B_7_35_0 > _rtP -> P_1 ) { _rtB -> B_3_1_0 [ 0 ] = _rtB -> B_7_23_0 ;
_rtB -> B_3_1_0 [ 1 ] = _rtB -> B_7_25_0 ; } else { if ( _rtB -> B_7_41_0 !=
0.0 ) { _rtB -> B_2_0_0 [ 0 ] = _rtB -> B_7_48_0 ; _rtB -> B_2_0_0 [ 1 ] =
rtb_B_7_49_0 ; } else { _rtB -> B_2_0_0 [ 0 ] = _rtB -> B_7_23_0 ; _rtB ->
B_2_0_0 [ 1 ] = _rtB -> B_7_25_0 ; } _rtB -> B_3_1_0 [ 0 ] = _rtB -> B_2_0_0
[ 0 ] ; _rtB -> B_3_1_0 [ 1 ] = _rtB -> B_2_0_0 [ 1 ] ; } _rtB -> B_7_52_0 [
0 ] = _rtB -> B_3_1_0 [ 0 ] ; _rtB -> B_7_52_0 [ 1 ] = _rtB -> B_3_1_0 [ 1 ]
; } else { _rtB -> B_7_52_0 [ 0 ] = _rtB -> B_7_23_0 ; _rtB -> B_7_52_0 [ 1 ]
= _rtB -> B_7_25_0 ; } _rtB -> B_7_53_0 = 0.0 ; _rtB -> B_7_53_0 += _rtP ->
P_48 * _rtX -> USV1_CSTATE [ 2 ] ; _rtB -> B_7_54_0 = _rtB -> B_7_52_0 [ 0 ]
- _rtB -> B_7_53_0 ; _rtB -> B_7_55_0 = _rtB -> B_7_54_0 * _rtB -> B_7_34_0 ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation5_MODE = _rtB ->
B_7_55_0 >= _rtP -> P_49 ? 1 : _rtB -> B_7_55_0 > _rtP -> P_50 ? 0 : - 1 ; }
_rtB -> B_7_56_0 = _rtDW -> Saturation5_MODE == 1 ? _rtP -> P_49 : _rtDW ->
Saturation5_MODE == - 1 ? _rtP -> P_50 : _rtB -> B_7_55_0 ; _rtB -> B_7_57_0
= _rtP -> P_51 * _rtB -> B_7_56_0 ; _rtB -> B_7_58_0 = _rtB -> B_7_21_0 +
_rtB -> B_7_57_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation4_MODE = _rtB -> B_7_58_0 >= _rtP -> P_52 ? 1 : _rtB -> B_7_58_0 >
_rtP -> P_53 ? 0 : - 1 ; } _rtB -> B_7_59_0 = _rtDW -> Saturation4_MODE == 1
? _rtP -> P_52 : _rtDW -> Saturation4_MODE == - 1 ? _rtP -> P_53 : _rtB ->
B_7_58_0 ; _rtB -> B_7_60_0 = 0.0 ; _rtB -> B_7_60_0 += _rtP -> P_56 * _rtX
-> DsLead1_CSTATE ; _rtB -> B_7_60_0 += _rtP -> P_57 * _rtB -> B_7_59_0 ; if
( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation6_MODE = _rtB ->
B_7_60_0 >= _rtP -> P_58 ? 1 : _rtB -> B_7_60_0 > _rtP -> P_59 ? 0 : - 1 ; }
_rtB -> B_7_61_0 = _rtDW -> Saturation6_MODE == 1 ? _rtP -> P_58 : _rtDW ->
Saturation6_MODE == - 1 ? _rtP -> P_59 : _rtB -> B_7_60_0 ; _rtB -> B_7_62_0
. ActuatorInputs [ 0 ] = _rtB -> B_7_19_0 ; _rtB -> B_7_62_0 . ActuatorInputs
[ 1 ] = _rtB -> B_7_61_0 ; _rtB -> B_7_62_0 . ActuatorInputs [ 2 ] = _rtB ->
B_7_19_0 ; _rtB -> B_7_62_0 . ActuatorInputs [ 3 ] = _rtB -> B_7_61_0 ;
ssCallAccelRunBlock ( S , 5 , 0 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 7
, 64 , SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 7 , 65 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 66 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 67 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 68 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 69 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 70 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ( _rtDW -> TimeStampA >= ssGetT ( S ) ) && (
_rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB -> B_7_71_0 = 0.0 ; } else {
rtb_B_7_49_0 = _rtDW -> TimeStampA ; lastU = & _rtDW -> LastUAtTimeA ; if (
_rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if ( _rtDW -> TimeStampB <
ssGetT ( S ) ) { rtb_B_7_49_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S ) ) {
rtb_B_7_49_0 = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } }
_rtB -> B_7_71_0 = ( _rtB -> B_7_53_0 - * lastU ) / ( ssGetT ( S ) -
rtb_B_7_49_0 ) ; } ssCallAccelRunBlock ( S , 7 , 72 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 73 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_7_74_0 = _rtP ->
P_60 * _rtB -> B_7_21_0 ; } _rtB -> B_7_75_0 = _rtB -> B_7_71_0 * _rtB ->
B_7_74_0 ; _rtB -> B_7_76_0 = _rtP -> P_61 * _rtB -> B_7_56_0 ; _rtB ->
B_7_77_0 = _rtB -> B_7_71_0 * _rtB -> B_7_76_0 ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_62 ; _rtB -> B_7_78_0 = robertoWRosTestedIssues_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_63 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput
( S ) == ssGetT ( S ) ) ) ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_64 ; _rtB
-> B_7_79_0 = robertoWRosTestedIssues_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_j .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_j . Last , _rtDW ->
TransportDelay_IWORK_j . Tail , _rtDW -> TransportDelay_IWORK_j . Head , _rtP
-> P_65 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID2 ( SimStruct * S , int_T tid ) { B_robertoWRosTestedIssues_T *
_rtB ; P_robertoWRosTestedIssues_T * _rtP ; _rtP = ( (
P_robertoWRosTestedIssues_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_robertoWRosTestedIssues_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_7_0_0
= _rtP -> P_2 ; _rtB -> B_7_5_0 = _rtP -> P_6 ; _rtB -> B_7_11_0 = _rtP ->
P_11 ; _rtB -> B_7_12_0 = _rtP -> P_12 ; _rtB -> B_7_16_0 = _rtP -> P_0 ;
_rtB -> B_7_19_0 = _rtP -> P_16 * _rtP -> P_15 ; _rtB -> B_7_26_0 = _rtP ->
P_28 ; _rtB -> B_7_27_0 = _rtP -> P_29 ; _rtB -> B_7_28_0 = _rtP -> P_30 ;
_rtB -> B_7_30_0 = _rtP -> P_31 ; _rtB -> B_7_31_0 = _rtP -> P_32 ; _rtB ->
B_7_36_0 = _rtP -> P_34 ; _rtB -> B_7_37_0 = _rtP -> P_35 ; _rtB -> B_7_38_0
= _rtP -> P_36 ; _rtB -> B_7_39_0 = _rtP -> P_37 ; _rtB -> B_7_42_0 = _rtP ->
P_40 ; _rtB -> B_7_43_0 = _rtP -> P_41 ; _rtB -> B_7_44_0 = _rtP -> P_42 ;
_rtB -> B_7_45_0 = _rtP -> P_43 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_robertoWRosTestedIssues_T * _rtB ;
P_robertoWRosTestedIssues_T * _rtP ; DW_robertoWRosTestedIssues_T * _rtDW ;
_rtDW = ( ( DW_robertoWRosTestedIssues_T * ) ssGetRootDWork ( S ) ) ; _rtP =
( ( P_robertoWRosTestedIssues_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_robertoWRosTestedIssues_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory2_PreviousInput = _rtB -> B_7_52_0 [ 0 ] ; _rtDW ->
Memory4_PreviousInput = _rtB -> B_7_52_0 [ 1 ] ; _rtDW ->
Memory5_PreviousInput = _rtB -> B_7_71_0 ; } if ( _rtDW -> TimeStampA == (
rtInf ) ) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeA ; } else if ( _rtDW -> TimeStampB == ( rtInf ) ) { _rtDW ->
TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } else if (
_rtDW -> TimeStampA < _rtDW -> TimeStampB ) { _rtDW -> TimeStampA = ssGetT (
S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else { _rtDW -> TimeStampB = ssGetT
( S ) ; lastU = & _rtDW -> LastUAtTimeB ; } * lastU = _rtB -> B_7_53_0 ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK .
Head < ( _rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
robertoWRosTestedIssues_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_62 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_7_77_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_j . Head = ( ( _rtDW ->
TransportDelay_IWORK_j . Head < ( _rtDW -> TransportDelay_IWORK_j .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_j . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_j . Head == _rtDW ->
TransportDelay_IWORK_j . Tail ) { if ( !
robertoWRosTestedIssues_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_j . CircularBufSize , & _rtDW -> TransportDelay_IWORK_j
. Tail , & _rtDW -> TransportDelay_IWORK_j . Head , & _rtDW ->
TransportDelay_IWORK_j . Last , simTime - _rtP -> P_64 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_j .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_j . Head ] = _rtB ->
B_7_75_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 7 , 80 , SS_CALL_MDL_UPDATE ) ; } UNUSED_PARAMETER
( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_robertoWRosTestedIssues_T *
_rtB ; P_robertoWRosTestedIssues_T * _rtP ; X_robertoWRosTestedIssues_T *
_rtX ; XDot_robertoWRosTestedIssues_T * _rtXdot ; _rtXdot = ( (
XDot_robertoWRosTestedIssues_T * ) ssGetdX ( S ) ) ; _rtX = ( (
X_robertoWRosTestedIssues_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_robertoWRosTestedIssues_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_robertoWRosTestedIssues_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_7_75_0 ; _rtXdot -> Integrator1_CSTATE = _rtB
-> B_7_79_0 ; _rtXdot -> Integrator_CSTATE_p = _rtB -> B_7_77_0 ; _rtXdot ->
Integrator1_CSTATE_o = _rtB -> B_7_78_0 ; _rtXdot -> USV1_CSTATE [ 0 ] = 0.0
; _rtXdot -> USV1_CSTATE [ 1 ] = 0.0 ; _rtXdot -> USV1_CSTATE [ 2 ] = 0.0 ;
_rtXdot -> USV1_CSTATE [ 1 ] += _rtP -> P_46 [ 0 ] * _rtX -> USV1_CSTATE [ 0
] ; _rtXdot -> USV1_CSTATE [ 1 ] += _rtP -> P_46 [ 1 ] * _rtX -> USV1_CSTATE
[ 1 ] ; _rtXdot -> USV1_CSTATE [ 2 ] += _rtP -> P_46 [ 2 ] * _rtX ->
USV1_CSTATE [ 1 ] ; _rtXdot -> USV1_CSTATE [ 0 ] += _rtP -> P_47 * _rtB ->
B_7_61_0 ; _rtXdot -> DsLead1_CSTATE = 0.0 ; _rtXdot -> DsLead1_CSTATE +=
_rtP -> P_54 * _rtX -> DsLead1_CSTATE ; _rtXdot -> DsLead1_CSTATE += _rtP ->
P_55 * _rtB -> B_7_59_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_robertoWRosTestedIssues_T
* _rtB ; P_robertoWRosTestedIssues_T * _rtP ; ZCV_robertoWRosTestedIssues_T *
_rtZCSV ; _rtZCSV = ( ( ZCV_robertoWRosTestedIssues_T * )
ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( ( P_robertoWRosTestedIssues_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_robertoWRosTestedIssues_T * )
_ssGetModelBlockIO ( S ) ) ; _rtZCSV -> c_SwitchCond_ZC = _rtB -> B_7_4_0 -
_rtP -> P_7 ; _rtZCSV -> c2_SwitchCond_ZC = _rtB -> B_7_4_0 - _rtP -> P_13 ;
_rtZCSV -> das_SwitchCond_ZC = _rtB -> B_7_10_0 - _rtP -> P_14 ; _rtZCSV ->
Switch_SwitchCond_ZC = _rtB -> B_7_29_0 ; _rtZCSV -> Switch_SwitchCond_ZC_k =
_rtB -> B_7_50_0 - _rtP -> P_45 ; _rtZCSV -> Saturation5_UprLim_ZC = _rtB ->
B_7_55_0 - _rtP -> P_49 ; _rtZCSV -> Saturation5_LwrLim_ZC = _rtB -> B_7_55_0
- _rtP -> P_50 ; _rtZCSV -> Saturation4_UprLim_ZC = _rtB -> B_7_58_0 - _rtP
-> P_52 ; _rtZCSV -> Saturation4_LwrLim_ZC = _rtB -> B_7_58_0 - _rtP -> P_53
; _rtZCSV -> Saturation6_UprLim_ZC = _rtB -> B_7_60_0 - _rtP -> P_58 ;
_rtZCSV -> Saturation6_LwrLim_ZC = _rtB -> B_7_60_0 - _rtP -> P_59 ; } static
void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
100295001U ) ; ssSetChecksumVal ( S , 1 , 1511514832U ) ; ssSetChecksumVal (
S , 2 , 2828564050U ) ; ssSetChecksumVal ( S , 3 , 3738591402U ) ; { mxArray
* slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" )
; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat ,
1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "9.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_robertoWRosTestedIssues_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_robertoWRosTestedIssues_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_robertoWRosTestedIssues_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & robertoWRosTestedIssues_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T
) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) {
slAccRegPrmChangeFcn ( S , mdlOutputsTID2 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
