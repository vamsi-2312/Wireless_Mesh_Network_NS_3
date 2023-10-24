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
