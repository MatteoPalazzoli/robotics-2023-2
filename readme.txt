# project 2
## node/plugins used for mapping
- tf_publisher, that is the node requested  
- pointcloud_to_laserscan, used to convert the velodyne points to planar laser points  
- slam_toolbox, used for the mapping process both in the 2D and 3D cases.  
- rviz, used for visualization  

## node/plugins used for navigation
For the navigation process, we set up a navigation stack according to the turotial specified on the official wiki: http://wiki.ros.org/navigation/Tutorials/RobotSetup, starting a move_base node.  
- cost map: costmap_2d
- Plugins: costmap_2d::StaticLayer, costmap_2d::ObstacleLayer, costmap_2d::InflationLayer
- Local planner: (default) base_local_planner/TrajectoryPlannerROS  
- Global planner: (default) navfn/NavfnROS  
   
Other nodes are:  
- map_server: provides the map  
- stage_ros: used to setup the simulation  
- navigation: our node that reads the CSV and publishes the goals  
- amcl: localization  
- RViz: to view the robot and the map.  