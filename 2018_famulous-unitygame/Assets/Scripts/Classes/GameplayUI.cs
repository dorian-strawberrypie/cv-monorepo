using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameplayUI : MonoBehaviour
{

    public KoUI KoUIScript;
    public GameObject KoUIGO;
    public GameObject PauseBtn;
    public GameObject Fader;
    private Image _faderImg;
    public TextMeshProUGUI LevelIndicator;
    public TextMeshProUGUI ScorePlus;
    private void Start()
    {
        KoUIScript = KoUIGO.GetComponent<KoUI>();
        KoUIScript.enabled = false;

        _faderImg = Fader.GetComponent<Image>();
        _faderImg.color = new Color(1,1,1,1);
        StartCoroutine(FadeIn());
    }
    public void Pause()
    {
        KoUIGO.SetActive(KoUIGO.activeInHierarchy ? false : true);
        PauseBtn.SetActive(PauseBtn.activeInHierarchy ? false : true);
        KoUIScript.enabled = KoUIScript.enabled ? false : true; //true;
        //GameManager.IsPaused = !GameManager.IsPaused;
        
    }
    IEnumerator FadeIn()
    {

        while (_faderImg.color.a > 0)
        {
            _faderImg.color = new Color(_faderImg.color.r, _faderImg.color.g, _faderImg.color.b, _faderImg.color.a - 2 * Time.deltaTime);
            yield return null;
        }
        
        Fader.SetActive(false);
    }
    public IEnumerator NextLevel()
    {

        Fader.SetActive(true);
        LevelIndicator.gameObject.SetActive(true);
        LevelIndicator.text = "Level " + (GameManager.Level + 1);
        while (_faderImg.color.a < 1)
        {
            _faderImg.color = new Color(_faderImg.color.r, _faderImg.color.g, _faderImg.color.b, _faderImg.color.a + 2 * Time.deltaTime);
            yield return null;
        }
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        
        //StartCoroutine(FadeIn());
    }
    //IEnumerator NextLevel()
    //{
    //    //PlayerPrefs.SetInt("GeomLevel", GeomManager.Instance.Level + 1);
    //}
}
