#include "robohead.h"

/* code by <rob.tillaart@removethisgmail.com>
 * ref. http://arduino.cc/playground/Main/MultiMap
 * approximation for non-linear functions - used for the Sharp IR ranger
 */
int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return map(val, _in[pos-1], _in[pos], _out[pos-1], _out[pos]);
}
