using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ChosenCollider : MonoBehaviour
{
    private float _scalePlus = 1.3f;
    public static GameObject ChoosedHeadMini;

    public static float enterPT, exitPT;

    public GameObject ChoosedHeadPrev;
    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.GetComponent<HeadsAll>())
        {
            if (ChoosedHeadMini)
            {
            AudioManager.Instance.Play("ShortTap");

            ChoosedHeadMini.transform.localScale *= 1 / _scalePlus;

            }

            ChoosedHeadMini = other.gameObject;


            ChoosedHeadMini.transform.localScale *= _scalePlus;
            ChoosedHeadPrev.GetComponentInChildren<Image>().sprite = ChoosedHeadMini.GetComponent<HeadsAll>().UniSprite;

            //ChoosedHeadPrev.transform.localScale *= 1 / _scalePlus;

            enterPT = ChoosedHeadMini.transform.parent.parent.position.x;
            ChoosedHeadPrev.GetComponent<ChosenHeadGO>().OnHeadChange();
        }
    }

    void OnTriggerExit2D(Collider2D other)
    {
        if (other.gameObject.GetComponent<HeadsAll>())
        {

            //ChoosedHeadMini.transform.localScale *= 1 / _scalePlus;
            exitPT = ChoosedHeadMini.transform.parent.parent.position.x;
        }
    }
    //Camera.main.ScreenToWorldPoint(ChoosedHeadMini.transform.position))
    
}
