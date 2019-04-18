 using UnityEngine;
using System.Collections;

public class HandPhysicsControllerInput : MonoBehaviour
{
    private HandPhysicsController _handController;

	void Start ()
	{
	    _handController = GetComponent<HandPhysicsController>();
	}

	void Update () 
    {
        //Enable or disable control
	    if (Input.GetKeyDown(KeyCode.C))
	        _handController.EnableControl = !_handController.EnableControl;

        //Bend or unbend all fingers
        if (Input.GetMouseButtonDown(0))
        {
            _handController.BendAllFingers();
        }
        if (Input.GetMouseButtonUp(0))
        {
            _handController.UnbendAllFingers();
        }

        //Bend or unbend one specific finger
        if (Input.GetKeyDown(KeyCode.H))
            _handController.BendFinger(FingersType.Pinky);
        if (Input.GetKeyDown(KeyCode.J))
            _handController.BendFinger(FingersType.Ring);
        if (Input.GetKeyDown(KeyCode.K))
            _handController.BendFinger(FingersType.Middle);
        if (Input.GetKeyDown(KeyCode.L))
            _handController.BendFinger(FingersType.Index);
        if (Input.GetKeyDown(KeyCode.B))
            _handController.BendFinger(FingersType.Thumb);

        if (Input.GetKeyUp(KeyCode.H))
            _handController.UnbendFinger(FingersType.Pinky);
        if (Input.GetKeyUp(KeyCode.J))
            _handController.UnbendFinger(FingersType.Ring);
        if (Input.GetKeyUp(KeyCode.K))
            _handController.UnbendFinger(FingersType.Middle);
        if (Input.GetKeyUp(KeyCode.L))
            _handController.UnbendFinger(FingersType.Index);
        if (Input.GetKeyUp(KeyCode.B))
            _handController.UnbendFinger(FingersType.Thumb);
        /*
        //Rotate forearm and wrist
        if (Input.GetMouseButton(1))
        {
            _handController.RotateForearm(Input.GetAxis("Mouse X"));
            _handController.RotateWrist(Input.GetAxis("Mouse Y"));
        }

        //Move forearm
        else _handController.MoveForearm(new Vector3(Input.GetAxis("Mouse X"), Input.GetAxis("Mouse ScrollWheel"), Input.GetAxis("Mouse Y")));
        */
	}
}
