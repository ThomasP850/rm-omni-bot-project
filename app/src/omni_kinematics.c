#include "omni_kinematics.h"

#include <math.h>
#include <stdio.h>

const float g_rot_mat[4][2] = {
  {-0.7071, 0.7071},
  {-0.7071, -0.7071},
  {0.7071, -0.7071},
  {0.7071, 0.7071}
};

void calculateOmniWheelVelocities(const ChassisVelocities targetVelocities, float outputVelocities[4], float maxWheelSpeed, float wheelRadius, float trackWidth, float wheelBase) {
  float d = hypot(trackWidth / 2, wheelBase / 2);

  float s_max = 0 ;
  for(int i = 0; i < 4; i++) {
    outputVelocities[i] = g_rot_mat[i][0] * targetVelocities.x +
          g_rot_mat[i][1] * targetVelocities.y +
          d * targetVelocities.omega;
    outputVelocities[i] *= (1 / wheelRadius);

    if(fabs(outputVelocities[i]) > s_max) {
      s_max = fabs(outputVelocities[i]);
    }
  }

  if(s_max > maxWheelSpeed) {
    float s_scale = (s_max == 0)? 1 : (maxWheelSpeed / s_max);
    for(int i = 0; i < 4; i++) {
      outputVelocities[i] *= s_scale;
    }
  }
}
