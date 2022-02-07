using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeadBase : MonoBehaviour
{
    protected SpriteRenderer _sprRen;
    protected bool _ignoreKO = false;

    public virtual void KeepGoing()
    {
        _ignoreKO = true; //model
        StartCoroutine(KeepGoingEnum());
    }
    IEnumerator KeepGoingEnum()
    {
        int _timesBlicked = 0;
        while (_timesBlicked < 6)
        {
            if (_sprRen.color == Color.white)
            {
                _sprRen.color = Color.red;
            }
            else
            {
                _sprRen.color = Color.white;
            }
            _timesBlicked++;
            yield return new WaitForSeconds(0.25f);
        }
        _ignoreKO = false;

    }
}
