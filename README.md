# Slackers_Platform
Want instant communication with the Dev team? Join our
[Discord Channel](https://discord.gg/VN7ZuWR)!

## Release 2.01
### What needs to change:
- All config.txt files will need to be updated with new image files.  The format is now:
	AI <AI Name> <x> <y> <Up Image> <Right Image> <Down Image> <Left Image> <Bullet Image>
	All images follow this format:
	images/<color>/tank<ColorLetter>_<direction>.png
	images/<color>/bullet<ColorLetter>.png
	For the blue tank:
		images/Blue/tankB_U.png 
		images/Blue/tankB_R.png 
		images/Blue/tankB_D.png 
		images/Blue/tankB_L.png 
		images/Blue/bulletB.png

### What's New?
- Radar
	- The Radar stat is what determines how far around the tank it can see.  If you 
		have a Radar stat of 2, you will only be able to see objects 2 spaces away from 
		you.
- Random Objects
	- The platform will now select from a pool of objects during object placement on
		the map.  The current two options are:  Tree, or Rock.
- Map Scaling
	- The map size can now be changed in the configuration settings between 15x9 to 
		40 x 20
- Idle Speed Adjustment
	- The idle speed can be changed within the configuration file.  Currently, this will
		only affect the time between turns.
- Restructuring of Images
	- Added two new colors for tanks and projectiles.  And restructured them based on their 
	affiliated color.
	- Restructured Objects into folders based on type

### Fixes
- Deconstructor is now called for custom tanks instead of relying on the parent.
- Changed configuration file to account for Radar instead of Range.
- Tanks are now limited to only pending the allowed number of attribute points.
- You will no longer get a message for an incorrect number of attribute points spent
	if you were within the limit.

## Release 1.04
### Whats New?
- Added checks for tanks cheating and adding too many attributes points to their
stats

## Release 1.03
### What's New?
- A new example tank has been added to show the basics of movment and shooting
- Fixed Bugs associated to parsing the config file,
    - The config file can now load up to 4 tanks
    - The config file also now error checking so invalid options are ignored and
set to defaults
- Improved the effeciency of the game manager so tank moves process faster
