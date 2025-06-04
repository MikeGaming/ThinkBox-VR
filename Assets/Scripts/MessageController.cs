using System.Globalization;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;
public class MessageController : MonoBehaviour
{

    public SerialController controller;

    [SerializeField] CubeController cubeController;
    [SerializeField] SymbolAnswer symbolAnswer;

    // Use this for initialization
    void Start()
    {
        controller = GameObject.Find("SerialController").GetComponent<SerialController>();
    }
    // Update is called once per frame
    void Update()
    {

        //---------------------------------------------------------------------
        // Receive data
        //---------------------------------------------------------------------

        string message = controller.ReadSerialMessage();

        if (message == null)
            return;

        // Check if the message is plain data or a connect/disconnect event.
        if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_CONNECTED))
            Debug.Log("Connection established");
        else if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_DISCONNECTED))
            Debug.Log("Connection attempt failed or disconnection detected");
        else
            Debug.Log("Message arrived: " + message);
        if (message.StartsWith("%"))
        {
            message.Trim();
            message = message.Substring(1);
            cubeController.lastMessage_array = message;
            Debug.Log("Arrived: " + message);
        }
        if (message.StartsWith("#"))
        {
            message.Trim();
            message = message.Substring(1);
            symbolAnswer.lastMessage_symbol = message;
            Debug.Log("Arrived: " + message);
        }
        if (message.StartsWith("&"))
        {
            message = message.Substring(1);
            var strings = message.Split(",");
            strings.ToList();
            cubeController.quaternion = new Vector4(float.Parse(strings[0], CultureInfo.InvariantCulture.NumberFormat), float.Parse(strings[1], CultureInfo.InvariantCulture.NumberFormat), float.Parse(strings[2], CultureInfo.InvariantCulture.NumberFormat), float.Parse(strings[3], CultureInfo.InvariantCulture.NumberFormat));
            Debug.Log("Arrived: " + message);
        }
    }

    public void SendTextData(string texts)
    {
        Debug.Log("Sending: " + texts);
        controller.SendSerialMessage(texts);
    }
}