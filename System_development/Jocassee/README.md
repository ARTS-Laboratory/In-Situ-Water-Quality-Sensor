
# Jocassee
An in situ water quality sensor for monitoring water quality

## V0.1
1. Measures pH and turbidity 
1. Saves data to SD card
1. Water-tight case 
1. This is a general dump of all the initial files. 

## V0.2
1. This is just a clean-up version of 0.1. 
1. The pads on the 1026 resistors are too small
1. move the SMA connection over.
1. Need to add a ground plane to V0.3.
1. Need to add the SMA footprint on V0.3.

## V0.3
1. New designs for PCB boards. 



## V 0.4.0
1. Includes part designs necessary to assemble the water sensor package.
2. Missing probe protector.
3. Missing Apple air tag mount.
4. Need to adjust hold positioning for Solar Flap Fixture.


## V 0.4.5 
1. Includes 2 component holders. One for TDS and pH, and another for TDS, pH, and Turbidity.
2. Includes a probe protector that prevents damage to the ends of the probes.
3. Updated solar flaps to house solar flaps wired in parallel
4. Solar Flap Fixture Cap updated to include a spot for Apple air tag
5. Updated Solar Flap Fixture. (position for holes moved, height extended, and inside tabs reduced from 4 to 2)
6. Need to make these parts out of solid plastic pieces and leak-test the package.
7. PCB Design includes RTC Module and Micro SD Card Module.
8. The PCB includes Footprints for the PH, TDS, and Turbidity Sensors.
9. Updated Arduino code to Measure the PH, TDS, and Turbidity of the water.
10. The code controls the sampling time and saves the collected data on a micro SD card.

## V 0.4.6 
1. These are general updates and a major reorganization of all the files in V0.4.5.
2. The updated PCB design includes footprints pH, Turbidity, TDS, and Temperature sensors.
3. The Updated Arduino code.
4. The Kriging Code

## V 0.4.7
1. The updated PCB design includes footprints for a GPS Module
2. Updated Arduino Code to include GPS readings
3. Added multiple designs for 3D printed Buoys
5. Added a design for a cap that includes a spot to attach an antenna
6. Included STL files and G-code for each buoy and cap.
7. Added an assembly to better size 3D printed parts for the Chassis
8. Added a Bill of Matirials

## V 0.5.0
Version of Refrence for "UAV-Deployable Sensor Nodes for Spatial and Temporal In-Situ Water Quality Monitoring and Mapping", Burnett et al. 2025
 1. Minor changes to chassis to more densly pack the sensors
 2. Minor Buoy/drop mechanism design revisions
 3. Minor changes to PCB mounting screw holes
![sensor_package_2025](https://github.com/user-attachments/assets/e8ce5730-7be3-43a4-8c8d-c7c84517157f)

## V 0.6.0
1. Updated PCB design including GPS, wireless module and latest compact signal conditioning boards for pH & TDS sensing.
2. Includes an easily dettachable solar buoy for increased operational endurance.
3. Includes waterproof connector for solar power input and battery charging from external sources.
4. Contains a BMS for effecient battery charging and load sharing.
5. Features a capless design where O'ring is used to seal the top opening.
6. Includes step files for every components used in sensor node.



















