using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Swiper : MonoBehaviour
{

    private Collider2D _col;
    private Vector2 _point2;
    private Vector2 _point1;
    private bool _firstDown = true;
    public float TranslateSpeed = 500;

    private static Swiper _instance;
    public static Swiper Instance
    {
        get
        {
            if (_instance == null)
            {
                //Debug.LogWarning("Hop Manager NULL");
                _instance = GameObject.Find("BotPanel1").GetComponent<Swiper>();
            }
            return _instance;

        }
    }

    void Start()
    {
        _col = GetComponent<Collider2D>();
    }
    public float chosenMiniPosX;
    public static bool ShouldTranslate;
    void Update()
    {
        //        if (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began)
        //if (Input.GetMouseButtonDown(0))
        //{
        //    _point1 = Input.mousePosition;
        //}
        if (Input.GetMouseButton(0))
        {
            Vector2 touch = (Input.mousePosition);
            //Physics2D.OverlapPoint(touch)
            if (_col.OverlapPoint(touch))
            {

                _point1 = (Input.mousePosition);
                float shift = (_point1.x - _point2.x);
                if (_point2.x != 0 && !_firstDown)
                    transform.position += new Vector3(shift, 0);
                if (_point1.x != _point2.x)
                    HeadsAll.IsCoroutineActive = false;
                _point2 = _point1;
                _firstDown = false;
            }
        }
        else
        {
            _firstDown = true;
            _point2.x = 0;


            chosenMiniPosX = ChosenCollider.ChoosedHeadMini ? Camera.main.ScreenToWorldPoint(ChosenCollider.ChoosedHeadMini.transform.position).x : 0;
            TranslateSpeed = Mathf.Abs(chosenMiniPosX) * 400 * Time.deltaTime;
            if (!HeadsAll.IsCoroutineActive)
                transform.position = Vector3.MoveTowards(transform.position, new Vector3(Camera.main.WorldToScreenPoint(new Vector3()).x, transform.position.y), TranslateSpeed * 3);

        }
    }
  
}
