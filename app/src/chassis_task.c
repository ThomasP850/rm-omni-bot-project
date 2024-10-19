#include "chassis_task.h"

#include "robot.h"
#include "remote.h"
#include "dji_motor.h"
#include "omni_kinematics.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;

DJI_Motor_Handle_t *g_chassis_motors[4];
float g_target_chassis_speeds[4];

void Chassis_Task_Init()
{
    
    for (int i = 1; i < 5; i++)
    {
        Motor_Config_t chassis_motor_config = {
        .can_bus = 1,
        .speed_controller_id = i,
        .offset = 0,
        .control_mode = VELOCITY_CONTROL,
        .motor_reversal = MOTOR_REVERSAL_NORMAL,
        .velocity_pid = 
            {
                .kp = 1000.0f,
                .ki = 0.0f,
                .kd = 100.0f,
                .output_limit = M2006_MAX_CURRENT,
            }};
        g_chassis_motors[i] = DJI_Motor_Init(&chassis_motor_config, M2006);
    }
}

void Chassis_Ctrl_Loop() {
    
    ChassisVelocities velocities = {
        g_robot_state.input.vy,
        -g_robot_state.input.vx,
        -g_robot_state.input.vOmega
    };
    calculateOmniWheelVelocities(velocities, g_target_chassis_speeds, MAX_CHASSIS_SPEED, (WHEEL_DIAMETER / 2), TRACK_WIDTH, WHEEL_BASE);

    for(int i = 0; i < 4; i++) {
        float tps = (g_target_chassis_speeds[i] / (PI * WHEEL_DIAMETER)) * (DJI_MAX_TICKS + 1);

        DJI_Motor_Set_Velocity(g_chassis_motors[i], tps);
    }
}