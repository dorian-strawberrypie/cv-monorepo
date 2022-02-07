using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class HeadsAll : MonoBehaviour, IPointerDownHandler, IPointerUpHandler
{
    public int Index;
    public string Name;
    public Sprite UniSprite;


    private float touchPosX;
    public static bool IsCoroutineActive;
    public void OnPointerDown(PointerEventData eventData)
    {
        touchPosX = Input.mousePosition.x;
    }
    public void OnPointerUp(PointerEventData eventData)
    {
        if (touchPosX == Input.mousePosition.x)
        {
            //Vector3 towards = Camera.main.WorldToScreenPoint(Camera.main.ScreenToWorldPoint(Swiper.Instance.transform.position) - Camera.main.ScreenToWorldPoint(transform.position)); //60 per 1
            //Swiper.Instance.transform.position = new Vector3(towards.x, Swiper.Instance.transform.position.y);
            StartCoroutine(MoveHead());
        }
    }
    IEnumerator MoveHead()
    {
        while (Mathf.Abs(Camera.main.ScreenToWorldPoint(transform.position).x) > 0.05)
        {
            IsCoroutineActive = true;
            //Swiper.Instance.chosenMiniPosX = Camera.main.ScreenToWorldPoint(transform.position).x;
            Vector3 towards = Camera.main.WorldToScreenPoint(Camera.main.ScreenToWorldPoint(Swiper.Instance.transform.position) - Camera.main.ScreenToWorldPoint(transform.position)); //60 per 1
            float TranslateSpeed = Mathf.Abs(Camera.main.ScreenToWorldPoint(transform.position).x) * 400 * Time.deltaTime;
            Swiper.Instance.transform.position = Vector3.MoveTowards(Swiper.Instance.transform.position, new Vector3(towards.x, Swiper.Instance.transform.position.y), TranslateSpeed * 6);
            
            yield return 0;
        }
            Debug.Log(ChosenCollider.ChoosedHeadMini);
            //Debug.Break();
            //IsCoroutineActive = false;
    }
}