# sphero-linux-api
Simple API for sphero 1&amp;2.0 written in c++

The API is (for now) built only over the bluez bluetooth stack, making it compatible with most recent linux distributions. It will NOT work on osx systems as of now.

### How To build :
1. Dependencies : 

  > dependencies are : bluez, libbluetooth, and libbluetooth-dev (and of course, classic compilation tools : g++, make, gcc, clib, git, ...)

  ```sh
  $ sudo apt-get install bluez libbluetooth libbluetooth-dev git
  ```

2. Retrieving the source code : 

  * either download the .zip from this page and extract it
  * or clone the github repository :
 
  ```sh
  $ git clone https://github.com/slock83/sphero-linux-api.git
  ```

3. Building the sources : 

  ```sh
  $ cd sphero-linux-api/sphero-api
  $ make
  ```