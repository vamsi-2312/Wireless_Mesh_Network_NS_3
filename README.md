# Wireless Mesh Network Using NS-3 

In this Repo we are going see how to create a Wireless Mesh Network in NS-3.<br>

NS-3 (Network Simulator - 3)<br>
It is free and open source tool.<br>

Vist this link for more information.<br>
https://www.nsnam.org/

# Installation

We will be creating a ubuntu (22.04) Virtual Machine, and then installing NS-3 in it.<br>

Install the Ubuntu ISO image.<br>
https://ubuntu.com/download/desktop

Setting up ubuntu Virtual Machine<br>
https://www.youtube.com/watch?v=rJ9ysibH768

## Installing NS-3

```
sudo apt update
```
```
sudo apt install build-essential autoconf automake libxmu-dev
```
```
sudo apt install g++ python3 cmake ninja-build git gir1.2-goocanvas-2.0 python3-gi python3-gi-cairo python3-pygraphviz gir1.2-gtk-3.0 ipython3 tcpdump wireshark sqlite sqlite3 libsqlite3-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools openmpi-bin openmpi-common openmpi-doc libopenmpi-dev doxygen graphviz imagemagick python3-sphinx dia imagemagick texlive dvipng latexmk texlive-extra-utils texlive-latex-extra texlive-font-utils libeigen3-dev gsl-bin libgsl-dev libgslcblas0 libxml2 libxml2-dev libgtk-3-dev lxc-utils lxc-templates vtun uml-utilities ebtables bridge-utils libxml2 libxml2-dev libboost-all-dev 
```

After that download the .tar file for NS-3 from the following link https://www.nsnam.org/releases/ns-allinone-3.40.tar.bz2<br>
Then unzip the .tar file into howe folder.<br>

```
cd ns-allinone-3.40
```
```
./build.py --enable-examples --enable-tests 
```
Installation finished.<br>

Testing NS-3
```
cd ns-3.40
```
```
./ns3 run hello-simulator
```
