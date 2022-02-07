using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stairs : ObstacleGeom
{
    public GameObject StairPrefab;

    protected List<GameObject> _stairs = new List<GameObject>();
    [SerializeField]
    private float _flipper = 1;
    private List<Vector3> Positions = new List<Vector3>();
    protected void Start()
    {
        if (!GeomManager.Instance.ShouldGenerateLevel)
        {
            base.Start();
            foreach (Transform t in transform)
            {
                _stairs.Add(t.gameObject);
            }
            return;
            if (IsFlipped) //did it reversely xD
                _flipper = -1;
            else
                _flipper = 1;
        }

        GameObject lastObj = null;
        
        float x;
        //if (Random.Range(0, 2) == 0)
        //    x = 1.25f;
        //else
            x = 1.25f;

        if (IsFlipped) //did it reversely xD
            _flipper = -1;
        else
            _flipper = 1;

        //Debug.Log(",  flipper:" + _flipper + ", flipped: " + IsFlipped);
        lastObj = Instantiate(StairPrefab, new Vector3(x * _flipper, transform.position.y, gameObject.transform.position.z), new Quaternion(), this.transform);
        _stairs.Add(lastObj);

        int i = 0;
        while ((lastObj.transform.position.x > -1.25f && !IsFlipped)|| (lastObj.transform.position.x < 1.25f && IsFlipped))
        {
            i++;
            if (i > 15)
            { Debug.LogWarning("Stairs - while had more than 10 iterations"); break; }

            int mode = Random.Range(0, 4);

            if (lastObj.transform.position.x > 1 || lastObj.transform.position.y < _stairs[0].transform.position.y)
                mode = 0;

            float xInc = 0, yInc = 0;
            switch (mode)
            {
                case 0: //increasing
                    xInc = 1 * _flipper;
                    yInc = 1;
                    break;

                case 1: //decreasing nojump
                    xInc = 1 * _flipper;
                    yInc = -1;
                    break;

                case 2: //decreasing jump
                    xInc = 1.5f * _flipper;
                    yInc = -1;
                    break;

                case 3: //constant
                    xInc = 1.25f * _flipper;
                    yInc = 0;
                    break;
            }
            if (Mathf.Abs(lastObj.transform.position.x - xInc) > 2)
                continue;
            //Debug.Log(lastObj.transform.position.x + ",  flipper:" + _flipper + ",  xInc: " + xInc + ", flipped: " + IsFlipped);
            lastObj = Instantiate(StairPrefab, new Vector3(lastObj.transform.position.x - xInc, lastObj.transform.position.y + yInc, gameObject.transform.position.z), new Quaternion(), this.transform);
            _stairs.Add(lastObj);
            
        }
        EndPoint += lastObj.transform.localPosition.y - 0.5f;
        GeomManager.Instance.LastEndPosition += EndPoint;
        base.Start();
    } // IF PARENT Z != 0, subscriber!
    
}
