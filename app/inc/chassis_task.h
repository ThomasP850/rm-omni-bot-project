#ifndef CHASSIS_TASK_H
#define CHASSIS_TASK_H

#define WHEEL_DIAMETER (0.07f)
#define TRACK_WIDTH (0.24749f)
#define WHEEL_BASE (0.24749f)
#define MAX_CHASSIS_SPEED (0.5f)

// Function prototypes
void Chassis_Task_Init(void);
void Chassis_Ctrl_Loop(void);

#endif // CHASSIS_TASK_H
