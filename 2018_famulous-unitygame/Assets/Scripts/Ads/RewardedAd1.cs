using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using GoogleMobileAds.Api;
using System;
using UnityEngine.SceneManagement;

public class RewardedAd1 : MonoBehaviour
{
    public static bool isDisabled;

    private RewardedAd rewardedAd;
    private RewardBasedVideoAd rewardedLegacy;
    private string adUnitId;
    public static int RewardId;
    void OnEnable()
    {
        MobileAds.Initialize(initStatus => { });
        if (isDisabled)
            return;


        adUnitId = "ca-app-pub-8971365310953313/3372036476";
        
        AdInit();

        //if (!isDisabled)
        //{
        //    //testad
        //    //adUnitId = "ca-app-pub-3940256099942544/5224354917";
        //    rewardedAd = new RewardedAd(adUnitId);
        //    AdRequest request;
        //    if (!rewardedAd.IsLoaded())
        //    {
        //        request = new AdRequest.Builder()
        //            .AddTestDevice("FB222B81D0D057D9")
        //            .Build();
        //        rewardedAd.LoadAd(request);
        //    }

        //    rewardedAd.OnAdClosed += HandeRewardAdClosed;
        //    rewardedAd.OnUserEarnedReward += HandeUserEarnedReward;
        //}
        //else
        //{
        //}
    }

    private void AdInit()
    {
        rewardedLegacy = RewardBasedVideoAd.Instance;
        AdRequest request = new AdRequest.Builder()
           // .AddTestDevice("FB222B81D0D057D9")
            .Build();
        rewardedLegacy.LoadAd(request, adUnitId);

        rewardedLegacy.OnAdClosed += HandeRewardAdClosed;
        rewardedLegacy.OnAdRewarded += HandeUserEarnedReward;
    }

    public void UserChoseToWatchAd()
    {
        //if (!isDisabled)
        //{
        //    if (rewardedAd.IsLoaded())
        //        rewardedAd.Show();

        //    return;
        //}

        if (rewardedLegacy.IsLoaded())
            rewardedLegacy.Show();


    }
    void HandeUserEarnedReward(object sender, EventArgs args)
    {
        if (RewardId == 0)
        {
            var GMInstance = GameObject.Find("GameManager").GetComponent<GameManager>();
            GMInstance.KeepGoing();
            GameManager.IsPaused = false;
            Time.timeScale = 1;
            KoUI.CanKeepGoing = false;
        }
        else if (RewardId == 1)
        {
            Time.timeScale = 1;
            PlayerPrefs.SetInt("ShouldGenerateLevelGeom", 1);
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
    void HandeRewardAdClosed(object sender, EventArgs args)
    {
        if (!rewardedLegacy.IsLoaded())
            AdInit();
    }
    void BackToMenu()
    {
        KoUI.ThisGO.SetActive(true);
    }
}
