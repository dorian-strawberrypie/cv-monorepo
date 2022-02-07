using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardSpk : ObstacleGeom
{
    public GameObject Spike;
    private EdgeCollider2D[] _colList;
    private EdgeCollider2D _col;
    void Awake()
    {
        _colList = GetComponentsInChildren<EdgeCollider2D>();
        if (!GeomManager.Instance.ShouldGenerateLevel)
            return;


        EndPoint += 2.5f;
        GeomManager.Instance.LastEndPosition += EndPoint;
    }
    void Start()
    {

        if (IsFlipped)
        {
            gameObject.GetComponent<SpriteRenderer>().flipX = true;
            _col = _colList[1];
            Destroy(_colList[0].gameObject);
        }
        else
        {
            _col = _colList[0];
            Destroy(_colList[1].gameObject);
        }
        if (!GeomManager.Instance.ShouldGenerateLevel)
        {
            foreach (Transform t in transform)
            {
                if (t.name == "spike(Clone)")
                    t.rotation = _col.transform.rotation;
            }

            base.Start();
            return;
        }


        int spikeCount = 4; // Random.Range(2, 5);
        int spikesActual = 0;
        Dictionary<int, bool> spaces = new Dictionary<int, bool>() {
            {1, false }, {2, false }, {3, false }, {4, false }, {5, false }//, {6, false }
        };
        while (spikeCount != spikesActual)
        {

            float rng = Random.Range(0, 5);

            foreach (var pos in spaces)
            {
                if (rng == pos.Key)
                {
                    if (pos.Value == false)
                    {
                        spikesActual++;

                        float p = 0.25f/6f + (1/6f * pos.Key); //když 1. aktivní, 2 ne 
                        if ((pos.Key == 2 && spaces[1] == true) || (pos.Key == 1 && spaces[2] == true))
                            break;
                        spaces[pos.Key] = true;
                        Instantiate(Spike, Vector3.Lerp(_col.transform.TransformPoint(_col.points[1]), _col.transform.TransformPoint(_col.points[0]), p), _col.transform.rotation, this.transform);
                    }
                    break;
                }
            }
        }
        base.Start();
    }
    //if flip, just solve col rotation
}
