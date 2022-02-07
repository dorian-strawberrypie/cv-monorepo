using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObstacleInit : MonoBehaviour
{
    private bool IsColliderRelevant(Collider2D col)
    {
        return col.name == "initCol" ? true : false;
    }
    void Start()
    {
        
    }

    //void OnTriggerEnter2D(Collider2D col)
    //{
    //    if (!IsColliderRelevant(col))
    //        return;
    //    print(FlappyManager.Instance.CurrentGameTime);        
    //}
    void OnTriggerExit2D(Collider2D col)
    {
        if (!IsColliderRelevant(col))
            return;

        FlappyManager.Instance.ShouldGenerate = true;

        print(col.gameObject.transform.position.x);
    }
    //  posunout o mezeru mezi obsts.
}
