#include "__cf_roberttoWRosBackup.h"
#include <math.h>
#include "roberttoWRosBackup_acc.h"
#include "roberttoWRosBackup_acc_private.h"
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
boolean_T roberttoWRosBackup_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
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
return ( true ) ; } real_T roberttoWRosBackup_acc_rt_TDelayInterpolate (
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
static void mdlOutputs ( SimStruct * S , int_T tid ) {
SL_Bus_roberttoWRosBackup_usv16_msgs_Usv16ActuatorInputs rtb_B_10_1_0 ;
real_T rtb_B_10_46_0 ; int32_T isHit ; B_roberttoWRosBackup_T * _rtB ;
P_roberttoWRosBackup_T * _rtP ; X_roberttoWRosBackup_T * _rtX ;
DW_roberttoWRosBackup_T * _rtDW ; _rtDW = ( ( DW_roberttoWRosBackup_T * )
ssGetRootDWork ( S ) ) ; _rtX = ( ( X_roberttoWRosBackup_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_roberttoWRosBackup_T * ) ssGetModelRtp
( S ) ) ; _rtB = ( ( B_roberttoWRosBackup_T * ) _ssGetModelBlockIO ( S ) ) ;
rtb_B_10_1_0 = _rtB -> B_10_0_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { ssCallAccelRunBlock ( S , 10 , 4 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> B_10_5_0 = _rtP -> P_12 * _rtB -> B_10_4_0 [ 3 ] ; if ( _rtDW ->
InitialYd_FirstOutputTime ) { _rtDW -> InitialYd_FirstOutputTime = false ;
_rtB -> B_10_7_0 = _rtP -> P_14 ; } else { _rtB -> B_10_7_0 = _rtDW ->
Memory_PreviousInput ; } if ( _rtDW ->
Initialt_last_lane_change_FirstOutputTime ) { _rtDW ->
Initialt_last_lane_change_FirstOutputTime = false ; _rtB -> B_10_9_0 = _rtP
-> P_16 ; } else { _rtB -> B_10_9_0 = _rtDW -> Memory1_PreviousInput ; } }
_rtB -> B_10_14_0 = _rtX -> Integrator_CSTATE ; _rtB -> B_10_15_0 = _rtX ->
Integrator1_CSTATE ; _rtB -> B_10_16_0 = _rtB -> B_10_14_0 - _rtB ->
B_10_15_0 ; _rtB -> B_10_17_0 = _rtP -> P_23 * _rtB -> B_10_16_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> c_Mode = ( _rtB -> B_10_17_0 >=
_rtP -> P_25 ) ; } if ( _rtDW -> c_Mode ) { _rtB -> B_10_19_0 = _rtB ->
B_10_13_0 ; } else { _rtB -> B_10_19_0 = _rtB -> B_10_18_0 ; } _rtB ->
B_10_20_0 = _rtX -> Integrator_CSTATE_c ; _rtB -> B_10_21_0 = _rtX ->
Integrator1_CSTATE_g ; _rtB -> B_10_22_0 = _rtB -> B_10_20_0 - _rtB ->
B_10_21_0 ; _rtB -> B_10_23_0 = _rtP -> P_28 * _rtB -> B_10_22_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> c2_Mode = ( _rtB -> B_10_17_0 >=
_rtP -> P_31 ) ; _rtDW -> das_Mode = ( _rtB -> B_10_23_0 >= _rtP -> P_32 ) ;
} if ( _rtDW -> c2_Mode ) { _rtB -> B_10_26_0 = _rtB -> B_10_24_0 ; } else {
_rtB -> B_10_26_0 = _rtB -> B_10_25_0 ; } if ( _rtDW -> das_Mode ) { _rtB ->
B_10_27_0 = _rtB -> B_10_19_0 ; } else { _rtB -> B_10_27_0 = _rtB ->
B_10_26_0 ; } _rtB -> B_10_28_0 = _rtB -> B_10_27_0 - _rtB -> B_10_12_0 ; if
( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Switch_Mode = ( _rtB -> B_10_28_0
!= 0.0 ) ; } if ( _rtDW -> Switch_Mode ) { _rtB -> B_10_32_0 = _rtB ->
B_10_11_0 ; } else { _rtB -> B_4_0_0 = _rtB -> B_10_23_0 * _rtB -> B_10_29_0
; _rtB -> B_4_1_0 = _rtB -> B_10_30_0 - _rtB -> B_4_0_0 ; _rtB -> B_4_3_0 =
1.0 / ( 1.0 + muDoubleScalarExp ( _rtB -> B_4_1_0 ) ) ; _rtB -> B_10_32_0 =
_rtB -> B_4_3_0 ; } _rtB -> B_10_33_0 = _rtP -> P_35 * _rtB -> B_10_32_0 ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_9_0_0 =
_rtP -> P_1 ; ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS ) ; if (
_rtB -> B_7_0_0 ) { _rtB -> B_8_0_0 = _rtB -> B_7_0_1 ; srUpdateBC ( _rtDW ->
EnabledSubsystem_SubsysRanBC ) ; } if ( _rtB -> B_8_0_0 . Vel . Linear . X >
_rtP -> P_44 ) { _rtB -> B_10_45_0 = ( ( ( _rtB -> B_10_7_0 + _rtB ->
B_10_34_0 ) + _rtB -> B_10_35_0 ) + _rtB -> B_10_36_0 ) + _rtB -> B_10_37_0 ;
} else { _rtB -> B_10_45_0 = ( ( ( _rtB -> B_10_7_0 - _rtB -> B_10_39_0 ) -
_rtB -> B_10_40_0 ) - _rtB -> B_10_41_0 ) - _rtB -> B_10_42_0 ; } }
rtb_B_10_46_0 = ssGetT ( S ) ; _rtB -> B_10_47_0 = rtb_B_10_46_0 - _rtB ->
B_10_9_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Switch_Mode_c = (
_rtB -> B_10_47_0 > _rtP -> P_45 ) ; } if ( _rtDW -> Switch_Mode_c ) { _rtB
-> B_3_0_0 = _rtB -> B_10_33_0 - _rtB -> B_10_10_0 ; if ( _rtB -> B_3_0_0 >
_rtP -> P_3 ) { _rtB -> B_3_2_0 [ 0 ] = _rtB -> B_10_7_0 ; _rtB -> B_3_2_0 [
1 ] = _rtB -> B_10_9_0 ; } else { if ( _rtB -> B_8_0_0 . Vel . Linear . X !=
0.0 ) { _rtB -> B_2_0_0 [ 0 ] = _rtB -> B_10_45_0 ; _rtB -> B_2_0_0 [ 1 ] =
rtb_B_10_46_0 ; } else { _rtB -> B_2_0_0 [ 0 ] = _rtB -> B_10_7_0 ; _rtB ->
B_2_0_0 [ 1 ] = _rtB -> B_10_9_0 ; } _rtB -> B_3_2_0 [ 0 ] = _rtB -> B_2_0_0
[ 0 ] ; _rtB -> B_3_2_0 [ 1 ] = _rtB -> B_2_0_0 [ 1 ] ; } _rtB -> B_10_49_0 [
0 ] = _rtB -> B_3_2_0 [ 0 ] ; _rtB -> B_10_49_0 [ 1 ] = _rtB -> B_3_2_0 [ 1 ]
; } else { _rtB -> B_10_49_0 [ 0 ] = _rtB -> B_10_7_0 ; _rtB -> B_10_49_0 [ 1
] = _rtB -> B_10_9_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { _rtB -> B_10_50_0 = _rtB -> B_8_0_0 . Pose . X ; } _rtB -> B_10_51_0 =
_rtB -> B_10_49_0 [ 0 ] - _rtB -> B_10_50_0 ; _rtB -> B_10_52_0 = _rtB ->
B_10_51_0 * _rtB -> B_10_33_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW
-> Saturation2_MODE = _rtB -> B_10_52_0 >= _rtP -> P_46 ? 1 : _rtB ->
B_10_52_0 > _rtP -> P_47 ? 0 : - 1 ; } _rtB -> B_10_53_0 = _rtDW ->
Saturation2_MODE == 1 ? _rtP -> P_46 : _rtDW -> Saturation2_MODE == - 1 ?
_rtP -> P_47 : _rtB -> B_10_52_0 ; _rtB -> B_10_54_0 = _rtB -> B_10_5_0 +
_rtB -> B_10_53_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation1_MODE = _rtB -> B_10_54_0 >= _rtP -> P_48 ? 1 : _rtB -> B_10_54_0
> _rtP -> P_49 ? 0 : - 1 ; } _rtB -> B_10_55_0 = _rtDW -> Saturation1_MODE ==
1 ? _rtP -> P_48 : _rtDW -> Saturation1_MODE == - 1 ? _rtP -> P_49 : _rtB ->
B_10_54_0 ; _rtB -> B_10_56_0 = _rtP -> P_50 * _rtB -> B_10_55_0 ; _rtB ->
B_10_57_0 = 0.0 ; _rtB -> B_10_57_0 += _rtP -> P_53 * _rtX -> DsLead_CSTATE ;
_rtB -> B_10_57_0 += _rtP -> P_54 * _rtB -> B_10_56_0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation3_MODE = _rtB ->
B_10_57_0 >= _rtP -> P_55 ? 1 : _rtB -> B_10_57_0 > _rtP -> P_56 ? 0 : - 1 ;
} rtb_B_10_46_0 = _rtDW -> Saturation3_MODE == 1 ? _rtP -> P_55 : _rtDW ->
Saturation3_MODE == - 1 ? _rtP -> P_56 : _rtB -> B_10_57_0 ; _rtB ->
B_10_59_0 = rtb_B_10_1_0 ; _rtB -> B_10_59_0 . ActuatorInputs [ 0 ] = _rtB ->
B_10_3_0 ; _rtB -> B_10_59_0 . ActuatorInputs [ 1 ] = rtb_B_10_46_0 ; _rtB ->
B_10_59_0 . ActuatorInputs [ 2 ] = _rtB -> B_10_3_0 ; _rtB -> B_10_59_0 .
ActuatorInputs [ 3 ] = rtb_B_10_46_0 ; ssCallAccelRunBlock ( S , 5 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 61 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 62 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 63 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { _rtB -> B_10_64_0 = _rtB -> B_8_0_0 . Vel . Linear . X * _rtB -> B_10_5_0
; } _rtB -> B_10_65_0 = _rtB -> B_8_0_0 . Vel . Linear . X * _rtB ->
B_10_53_0 ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_57 ; _rtB ->
B_10_66_0 = roberttoWRosBackup_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 ,
* tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_58 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_g
. TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_g . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_59 ; _rtB -> B_10_67_0 =
roberttoWRosBackup_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay_IWORK_o . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_o . Last , _rtDW -> TransportDelay_IWORK_o . Tail ,
_rtDW -> TransportDelay_IWORK_o . Head , _rtP -> P_60 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID2 ( SimStruct * S
, int_T tid ) { B_roberttoWRosBackup_T * _rtB ; P_roberttoWRosBackup_T * _rtP
; _rtP = ( ( P_roberttoWRosBackup_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_roberttoWRosBackup_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_10_0_0 =
_rtP -> P_2 ; _rtB -> B_10_3_0 = _rtP -> P_5 * _rtP -> P_4 ; _rtB ->
B_10_10_0 = _rtP -> P_17 ; _rtB -> B_10_11_0 = _rtP -> P_18 ; _rtB ->
B_10_12_0 = _rtP -> P_19 ; _rtB -> B_10_13_0 = _rtP -> P_20 ; _rtB ->
B_10_18_0 = _rtP -> P_24 ; _rtB -> B_10_24_0 = _rtP -> P_29 ; _rtB ->
B_10_25_0 = _rtP -> P_30 ; _rtB -> B_10_29_0 = _rtP -> P_33 ; _rtB ->
B_10_30_0 = _rtP -> P_34 ; _rtB -> B_10_34_0 = _rtP -> P_36 ; _rtB ->
B_10_35_0 = _rtP -> P_37 ; _rtB -> B_10_36_0 = _rtP -> P_38 ; _rtB ->
B_10_37_0 = _rtP -> P_39 ; _rtB -> B_10_39_0 = _rtP -> P_40 ; _rtB ->
B_10_40_0 = _rtP -> P_41 ; _rtB -> B_10_41_0 = _rtP -> P_42 ; _rtB ->
B_10_42_0 = _rtP -> P_43 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T isHit ;
B_roberttoWRosBackup_T * _rtB ; P_roberttoWRosBackup_T * _rtP ;
DW_roberttoWRosBackup_T * _rtDW ; _rtDW = ( ( DW_roberttoWRosBackup_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_roberttoWRosBackup_T * ) ssGetModelRtp
( S ) ) ; _rtB = ( ( B_roberttoWRosBackup_T * ) _ssGetModelBlockIO ( S ) ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory_PreviousInput = _rtB -> B_10_49_0 [ 0 ] ; _rtDW ->
Memory1_PreviousInput = _rtB -> B_10_49_0 [ 1 ] ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = (
( _rtDW -> TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! roberttoWRosBackup_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Tail , & _rtDW -> TransportDelay_IWORK . Head , &
_rtDW -> TransportDelay_IWORK . Last , simTime - _rtP -> P_57 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_10_65_0 ; } { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay_PWORK_g . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_g .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_o . Head = ( ( _rtDW -> TransportDelay_IWORK_o . Head <
( _rtDW -> TransportDelay_IWORK_o . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_o . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_o . Head == _rtDW -> TransportDelay_IWORK_o . Tail ) {
if ( ! roberttoWRosBackup_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_o . CircularBufSize , & _rtDW -> TransportDelay_IWORK_o
. Tail , & _rtDW -> TransportDelay_IWORK_o . Head , & _rtDW ->
TransportDelay_IWORK_o . Last , simTime - _rtP -> P_59 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_o .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_o . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_o . Head ] = _rtB ->
B_10_64_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_roberttoWRosBackup_T * _rtB
; P_roberttoWRosBackup_T * _rtP ; X_roberttoWRosBackup_T * _rtX ;
XDot_roberttoWRosBackup_T * _rtXdot ; _rtXdot = ( ( XDot_roberttoWRosBackup_T
* ) ssGetdX ( S ) ) ; _rtX = ( ( X_roberttoWRosBackup_T * ) ssGetContStates (
S ) ) ; _rtP = ( ( P_roberttoWRosBackup_T * ) ssGetModelRtp ( S ) ) ; _rtB =
( ( B_roberttoWRosBackup_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_10_64_0 ; _rtXdot -> Integrator1_CSTATE = _rtB
-> B_10_67_0 ; _rtXdot -> Integrator_CSTATE_c = _rtB -> B_10_65_0 ; _rtXdot
-> Integrator1_CSTATE_g = _rtB -> B_10_66_0 ; _rtXdot -> DsLead_CSTATE = 0.0
; _rtXdot -> DsLead_CSTATE += _rtP -> P_51 * _rtX -> DsLead_CSTATE ; _rtXdot
-> DsLead_CSTATE += _rtP -> P_52 * _rtB -> B_10_56_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_roberttoWRosBackup_T *
_rtB ; P_roberttoWRosBackup_T * _rtP ; ZCV_roberttoWRosBackup_T * _rtZCSV ;
_rtZCSV = ( ( ZCV_roberttoWRosBackup_T * ) ssGetSolverZcSignalVector ( S ) )
; _rtP = ( ( P_roberttoWRosBackup_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_roberttoWRosBackup_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
c_SwitchCond_ZC = _rtB -> B_10_17_0 - _rtP -> P_25 ; _rtZCSV ->
c2_SwitchCond_ZC = _rtB -> B_10_17_0 - _rtP -> P_31 ; _rtZCSV ->
das_SwitchCond_ZC = _rtB -> B_10_23_0 - _rtP -> P_32 ; _rtZCSV ->
Switch_SwitchCond_ZC = _rtB -> B_10_28_0 ; _rtZCSV -> Switch_SwitchCond_ZC_j
= _rtB -> B_10_47_0 - _rtP -> P_45 ; _rtZCSV -> Saturation2_UprLim_ZC = _rtB
-> B_10_52_0 - _rtP -> P_46 ; _rtZCSV -> Saturation2_LwrLim_ZC = _rtB ->
B_10_52_0 - _rtP -> P_47 ; _rtZCSV -> Saturation1_UprLim_ZC = _rtB ->
B_10_54_0 - _rtP -> P_48 ; _rtZCSV -> Saturation1_LwrLim_ZC = _rtB ->
B_10_54_0 - _rtP -> P_49 ; _rtZCSV -> Saturation3_UprLim_ZC = _rtB ->
B_10_57_0 - _rtP -> P_55 ; _rtZCSV -> Saturation3_LwrLim_ZC = _rtB ->
B_10_57_0 - _rtP -> P_56 ; } static void mdlInitializeSizes ( SimStruct * S )
{ ssSetChecksumVal ( S , 0 , 540074466U ) ; ssSetChecksumVal ( S , 1 ,
3685242429U ) ; ssSetChecksumVal ( S , 2 , 85245441U ) ; ssSetChecksumVal ( S
, 3 , 3919920926U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat
= mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "9.1" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_roberttoWRosBackup_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_roberttoWRosBackup_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_roberttoWRosBackup_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & roberttoWRosBackup_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T ) )
; } static void mdlInitializeSampleTimes ( SimStruct * S ) {
slAccRegPrmChangeFcn ( S , mdlOutputsTID2 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
