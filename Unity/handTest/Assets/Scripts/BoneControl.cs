using UnityEngine;
using System.Collections;

public class BoneControl : MonoBehaviour
{

    public Transform bone;

    void Start()
    {
        bone = GetComponent<Transform>().Find("Bone_001");
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            GetComponent<Animation>().Play("animation1");
        }
    }
    void LateUpdate()
    {
        if (Input.GetKeyDown(KeyCode.B))
        {
            if (bone != null)
            {
                bone.eulerAngles = new Vector3(0, 0, 90);
            }
            else
            {
                Debug.Log("bone is null!");
            }

        }

    }
}