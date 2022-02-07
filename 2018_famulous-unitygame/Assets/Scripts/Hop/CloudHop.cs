using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.Rendering.LWRP;

public class CloudHop : BoardHop
{
    public GameObject Particles;
    public SpriteRenderer SprRen;
    public void Destruction()
    {
        Particles.SetActive(true);
        SprRen.enabled = false;
        GetComponentInChildren<Light2D>().enabled = false;
        Destroy(this.gameObject, 0.5f);
    }
}
