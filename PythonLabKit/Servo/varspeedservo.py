import time
# import pwmio
# import board
# from adafruit_motor import servo

from myservo import Servo
from varspeed import Vspeed

class VspeedServo(Vspeed):
  """Provides an non-blocking object that can be called repeatedly 
    with the move() and sequence() functions to generate a timed series 
    of values from a current position to a new position(s)
  """

  def __init__(self, init_position = 0, result = "int", MIN = 0, MAX = 180, pin: int=15):
    """Creates and initialzes a varspeed object.

    Args:
        init_position (int/float): sets the initial position of the object.
        result (string = "int" or "float"): sets the type of the returned position.

    Returns:
        object: returns a varspeed object

    """

    self.MIN = MIN
    self.MAX = MAX

    # set up the varspeed object
    #
    # init_position = initial start position
    # result = float, int
    self.vs = Vspeed(init_position=init_position, result=result)

    # make the output of the function be within the bounds set
    self.vs.set_bounds(lower_bound=MIN, upper_bound=MAX)

    # Create a servo object
    self._servo=Servo(pin)

  def move_normal(self, new_position = 0):
    print(f'Paused for 5 seconds at {new_position}...')
    self._servo.ServoAngle(new_position)
    time.sleep(5)

  def move(self, new_position = 0, time_secs = 2.0, steps = 20, easing = "LinearInOut"):
    """Generates a series of values that transition from the current position to a new_position

    Args:
        new_position (float): new position output will change to over time_secs
        time_secs (int): time for the transition to the new_position
        steps (int): number of steps to change from the start position to the new_position
        easing (string): the easing function to use for the transition

    Returns:
        position (int or float): each new position, marked by changed being True
        running (Boolean): if true there are more steps to go in the transition
        changed (Boolean): indicates if the latest position value is different from the previous position value

    """
    # move(new_position,time_secs of move,steps in move,easing function)
    # for more into on easing, see: https://github.com/semitable/easing-functions
    # for a visual repesentation of the easing options see: http://www.emix8.org/forum/viewtopic.php?t=1063
    #
    # move from the current position
    position, running, changed = self.vs.move(new_position=new_position, time_secs=time_secs, steps=steps, easing=easing)
    if changed:  # only act if the output changed
        #print(f'Step: {self.vs.step}, Position: {position}')
        self._servo.ServoAngle(position)

    return position, running, changed

