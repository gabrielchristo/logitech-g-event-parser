using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;
using UnityEngine;
using UnityStandardAssets.Vehicles.Car;

public class SteeringWheelInputParser : MonoBehaviour
{
    static UdpClient _udp;
    Thread _thread;
    public string _bufferData = "";
    CarController _car;

    public struct SteeringWheelData{
        public float steeringWheelAngle;
        public short throttle;
        public short brake;
        public short clutch;
    }

    void Start()
    {
        Debug.Log("Logitech G920 Sandbox");

        _thread = new Thread(new ThreadStart(ThreadMethod)); 
        _thread.Start();

        _car = this.GetComponent<CarController>();
    }

    void ThreadMethod(){
         
         _udp = new UdpClient(5000);

         while(true){

            IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5000);
			byte[] receiveBytes = _udp.Receive(ref RemoteIpEndPoint);
			_bufferData = Encoding.ASCII.GetString(receiveBytes);

         }
       
    }

    void FixedUpdate(){

        if(_bufferData != "") _car.updateWheelAngle(_bufferData);

    }

    void OnApplicationQuit(){
        _udp.Close();
    }

}