using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TempDisableAds : MonoBehaviour
{
    public List<Image> BtnColors = new List<Image>();
    public void DisableBanners()
    {
        BannerAd.isDisabled = !BannerAd.isDisabled;
        ColorBtn();
    }
    public void DisableRewardedAds()
    {
        RewardedAd1.isDisabled = !RewardedAd1.isDisabled;
        ColorBtn();
    }
    public void DisableBreakAds()
    {
        BreakAd.isDisabled = !BreakAd.isDisabled;
        ColorBtn();
    }
    private void Start()
    {
        ColorBtn();
    }
    private void ColorBtn()
    {
        if (BannerAd.isDisabled)
            BtnColors[0].color = Color.red;
        else
            BtnColors[0].color = Color.green;

        if (RewardedAd1.isDisabled)
            BtnColors[1].color = Color.red;
        else
            BtnColors[1].color = Color.green;

        if (BreakAd.isDisabled)
            BtnColors[2].color = Color.red;
        else
            BtnColors[2].color = Color.green;
    }
}
