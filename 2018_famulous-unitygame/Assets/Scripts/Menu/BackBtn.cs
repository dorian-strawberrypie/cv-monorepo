using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class BackBtn : MonoBehaviour
{
    private TextMeshProUGUI _textMesh;
    private Image _circle;
    void Start()
    {
        _textMesh = GetComponentInChildren<TextMeshProUGUI>();
        //_circle = ... change image by whats active (<, shop icon)
        Refresh();   
    }

    public void Refresh()
    {
        //print("textmesh: " + _textMesh);
        switch (Manager.ActiveMenuList)
        {
            default:
                _textMesh.text = "BACK";
                break;
            case "heads":
                _textMesh.text = "SHOP";
                break;
            case "games":
                _textMesh.text = "HEADS";
                break;
        }
    }
}
