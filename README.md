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

## First Example
### Point To Point Connection

Code (save in .cc format)<br>

```
//Point To Point Connection (Client and Server)

/*
Delay      	    = 5ms
Maximum Packets     = 10
Simulation Time     = 20sec
Maximum Packet Size = 1024 Bytes 
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SV_Example_1");

int main (int argc, char *arg[])//argument count and argument vector
{
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  NodeContainer nodes;//predefined class
  nodes.Create (2); //we need to two nodes for create 2 nodes.
  
  PointToPointHelper pointToPoint;//Predefined class
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("50Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue ("5ms"));
  
  NetDeviceContainer devices;//class
  devices = pointToPoint.Install (nodes);
  
  InternetStackHelper stack;
  stack.Install (nodes);
  
  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.255.255.0"); //this is base address, we cant use this address for nodes.
  
  Ipv4InterfaceContainer interfaces = address.Assign (devices);
  
  //Lets start making the client and server
  UdpEchoServerHelper echoServer (1234);//1234 is port number
  ApplicationContainer serverApps = echoServer.Install (nodes.Get(1));
  serverApps.Start(Seconds (1.0));
  serverApps.Stop(Seconds (20.0));
  
  UdpEchoClientHelper echoClient (interfaces.GetAddress(1), 1234);
  echoClient.SetAttribute ("MaxPackets",UintegerValue (10));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
  
  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (20.0));
  
  AnimationInterface anim("sv_eg1.xml");
  //anim.SetConstantPosition(nodes.Get (0), 10.0, 10.0);
  //anim.SetConstantPosition(nodes.Get (1), 20.0, 20.0);
  
  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll(ascii.CreateFileStream("sv_eg1.tr"));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0; 
}
```
To run the program.<br>

Open Terminal
```
cd ~/ns-allinone-3.40/ns-3.40
```
```
./ns3 run scratch/sv_eg1.cc
```
![Screenshot from 2023-10-24 13-24-56](https://github.com/vamsi-2312/Wireless_Mesh_Network_NS_3/assets/142248038/80815dde-c0ea-436f-b5cf-e71b6122ef46)

We can see the packets be exchaged.<br>

Lets the Animation.<br>
Open another terminal.<br>
```
cd ~/ns-allinone-3.40/netanim-3.109
```
```
./NetAnim
```
Then Open the .xml file, and the start the simulation.<br>
![Screenshot from 2023-10-24 13-29-29](https://github.com/vamsi-2312/Wireless_Mesh_Network_NS_3/assets/142248038/bde07d0d-f06d-4003-b24b-0a3332972e71)

Next let's check the throughput.<br>
Open another terminal
```
cd ~/tracemetrics-1.4.0
```
```
java -jar tracemetrics.jar
```
Then Tracematrics will open, open the .tr file<br>
Then execute analysis.<br>
![Screenshot from 2023-10-24 13-32-57](https://github.com/vamsi-2312/Wireless_Mesh_Network_NS_3/assets/142248038/1669fe5a-b7af-4201-9993-74567ce72411)

## Second Example
### Point to Point Network And Bus Network
code<br>
```
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

//csma - carrier sense multiple access

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SV_EXAMPLE_2");

int main (int argc, char *argv[])
{
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  NodeContainer p2pNodes;
  p2pNodes.Create (2); //2 nodes being created in Point to Point Network
  
  NodeContainer csmaNodes;
  csmaNodes.Add (p2pNodes.Get(1)); //Adding Point to Point node to CSMA Network
  csmaNodes.Create(3); //3 nodes being created in CSMA Network
  
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue ("2ms"));
  
  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);
  
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
  
  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);
  
  //Setting the IP address
  InternetStackHelper stack;
  stack.Install(p2pNodes.Get(0));
  stack.Install(csmaNodes);
  
  Ipv4AddressHelper address;
  
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);
  
  address.SetBase ("10.2.1.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);
  
  UdpEchoServerHelper echoServer (9);
  
  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get(3)); //making csma n3 as server
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));
  
  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (3),9); //(server id,port number)
  
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
  
  ApplicationContainer clientApps = echoClient.Install (p2pNodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));
  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();//class
  
  pointToPoint.EnablePcapAll ("p2p"); //pcap files will be generated.
  csma.EnablePcapAll("csma");
  
  AnimationInterface anim("sv_eg2.xml");
  anim.SetConstantPosition(p2pNodes.Get(0),10.0,10.0);
  anim.SetConstantPosition(csmaNodes.Get(0),10.0,20.0);
  anim.SetConstantPosition(csmaNodes.Get(1),20.0,30.0);
  anim.SetConstantPosition(csmaNodes.Get(2),20.0,40.0);
  anim.SetConstantPosition(csmaNodes.Get(3),20.0,50.0);
  
  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll(ascii.CreateFileStream("sv_eg2.tr"));
  
  Simulator::Run();
  Simulator::Destroy();
  return 0;
}
```

## Installing Proper Functioning Netanim(Network Animation)
```
cd
```
```
sudo apt install mercurial
```
```
hg clone http://code.nsnam.org/netanim
```
```
cd netanim
```
```
qmake Netanim.pro
```
```
make
```
```
./NetAnim
```

## Third Example
### Point to Point, CSMA and Wireless Network

code<br>
```

```
