using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using GoogleMobileAds.Api;
using System;
using UnityEngine.SceneManagement;

public class BreakAd : MonoBehaviour
{
    public static bool isDisabled;

    public InterstitialAd interstitial;
    private static float LastAdTime;
    private void OnEnable()
    {
        if (isDisabled)
            return;

        print("last ad time: " + (LastAdTime / 60) + " minutes");
        print("time now: " + (Time.realtimeSinceStartup / 60) + " minutes");


        float timeNow = Time.realtimeSinceStartup;
        float launchAdTime = 90f;
        if (timeNow - LastAdTime > launchAdTime)
        {
            RequestInterstitial();
            LastAdTime = timeNow;
        }
    }
    private void Start()
    {
        MobileAds.Initialize(initStatus => { });
        SceneManager.sceneLoaded += OnSceneLoad;
        SceneManager.sceneUnloaded += OnSceneUnload;
    }
    private void RequestInterstitial()
    {
#if UNITY_ANDROID
        string adUnitId = "ca-app-pub-8971365310953313/4493546457";

        //testad
        //string adUnitId = "ca-app-pub-3940256099942544/1033173712";
    #elif UNITY_IPHONE
            string adUnitId = "ca-app-pub-3940256099942544/4411468910";
    #else
            string adUnitId = "unexpected_platform";
    #endif

        // Initialize an InterstitialAd.
        this.interstitial = new InterstitialAd(adUnitId);


        // Create an empty ad request.
        AdRequest request = new AdRequest.Builder()
            //.AddTestDevice("FB222B81D0D057D9")
            .Build();
        // Load the interstitial with the request.
        this.interstitial.LoadAd(request);

        interstitial.OnAdClosed += HandleOnAdClose;
    }
    public void ShowBreakAd()
    {
        if (interstitial.IsLoaded())
        {
            interstitial.Show();
            print("showing break ad");
        }
        else
            Debug.LogError("NOT LOADED interstitial");
    }
    void HandleOnAdClose(object sender, EventArgs args)
    {
        interstitial.Destroy();
    }
    private void OnDestroy()
    {
        if (interstitial != null && interstitial.IsLoaded())
            interstitial.Destroy();
    }
    void OnSceneLoad(Scene scene, LoadSceneMode loadSceneMode)
    {
        DestroyReferences();
    }
    void OnSceneUnload(Scene scene)
    {
        DestroyReferences();
    }

    void DestroyReferences()
    {

        interstitial.Destroy();
        SceneManager.sceneLoaded -= OnSceneLoad;
        SceneManager.sceneUnloaded -= OnSceneUnload;
    }
}
