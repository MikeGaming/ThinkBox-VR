using UnityEngine;
public class MessageListener : MonoBehaviour
{

    SerialController controller;

    // Use this for initialization
    void Start()
    {
        controller = GetComponent<SerialController>();
    }
    // Update is called once per frame
    void Update()
    {


    }
    // Invoked when a line of data is received from the serial device.
    void OnMessageArrived(string msg)
    {
        Debug.Log("Arrived: " + msg);
    }
    // Invoked when a connect/disconnect event occurs. The parameter 'success'
    // will be 'true' upon connection, and 'false' upon disconnection or
    // failure to connect.
    void OnConnectionEvent(bool success)
    {
        Debug.Log(success ? "Device connected" : "Device disconnected");
    }

    void SendColourData(int led, int colour)
    {
        //1 = red, 2 = green, 3 = blue
        string message = "" + led + colour;
        Debug.Log("Sending: " + message);
        controller.SendSerialMessage(message);
    }
}