using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class DeathClass : MonoBehaviour
{
    public DeathClass()
    {
        SceneManager.LoadScene("KoMenu", LoadSceneMode.Additive);
        Time.timeScale = 0;
    }
}
public class KoUI : MonoBehaviour
{

    public static bool IsDead;
    private int _activeSceneId;

    public static string ScoreSaveName;
    private int _savedScore;
    public static int Score;

    public TextMeshProUGUI LevelTextGO;
    public GameObject ScoreTextGO;
    public GameObject HighestScoreTextGO;
    public GameObject ContinueBtn;
    public GameObject KeepGoingBtn;
    //public UnityEvent OnContinue;
    //public GameManager GMInstance;
    public static bool CanKeepGoing = true;

    
    public RewardedAd1 RewardedAKeepGoing;
    public BreakAd TimedBreakAd; //prefab to GUI -> to load
    public static GameObject ThisGO;
    void OnEnable()
    {

        ThisGO = gameObject;
        _activeSceneId = SceneManager.GetActiveScene().buildIndex;
        _savedScore = PlayerPrefs.GetInt(ScoreSaveName);
        if (Score > _savedScore)
        {
            PlayerPrefs.SetInt(ScoreSaveName, Score);
        }

        LevelTextGO.text = "Level " + GameManager.Level;
        ScoreTextGO.GetComponent<TextMeshProUGUI>().text = Score.ToString("0");
        HighestScoreTextGO.GetComponent<TextMeshProUGUI>().text = "Highest: " + _savedScore.ToString("0");

        if (IsDead)
        {
            KeepGoingBtn.SetActive(CanKeepGoing);
            ContinueBtn.SetActive(false);

            if (TimedBreakAd.interstitial != null && TimedBreakAd.interstitial.IsLoaded())
            {
                TimedBreakAd.ShowBreakAd();
            }
        }
        else
        {
            ContinueBtn.SetActive(true);
            KeepGoingBtn.SetActive(false);
        }
    }

    public void BtnClicked(int btn)
    {
        switch (btn)
        {
            case 1: //continue
                GameManager.IsPaused = false;
                Time.timeScale = 1;
                break;
            case 2: //keep going
                //Ad -> timescale -> IEnumerator for inactive col
                RewardedAd1.RewardId = 0;
                RewardedAKeepGoing.UserChoseToWatchAd();
                break;
            case 3: //retry
                SceneManager.LoadScene(_activeSceneId);
                Time.timeScale = 1;
                break;
            case 4: //menu
                SceneManager.LoadScene(0);
                Time.timeScale = 1;
                SceneManager.UnloadSceneAsync(SceneManager.GetActiveScene());
                break;

            default:
                break;
        }
    }
}

