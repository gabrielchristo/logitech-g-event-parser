using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using UnityEngine;


[StructLayout(LayoutKind.Sequential, Pack = 1)]
public struct gunnerController{
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte up;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte down;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte left;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte right;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
    public byte fire;
}

public class Cannon : MonoBehaviour
{

    public GameObject cannonTurret;
    public GameObject cannonBarrel;
    public GameObject muzzle;

    public GameObject bulletObject;

    public gunnerController gc;

    static UdpClient _udp;
    Thread _thread;


    void Start(){

        // data struct
        gc = new gunnerController();

        // socket thread
        _thread = new Thread(new ThreadStart(getGunnerInput)); 
        _thread.Start();

    }


    void Update()
    {

        if(gc.left == 1){
            cannonTurret.transform.Rotate(0, -2f, 0, Space.Self);
        }

        else if(gc.right == 1){
            cannonTurret.transform.Rotate(0, 2f, 0, Space.Self);
        }

        else if(gc.up == 1){    
            cannonBarrel.transform.Rotate(-2f, 0, 0, Space.Self);
        }

        else if(gc.down == 1){    
            cannonBarrel.transform.Rotate(2f, 0, 0, Space.Self);
        }

        else if(gc.fire == 1){    
            Launch();
        }

        Debug.Log(cannonBarrel.transform.rotation.x + "-" + cannonBarrel.transform.rotation.y + "-" + cannonBarrel.transform.rotation.z);
        

    }

    void Launch(){

        // instance of bullet
        GameObject bullet = Instantiate(bulletObject, muzzle.transform.position, cannonBarrel.transform.rotation);

        // applying force
        bullet.GetComponent<Rigidbody>().AddRelativeForce(cannonBarrel.transform.forward * -2000);
        //bullet.GetComponent<Rigidbody>().velocity = cannonBarrel.transform.TransformDirection(cannonBarrel.transform.forward * -40);

        // destroying bullet and his rigid body in 3 seconds 
        Destroy(bullet.GetComponent<Rigidbody>(), 3);
        Destroy(bullet, 3);

        
    }

    void getGunnerInput(){ 

        _udp = new UdpClient(5001);

         while(true){

            IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5001);
			byte[] receiveBytes = _udp.Receive(ref RemoteIpEndPoint);
            this.deserialize(receiveBytes);

         }

    }

    // setting received byte stream to data strucuture
    void deserialize(byte[] stream){
        gc.up = stream[0];
        gc.down = stream[1];
        gc.left = stream[2];
        gc.right = stream[3];
        gc.fire = stream[4];
    }


}
