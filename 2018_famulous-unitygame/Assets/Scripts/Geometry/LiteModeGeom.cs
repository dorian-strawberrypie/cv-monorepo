using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.Rendering.PostProcessing;
using UnityEngine.UI;

public class LiteModeGeom : MonoBehaviour
{
    public PostProcessLayer PPL;
    public TextMeshProUGUI LiteModeBtn;
    private static bool _isLite
    {
        get
        {
            return PlayerPrefs.GetInt("GeomLite", 0) == 0 ? false : true;
        }
    }
    private void Start()
    {
        //PPL.enabled = _isLite ? false : true;
    }
    public void OnLiteModeButtonClick()
    {
        if (PPL.enabled)
        {
            PPL.enabled = false;
            LiteModeBtn.text = "ON";
            PlayerPrefs.SetInt("GeomLite", 1);
            //_isLite = true;
        }
        else
        {
            PPL.enabled = true;
            LiteModeBtn.text = "OFF";
            PlayerPrefs.SetInt("GeomLite", 0);
            //_isLite = false;
        }
        PlayerPrefs.Save();
    }
}
