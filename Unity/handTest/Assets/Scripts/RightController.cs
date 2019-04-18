using UnityEngine;
using System.Collections;

public class RightController : MonoBehaviour
{

    public GameObject camera;
    public float speed = 10;
    public bool canHold = true;
    public GameObject pickup;
    public Transform guide;

    void Start()
    {
        camera = GameObject.Find("Camera");
        guide = this.transform;
    }

    void LateUpdate()
    {   
        Vector3 forDir = camera.transform.up;
        Vector3 backDir = -camera.transform.up;
        Vector3 rightDir = camera.transform.right;
        Vector3 leftDir = -camera.transform.right;

        forDir.x = transform.position.x;
        backDir.x = transform.position.x;
        rightDir.x = transform.position.x;
        leftDir.x = transform.position.x;

        forDir.Normalize();
        backDir.Normalize();
        leftDir.Normalize();
        rightDir.Normalize();

        if (Input.GetKeyDown("i"))
            transform.Translate(forDir * 2 * Time.deltaTime);

        if (Input.GetKeyDown("j"))
            transform.Translate(leftDir * 2 * Time.deltaTime);

        if (Input.GetKeyDown("l"))
            transform.Translate(rightDir * 2 * Time.deltaTime);

        if (Input.GetKeyDown("k"))
            transform.Translate(backDir * 2 * Time.deltaTime);

        if (Input.GetKeyDown("m"))
        {
            if (!canHold)
                throw_drop();
            else
                Pickup();
        }
        if (!canHold && pickup)
            pickup.transform.position = guide.position;

    }
    void OnCollisionEnter(Collision col)
    {
        Debug.Log(col.gameObject.tag);
        if (col.gameObject.tag == "Pickup")
            if (!pickup) 
               pickup = col.gameObject;
    }


    private void Pickup()
    {
        if (!pickup)
            return;

        Debug.Log("Pickup Attempt");
        pickup.transform.SetParent(guide);
        pickup.GetComponent<Rigidbody>().useGravity = false;
        pickup.transform.localRotation = transform.rotation;
        pickup.transform.position = guide.position;
        canHold = false;
    }

    private void throw_drop()
    {
        if (!pickup)
            return;
        pickup.GetComponent<Rigidbody>().useGravity = true;
        pickup = null;
        guide.GetChild(0).gameObject.GetComponent<Rigidbody>().velocity = transform.forward * speed;
        guide.GetChild(0).parent = null;
        canHold = true;
    }
}