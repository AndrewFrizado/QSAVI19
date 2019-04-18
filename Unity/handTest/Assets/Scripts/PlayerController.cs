using UnityEngine;

public class PlayerController : MonoBehaviour
{

    #region "Variables"
    public Rigidbody Rigid;
    public float MouseSensitivity = 5f;
    public float MoveSpeed;
    public float JumpForce = 40;
    #endregion

    private void Start()
    {
        Rigid = GetComponent<Rigidbody>();
        Cursor.lockState = CursorLockMode.Locked;
    }
    void FixedUpdate()
    {
        Rigid.MoveRotation(Rigid.rotation * Quaternion.Euler(new Vector3(0, Input.GetAxis("Mouse X") * MouseSensitivity, 0)));
        Rigid.MovePosition(transform.position + (transform.forward * Input.GetAxis("Vertical") * MoveSpeed) + (transform.right * Input.GetAxis("Horizontal") * MoveSpeed));
        if (Input.GetKeyDown("space"))
            Rigid.AddForce(transform.up * JumpForce);

        if (Input.GetKeyDown("escape")) {
            Cursor.lockState = CursorLockMode.None;
        }
    }
}