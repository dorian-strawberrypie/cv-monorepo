using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeadRotation : MonoBehaviour
{
    private float _rVelocity = 540f;
    public bool ShouldRotate
    {
        get
        {
            if (
            (Mathf.Round(transform.localRotation.eulerAngles.z) == 0) ||
            (Mathf.Round(transform.localRotation.eulerAngles.z) == 90) ||
            (Mathf.Round(transform.localRotation.eulerAngles.z) == 180) ||
            (Mathf.Round(transform.localRotation.eulerAngles.z) == 270)
            )
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    void Start()
    {
        HeadGeom.OnBorderBump += Reverse;
    
    }
    void Update()
    {
        if (!HeadGeom.IsGrounded)// || ShouldRotate)
            Rotate(1);
        else  if (ShouldRotate)//need to get the rest to 90, 180...
        {

            //Debug.Log(Mathf.Round(transform.localRotation.eulerAngles.z));
            transform.localRotation = Quaternion.Euler(0, 0, Mathf.Round(transform.localRotation.eulerAngles.z / 90) * 90);
            //Debug.Log(Mathf.Round(transform.localRotation.eulerAngles.z));
        }

        //-parent
    }

    private void Rotate(float scale)
    {
        //transform.rotation = new Quaternion(0, 0, transform.rotation.z + _rVelocity, 0);

        transform.Rotate(0, 0, _rVelocity * scale * Time.deltaTime, Space.Self);
        //Debug.Log(transform.rotation);
        //
    }
    private void Reverse()
    {
        _rVelocity *= -1;
    }
}

