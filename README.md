# sphero-linux-api
Simple API for sphero 1&amp;2.0 written in c++

The API is (for now) built only over the bluez bluetooth stack, making it compatible with most recent linux distributions. It will NOT work on osx systems as of now.

Sphero reference doc: http://docs-beta.gosphero.com/reference/ 

! to remove before switching to public ! these are normally private documents from orbotix and should not be available (if they are public, it isn't stated anywhere ... and it wasn't that easy to "stumble" upon them)

User Hack mode reference : https://s3.amazonaws.com/docs.gosphero.com/api/Sphero_Shell_Commands_1.0.pdf

Sphero collision detection : https://s3.amazonaws.com/docs.gosphero.com/api/Collision%20detection.pdf

locator reference : https://s3.amazonaws.com/docs.gosphero.com/api/Sphero%20Locator%201.1.pdf

full api reference : https://s3.amazonaws.com/docs.gosphero.com/api/Sphero_API_1.20.pdf

full macro reference : https://s3.amazonaws.com/docs.gosphero.com/api/Sphero_Macros.pdf

orbBasic refenrence, with plenty examples : https://s3.amazonaws.com/docs.gosphero.com/api/Sphero_orbBasic.pdf



### How To build :
####1. Dependencies : 

  > dependencies are : bluez, libbluetooth, libbluetooth-dev, and libreadline6-dev libncurses5 libncurses5-dev (and of course, classic compilation tools : g++, make, gcc, clib, git, ...)

  ```sh
  $ sudo apt-get install bluez libbluetooth libbluetooth-dev git libreadline6-dev libncurses5 libncurses5-dev
  ```
  
  > some distros may have libbluetooth called libbluetooth3 and libreadline6 called libreadline, use your favorite package manager to figure out dependancies you can't install using the provided command, these are quite usual packages so they should be available for you

####2. Retrieving the source code : 

  * either download the .zip from this page and extract it
  * or clone the github repository :
 
  ```sh
  $ git clone https://github.com/slock83/sphero-linux-api.git
  ```

####3. Building the sources : 

  ```sh
  $ cd sphero-linux-api/sphero-api
  $ make
  ```
  
### Testing application

####1. Building the testing application : 

  ```sh
  $ cd example-app
  $ make
  ```

####2. Using the application

##### Running
	
still in the example-app folder, do
	
  ```sh
  $ ./sphero-cli
  ```

##### Commands

| Command | Effect | Usage |
| ----- | ----- | ----- |
help | Shows the application help |
connect | Connects to a sphero via bluetoth | connect xx:xx:xx:xx:xx |
list | Lists all available sphero | list |
select | Select which sphero you want to drive | select id |
changeColor | Changes the led color | changeColor red green blue colorPersists |
backled | Changes the back LED intensity | backled intensity |
roll | Makes the sphero roll at the specified speed and angle | roll speed angle |
ping | Sends a ping to the sphero to witch it should answer ASAP | ping |
sleep | Puts the sphero to sleep for the given amount of time, it will then wake up and we will try to connect back to him | sleep duration |
interactive | Switch to interactive driving mode | interactive |
setit | Change inactivity timeout | setit duration |
exit | Closes the application | exit |

### Graphical application

> A graphical application is also being worked on by the team ! please check out https://github.com/slock83/sphero-command-app for more details
