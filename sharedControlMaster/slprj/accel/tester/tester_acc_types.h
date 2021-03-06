#include "__cf_tester.h"
#ifndef RTW_HEADER_tester_acc_types_h_
#define RTW_HEADER_tester_acc_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_tester_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_tester_ros_time_Time_
typedef struct { real_T Sec ; real_T Nsec ; } SL_Bus_tester_ros_time_Time ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_tester_usv16_msgs_Usv16ActuatorInputs_
#define DEFINED_TYPEDEF_FOR_SL_Bus_tester_usv16_msgs_Usv16ActuatorInputs_
typedef struct { real_T T ; real_T ActuatorInputs [ 4 ] ;
SL_Bus_tester_ros_time_Time TimeNow ; }
SL_Bus_tester_usv16_msgs_Usv16ActuatorInputs ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_tester_geometry_msgs_Pose2D_
#define DEFINED_TYPEDEF_FOR_SL_Bus_tester_geometry_msgs_Pose2D_
typedef struct { real_T X ; real_T Y ; real_T Theta ; }
SL_Bus_tester_geometry_msgs_Pose2D ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_tester_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_tester_geometry_msgs_Vector3_
typedef struct { real_T X ; real_T Y ; real_T Z ; }
SL_Bus_tester_geometry_msgs_Vector3 ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_tester_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_tester_geometry_msgs_Twist_
typedef struct { SL_Bus_tester_geometry_msgs_Vector3 Linear ;
SL_Bus_tester_geometry_msgs_Vector3 Angular ; }
SL_Bus_tester_geometry_msgs_Twist ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_tester_usv16_msgs_Usv16State_
#define DEFINED_TYPEDEF_FOR_SL_Bus_tester_usv16_msgs_Usv16State_
typedef struct { real_T T ; SL_Bus_tester_ros_time_Time TimeNow ;
SL_Bus_tester_geometry_msgs_Pose2D Pose ; SL_Bus_tester_geometry_msgs_Twist
Vel ; SL_Bus_tester_geometry_msgs_Twist Acc ; }
SL_Bus_tester_usv16_msgs_Usv16State ;
#endif
typedef struct P_tester_T_ P_tester_T ;
#endif
