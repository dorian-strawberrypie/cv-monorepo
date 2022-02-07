using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Sound
{
    public string Name;
    [Range(0f,1f)]
    public float Volume;
    public AudioClip Clip;
    [HideInInspector]
    public AudioSource Source;
}
