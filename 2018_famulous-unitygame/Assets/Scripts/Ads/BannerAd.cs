using UnityEngine;
using GoogleMobileAds.Api;
using UnityEngine.SceneManagement;
using System.Collections;

public class BannerAd : MonoBehaviour {

    public static bool isDisabled;

    private BannerView bannerView;
    public string AdUnitId;
    public bool IsBottom;
    private bool isInitialized;
    private AdPosition _adPos { get
        {
            return IsBottom ? AdPosition.Bottom : AdPosition.Top;
        } }
    public void Start()
    {
        AdInit();
        SceneManager.sceneLoaded += OnSceneLoad;
        SceneManager.sceneUnloaded += OnSceneUnload;
        bannerView.OnAdFailedToLoad += OnAdFailedToLoad;
        isInitialized = true;
    }
    public void OnEnable()
    {
        if (!isInitialized)
            AdInit();
    }

    private void AdInit()
    {
        if (isDisabled)
            return;

        ////TEST
        //AdUnitId = "ca-app-pub-3940256099942544/6300978111";

        //if (IsBottom)
        AdUnitId = "ca-app-pub-8971365310953313/7885482897";
        //else
        AdUnitId = "ca-app-pub-8971365310953313/8582884255";

#if UNITY_ANDROID
        string appId = "ca-app-pub-8971365310953313~8774455947";
#elif UNITY_IPHONE
            string appId = "ca-app-pub-3940256099942544~1458002511";
#else
            string appId = "unexpected_platform";
#endif

        // Initialize the Google Mobile Ads SDK.
        MobileAds.Initialize(appId);

        RequestBanner();
    }

    private void RequestBanner()
    {
#if UNITY_ANDROID
        string adUnitId = AdUnitId;
#elif UNITY_IPHONE
            string adUnitId = "ca-app-pub-3940256099942544/2934735716";
#else
            string adUnitId = "unexpected_platform";
#endif

        if (bannerView != null)
            bannerView.Destroy();

        // Create a 320x50 banner at the top of the screen.
        bannerView = new BannerView(adUnitId, AdSize.Banner, _adPos);

        AdRequest request = new AdRequest.Builder()
            //.AddTestDevice("FB222B81D0D057D9")
            .Build();
        bannerView.LoadAd(request);
    }

    public void OnAdFailedToLoad(object sender, AdFailedToLoadEventArgs args)
    {
        Invoke("AdInit", 1f);
    }
    private void OnDestroy()
    {
        DestroyReferences();
    }
    private void OnDisable()
    {
        DestroyReferences();
    }
    private void OnBecameInvisible()
    {
        DestroyReferences();

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

        bannerView.OnAdFailedToLoad -= OnAdFailedToLoad;
        bannerView.Destroy();
        SceneManager.sceneLoaded -= OnSceneLoad;
        SceneManager.sceneUnloaded -= OnSceneUnload;

        Destroy(gameObject);
    }
}