using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class ChosenHeadGO : MonoBehaviour
{
    public TextMeshProUGUI HeadName;

    public float RotationSpeed, ScaleSpeed;

    public void OnHeadChange()
    {
        var ChosenHead = ChosenCollider.ChoosedHeadMini.GetComponent<HeadsAll>();
        
            HeadName.text = ChosenHead.Name;
        
    }

}
