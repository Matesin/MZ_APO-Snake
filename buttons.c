#include "buttons.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SENSITIVITY 3


int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range) {
//modify the current value of chosen button based on direction of rotation
    if (cur_value < prev_value && (abs(cur_value - prev_value) > SENSITIVITY)) {
      if (action_num == 1) {
        action_num = upper_range;
      } else {
        action_num -= 1;
      }
    } else if ((cur_value > prev_value) && (abs(cur_value - prev_value) > SENSITIVITY)) {
      if (action_num == upper_range) {
        action_num = 1;
      } else {
        action_num += 1;
      }
    }
    //return the current value of button
    return action_num;
}