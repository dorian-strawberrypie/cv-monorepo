using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardHop : MonoBehaviour
{

    private bool _shouldReverse;
    public bool HasSideSpikes, Movable, IsSecondObstacle;

    public float _start;
    private float _xVelocity ;
    void Start()
    {
        _start = this.transform.position.x;
        
        Transform right = transform.Find("right");
        Transform left = transform.Find("left");
        
        if (left != null && right != null)
        {
            left.gameObject.SetActive(false);
            right.gameObject.SetActive(false);
            

            if (HasSideSpikes)
            {
                if (Random.Range(0, 2) == 0)
                    right.gameObject.SetActive(true);
                else
                    left.gameObject.SetActive(true);
            }
        }

        if (IsSecondObstacle)
            transform.position = new Vector3(Random.Range(-1f, 1f), transform.position.y);
        //if (!_hasSideSpikes && Random.Range(0, 3) == 0)
        //{
        //    _xVelocity = Random.Range(1f, 2f);
        //    _movable = true;
        //}
        if (_start + 2 > 2) //start -= 2
        {
            _start -= 2;
            _xVelocity *= -1;
        }
    }
    
    void Update()
    {

        if (Movable)
        {
            transform.Translate(new Vector3(_xVelocity, 0) * Time.deltaTime);
            //only if is _lastObstacle
            //if (transform.position.x) //mezi
            if (!_shouldReverse && transform.position.x > _start && transform.position.x < _start + 2)
                _shouldReverse = true;
            if (_shouldReverse && (transform.position.x < _start || transform.position.x > _start + 2))
            {
                _shouldReverse = false;
                _xVelocity *= -1;
            }
            //}
            //else
            //{
            //    if (transform.position.x > _start || transform.position.x < _start - 2)
            //        _xVelocity *= -1;
            //}

        }
    }
    
    
}