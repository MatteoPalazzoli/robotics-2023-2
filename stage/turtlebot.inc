define kinect ranger
(
  sensor
  (
    pose [ 0.0 0.0 0.0 0.0 ]
    size [0.1 0.1 0.1 ]
    range  [0 6.5]
    fov 120.0
    samples 640
  )
  
  color "black"
  size [ 0.06 0.15 0.03 ]
)

define mybot position
(
  pose [ 0.0 0.0 0.0 0.0 ]
  localization "odom"
  odom_error [0.03 0.03 0.00 0.05]
  size [ 0.6 0.4 0.1 ]
  origin [ 0.0 0.0 0.0 0.0 ]
  #velocity_bounds [ xmin xmax ymin ymax zmin zmax amin amax ] x,y,z in meters per second, a in degrees per second
  velocity_bounds [-0.45 0.45 0 0 0 0 -57.32 57.32 ]					
  acceleration_bounds [-2.5 2.5 -2.5 2.5 -0 0 -183.44 183.44]
  gui_nose 1
  drive "diff"
  kinect()
)
