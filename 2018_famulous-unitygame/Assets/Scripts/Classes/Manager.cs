using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Manager : MonoBehaviour
{
    public static Sprite HeadSprite;
    public static string ActiveMenuList;
    public GameObject BackButton;

    private BackBtn _backBtnScript;
    public List<GameObject> MenuLists;

    public GameObject Fader;
    private Image _faderImg;
    void Start()
    {
        GoogleMobileAds.Api.MobileAds.Initialize(initStatus => { });
        ActiveMenuList = "heads";
        _backBtnScript = BackButton.GetComponent<BackBtn>();
        _faderImg = Fader.GetComponent<Image>();
        Resources.UnloadUnusedAssets();
    }
    public void OnHeadClick()
    {
        ActiveMenuList = "games";
        HeadSprite = ChosenCollider.ChoosedHeadMini.GetComponent<HeadsAll>().UniSprite;
        _backBtnScript.Refresh();

        ChangeMenuList();
    }
    public void OnBackButtonClick()
    {
        if (ActiveMenuList == "heads")
        {
            ActiveMenuList = "shop";
        }
        else
        {
            ActiveMenuList = "heads";
        }

        ChangeMenuList();
    }
    void ChangeMenuList()
    {
        switch (ActiveMenuList)
        {
            case "shop":
                StartCoroutine(FadeAndSetActive(0));
                break;
            case "heads":
                StartCoroutine(FadeAndSetActive(1));
                //SetCurrentListActive(false, true, false);
                break;
            case "games":
                StartCoroutine(FadeAndSetActive(2));
                break;
            case "settings":
                StartCoroutine(FadeAndSetActive(3));
                break;
        }
        AudioManager.Instance.Play("LongTap");

        _backBtnScript.Refresh();
    }
    IEnumerator FadeAndSetActive(int id)
    {
        Fader.SetActive(true);
        while (_faderImg.color.a < 1)
        {
            _faderImg.color = new Color(_faderImg.color.r, _faderImg.color.g, _faderImg.color.b, _faderImg.color.a + 0.05f);
            yield return new WaitForSeconds(0.025f);
        }
        //MenuLists[0].SetActive(a);
        //MenuLists[1].SetActive(b);
        //MenuLists[2].SetActive(c);
        for (int i = 0; i < MenuLists.Count; i++)
        {
            MenuLists[i].SetActive(i == id ? true : false);
        }
        while (_faderImg.color.a > 0)
        {
            _faderImg.color = new Color(_faderImg.color.r, _faderImg.color.g, _faderImg.color.b, _faderImg.color.a - 0.05f);
            yield return new WaitForSeconds(0.025f);
        }
        Fader.SetActive(false);
        StopCoroutine(FadeAndSetActive(id));
    }
    public void OnPlayButtonClick()
    {
        int gameId = GamesPanel.CurrentGameId + 1;
        //SceneManager.LoadScene(gameId);
        StartCoroutine(LoadSceneAsync(gameId));
        AudioManager.Instance.Play("LongTap");

    }
    IEnumerator LoadSceneAsync(int gameId)
    {
        //if (!Fader.activeSelf)
        Fader.SetActive(true);

        AsyncOperation sceneLoad = SceneManager.LoadSceneAsync(gameId);

        while (!sceneLoad.isDone)
        {
            if (_faderImg.color.a < 1)
                _faderImg.color = new Color(_faderImg.color.r, _faderImg.color.g, _faderImg.color.b, _faderImg.color.a + 2*Time.deltaTime);
            yield return null;
        }
        GamesPanel.CurrentGameId = 0;
    }
}
