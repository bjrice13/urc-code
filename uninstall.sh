#!/bin/bash
oformat=\e[93m\e[1m\e[4m
clearformat=\e[0m
CATKIN=~/catkin_ws/
ntoinstall=0


echo This script will uninstall dependencies needed to successfully run
echo SDRC software with ROS.
echo
echo -e "\e[93m\e[1m\e[4mDo you wish to uninstall the following dependencies:\e[0m"

if [  -d "$CATKIN/src/roboteq" ]; then
printf "\troboteq_driver\n"
let "ntoinstall++"
fi
if [  -d "$CATKIN/src/serial" ]; then
printf "\tserial\n"
let "ntoinstall++"
fi
#printf "\n\tar_track_alvar"
if [  -d "$CATKIN/src/joystick_drivers" ]; then
printf "\tjoy\n"
let "ntoinstall++"
fi
if  dpkg -l | grep -qw libspnav-dev; then
  printf "\tlibspnav-dev\n"
  let "ntoinstall++"
fi
if  dpkg -l | grep -qw libbluetooth-dev; then
  printf "\tlibbluetooth-dev\n"
  let "ntoinstall++"
fi
if  dpkg -l | grep -qw libcwiid-dev; then
  printf "\tlibcwiid-dev\n"
  let "ntoinstall++"
fi
if  dpkg -l | grep -qw libusb-dev; then
  printf "\tlibusb-dev\n"
  let "ntoinstall++"
fi

if [ $ntoinstall == 0 ]; then
  echo -e "\e[1m\nNo installed dependencies found! Exiting..."
  exit 0
fi

read -p 'y/n: ' continue

if [ $continue = "y" ] || [ $continue = "Y" ] || [ $continue = "yes" ] || [ $continue = "Yes" ]
then

  if [ ! -d "$CATKIN/src" ]; then
    echo "\n\e[93m\e[1mERROR: Cannot locate catkin workspace!"
    echo "Make sure it is set up at $CATKIN"
    exit 1
  fi

  if [ -d "$CATKIN/src/roboteq" ]; then
    echo -e "\e[93m\e[4mDeleting roboteq_driver\e[0m"
    rm -rf $CATKIN/src/roboteq/
    echo
  fi

  if [ -d "$CATKIN/src/serial" ]; then
    echo -e "\e[93m\e[4mDeleting serial:\e[0m"
    rm -rf $CATKIN/src/serial/
    echo
  fi

  if [ -d "$CATKIN/src/joystick_drivers" ]; then
    echo -e "\e[93m\e[4mDeleting joy:\e[0m"
    rm -rf $CATKIN/src/joystick_drivers/
    echo
  fi

  echo -e "\e[93m\e[4mUninstalling libspnav-dev:\e[0m"
  echo apt-get purge -y libspnav-dev
  sudo apt-get purge -y libspnav-dev
  echo
  echo -e "\e[93m\e[4mUninstalling libbluetooth-dev:\e[0m"
  echo apt-get purge -y libbluetooth-dev
  sudo apt-get purge -y libbluetooth-dev
  echo
  echo -e "\e[93m\e[4mUninstalling libcwiid-dev:\e[0m"
  echo apt-get purge -y libcwiid-dev
  sudo apt-get purge -y libcwiid-dev
  echo
  echo -e "\e[93m\e[4mUninstalling libusb-dev:\e[0m"
  echo apt-get purge -y libusb-dev
  sudo apt-get purge -y libusb-dev

  echo
  echo Successfully uninstalled all dependencies!
fi
