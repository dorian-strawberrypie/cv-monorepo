using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;

public class Scores : MonoBehaviour, IPointerDownHandler, IPointerUpHandler
{
    //public string ScoreSaveName;
    public string GameCodeName;
    private float _xStart;
    public static Manager MenuManager;
    void Start()
    {
        var TMPs = GetComponentsInChildren<TextMeshProUGUI>();
        TMPs[0].text = PlayerPrefs.GetInt(GameCodeName+"Score", 0).ToString();
        TMPs[1].text = "Level "+PlayerPrefs.GetInt(GameCodeName+"Level", 1);
        if (!MenuManager)
            MenuManager = GameObject.Find("MenuManager").GetComponent<Manager>();
    }
    public void OnPointerDown(PointerEventData eventData)
    {
        _xStart = Input.mousePosition.x;
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        
        if (eventData.position.x == _xStart)
            MenuManager.OnPlayButtonClick();
    }


}
