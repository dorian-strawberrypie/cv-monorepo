using System;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public static AudioManager Instance;
    public Sound[] Sounds;
    private void Awake()
    {
        Instance = this;
        foreach (var sound in Sounds)
        {
            sound.Source = gameObject.AddComponent<AudioSource>();
            sound.Source.clip = sound.Clip;
            sound.Source.volume = sound.Volume;
        }    
    }
    public void Play(string soundName)
    {
        Sound s = Array.Find<Sound>(Sounds, sound => sound.Name == soundName);
        if (!s.Source.isPlaying)
            s.Source.Play();
    }
}
