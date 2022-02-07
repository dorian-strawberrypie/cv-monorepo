using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static bool IsPaused;
    //public GameObject GameplayUIGO;
    public GameplayUI GPUI;
    public float Score = 1;
    public AudioManager AudioManager;
    public Animator ScoreAnimator;

    public TextMeshProUGUI _scoreText; 
    int increment = 0;
    public static int Level;

    public delegate void KeepGoingActivatedEventHandler();
    public static event KeepGoingActivatedEventHandler KeepGoingActivated;
    protected void Start()
    {
        GPUI = GameObject.Find("GameplayUI").GetComponent<GameplayUI>();
        AudioManager = GameObject.Find("AudioManager").GetComponent<AudioManager>();
        ScoreAnimator = GameObject.Find("scorePlus").GetComponent<Animator>();
        KoUI.CanKeepGoing = true;
    }
    protected void PauseGame(bool death)
    {
        KoUI.Score = Mathf.RoundToInt(Score);
        KoUI.IsDead = death;

        if (death)
            StartCoroutine(IPause());
        else
        {
            GPUI.Pause();
            Time.timeScale = 0;
        }
    }
    IEnumerator IPause()
    {
        while (increment < 1f)
        {
            increment++;
            yield return new WaitForSeconds(1f);
        }

        Time.timeScale = 0;
        if (!GPUI)
        {
            Debug.LogWarning("No GPUI found  - GameManager.cs 49");
            GPUI = GameObject.Find("GameplayUI").GetComponent<GameplayUI>();
        }

        GPUI.Pause();
    }

    public virtual void KeepGoing()
    {
        GPUI.Pause();

        var head = GameObject.Find("Head").GetComponent<HeadBase>();
        head.KeepGoing();

        
        //if (died from fall) -> save stair position, spawn here, countdown.... else -> collider
    }
}
