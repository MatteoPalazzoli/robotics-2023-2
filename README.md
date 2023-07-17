# robotics-2023-2
Robotics second project academic year 2022/2023 at PoliMi.  
Grade: **3/3**  
## Data
Two bags of a skid-steering robot (footprint: 0.4 x 0.6). Topics:  
- /scan: data from a single plane scanner
- /t265/odom: odometry data from sensor t265
- /velodyne_points: 3d laser scans from Velodyne sensor
- /tf_static: some static tf
## Part 1 - mapping
Create a package "second_project". Inside, create a node "tf_publisher" that performs the conversion from odometry to tf.  
Create a map from the data in two ways: the first with laser data, and the second with LiDAR data (convert to laserscans). Use both bag files, in order to produce 4 maps in total.
## Part 2 - navigation
Navigae the map created. Clean the map from noisy points, create and setup a stage simulation and create a node "navigation" that reads some waypoints and publishes them as a goal, one after another. Pseudocode:  
```
for i in range(N) :
  1. read goal i
  2. publish goal i
  3. wait for result
  4. get result
```
Waypoints format: `x,y,heading` (assuming heading is in degrees)
