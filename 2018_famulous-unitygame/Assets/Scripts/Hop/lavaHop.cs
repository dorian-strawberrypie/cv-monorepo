using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lavaHop : MonoBehaviour
{
    public static Animator Animator;
    private void Start()
    {
        Animator = GetComponent<Animator>();
        Animator.enabled = false;
    }
}
