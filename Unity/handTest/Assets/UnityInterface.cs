using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class PongTest : MonoBehaviour
{
    // ------------------------- CONSTANT SERIAL PORT DATA -------------------------

    [Header("COM Port")]
    public string setCOMPort = "\\\\.\\COM7";
    public int setCOMBaud = 115200;

    public static string COM_PORT;
    public static int COM_BAUD;

    // ------------------------- CONSTANT TIMING DATA -------------------------

    [Header("Timing")]
    public float setSerialPortRefreshPeriod = 0.01f; // Seconds
    public float setSerialPortRequestDelayPeriod = 0.0005f; // Seconds

    // ------------------------- SERIAL PORT -------------------------

    private SerialPort stream;

    // ------------------------- Initialize -------------------------
    void Start()
    {
        //Initial Port
        stream = new SerialPort(setCOMPort, setCOMBaud);
        stream.ReadTimeout = 50;
        stream.Open();
        //Check if serial open
        if (stream.IsOpen)
        {
            Debug.Log("Opened");
        }
        else
        {
            Debug.Log("Failed");
        }

        StartCoroutine
        (
            ReadArduino
            ((string datastring) => CommandHandler(datastring),
                () => Debug.LogError("Error!"),
                setSerialPortRefreshPeriod
            )
        );
    }

    void CommandHandler(string message)
    {
        //Message format fingernum/resistance eg: 1,4
        string[] parsed = message.Split(',');
        int finger = 0;
        int resistance = 0;
        Debug.Log(message);
        /*
        if (parsed.Length == 1 && Int32.TryParse(parsed[0], out finger))
        {
            Debug.Log("Finger: " + finger);
        }
        else
        {
            Debug.Log("Invalid Data");
            return;
        }
        if (Int32.TryParse(parsed[1], out resistance))
        {
            Debug.Log("Resistance: " + resistance);
        }
        else
        {
            Debug.Log("Invalid Data");
            return;
        }*/
    }

    void WriteArduino(string message)
    {
        stream.WriteLine(message);
        stream.BaseStream.Flush();
    }

    IEnumerator ReadArduino(Action<string> callback, Action fail = null, float timeout = float.PositiveInfinity)
    {
        stream.Write("PING");
        yield return new WaitForSeconds(setSerialPortRequestDelayPeriod);

        DateTime initialTime = DateTime.Now;
        DateTime nowTime;
        TimeSpan diff = default(TimeSpan);
        string dataString = null;
        do
        {
            try
            {
                dataString = stream.ReadLine();
            }
            catch (TimeoutException)
            {
                dataString = null;
            }
            if (dataString != null)
            {
                callback(dataString);
                yield break;
            }
            else
                yield return null;
            nowTime = DateTime.Now;
            diff = nowTime - initialTime;
        } while (diff.Milliseconds < timeout);

        if (fail != null)
            fail();
        yield return null;
            
        StartCoroutine
        (
            ReadArduino
            ((string datastring) => CommandHandler(datastring),
                () => Debug.LogError("Error!"),
                setSerialPortRefreshPeriod
            )
        );
    }

}



