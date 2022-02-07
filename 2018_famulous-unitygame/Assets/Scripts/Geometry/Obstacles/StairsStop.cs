using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StairsStop : Stairs
{
    private List<float> _startYs = new List<float>();
    private float _yVelocity = 2.5f;
    private bool _shouldReverse;
    private Vector3 _lastCollided;
    void Start()
    {
        base.Start();

        foreach (var obj in _stairs)
        {
            _startYs.Add(obj.transform.localPosition.y);
        }
        
    }

    void Update()
    {
        for (int i = 0; i < _stairs.Count; i++)
        {
            if (i % 2 == 1)
            {
                SwitchY(i);
                _stairs[i].transform.Translate(new Vector2(0, _yVelocity) * Time.deltaTime);
            }
            else
            {
                SwitchY(i);
                _stairs[i].transform.Translate(new Vector2(0, -_yVelocity) * Time.deltaTime);
            }
        }
    }

    private void SwitchY(int i)
    {
        if (_stairs[i].transform.localPosition.y < _startYs[i] + 1 && _stairs[i].transform.localPosition.y > _startYs[i] - 1)
            _shouldReverse = true;
        else if (_stairs[i].transform.localPosition.y > _startYs[i] + 1 && _shouldReverse)
        {
            _yVelocity *= -1;
            _shouldReverse = false;
        }
        else if (_stairs[i].transform.localPosition.y < _startYs[i] - 1 && _shouldReverse)
        {
            _yVelocity *= -1;
            _shouldReverse = false;
        }
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.gameObject.name == "Head")
        {
            if (_lastCollided.x != collision.otherCollider.transform.position.x)
                HeadGeom.ShouldMove = false;

            _lastCollided = collision.otherCollider.transform.position;

            //collision.otherCollider.transform.Translate(0, _yVelocity * Time.deltaTime, 0);
         }
    }

    //void OnCollisionStay2D(Collision2D collision)
    //{
    //    if (collision.collider.gameObject.name == "Head")
    //    {
    //        collision.otherRigidbody.velocity = new Vector2(0, 0);
    //        collision.otherCollider.transform.Translate(0, _yVelocity * Time.deltaTime, 0);
    //    }
    //}
}
