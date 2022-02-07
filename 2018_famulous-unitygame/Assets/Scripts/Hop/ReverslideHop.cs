using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReverslideHop : MonoBehaviour
{
    private HeadHop _head;
    private BoxCollider2D _col;
    private float _scaleSpd;

    private float _baseScale = 0.8f;
    void Start()
    {
        _head = GameObject.Find("Head").GetComponent<HeadHop>();
        _col = GetComponent<BoxCollider2D>();

    }

    void OnTriggerEnter2D(Collider2D col) //---> bit
    {
        _head.Jump();
        Destroy(this.gameObject);
    }
    //void OnTriggerStay2D(Collider2D col) //---> reverslide
    //{
    //    _head.Jump();
    //    //_baseScale = _head.JumpVelocity - 0.2f;
    //    if (transform.localScale.y > 0 || _head.transform.position.y < transform.position.y + _col.bounds.extents.y) //není head nad/manší než 0
    //    {
    //        //if (_head.transform.position.y < transform.position.y + _col.bounds.extents.y)
    //        //{

    //        //}
    //            transform.localScale -= new Vector3(0, _baseScale) * Time.deltaTime; // 0.1
    //            transform.position += new Vector3(0, _baseScale / 2 * _col.size.y) * Time.deltaTime;
    //    }
    //    else
    //        Destroy(this.gameObject);


    //    //_baseScale *= 9/10
    //    //1/10 = x/9
    //    //0,8 = 0,9*x -> 9-0,8/0,9

    //}
}
