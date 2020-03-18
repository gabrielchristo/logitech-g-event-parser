using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;
using System;
using UnityEngine;
using UnityStandardAssets.Vehicles.Car;


[StructLayout(LayoutKind.Sequential, Pack = 1)]
public struct SteeringWheelData{
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public Single steeringWheelAngle;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public Single throttle;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public Single brake;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public Single clutch;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte lps;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte rps;
}

public class SteeringWheelInputParser : MonoBehaviour
{
    static UdpClient _udp;
    Thread _thread;
    public CarController _car;
    public SteeringWheelData data;

    void Start()
    {
        //Debug.Log("Logitech G920 Sandbox");

        _thread = new Thread(new ThreadStart(ThreadMethod)); 
        _thread.Start();

        //_car = this.GetComponent<CarController>();

        data = new SteeringWheelData();
    }

    void ThreadMethod(){
         
         _udp = new UdpClient(5000);

         while(true){

            IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5000);
			byte[] receiveBytes = _udp.Receive(ref RemoteIpEndPoint);
            this.deserialize(receiveBytes);

            //Debug.Log(BitConverter.ToString(receiveBytes, 0));

         }
       
    }

    // updating values on car controller
    void Update(){
        if(_car != null) _car.updateValues(data.steeringWheelAngle, data.throttle, data.brake, data.clutch);
    }

    // close udp server socket on exit
    void OnApplicationQuit(){
        _udp.Close();
    }

    void deserialize(byte[] stream){

        this.data.steeringWheelAngle = BitConverter.ToSingle(stream, 0);
        this.data.throttle = BitConverter.ToSingle(stream, 4);
        this.data.brake = BitConverter.ToSingle(stream, 8);
        this.data.clutch = BitConverter.ToSingle(stream, 12);
        this.data.lps = stream[16];
        this.data.rps = stream[17];

        //Debug.Log("Angle:"+data.steeringWheelAngle+" Acel:"+data.throttle+" Brake:"+data.brake+" Clutch:"+data.clutch+" lps:"+data.lps+" rps:"+ data.rps);
        

    }
}

