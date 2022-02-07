using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlideObstaclesHop : MonoBehaviour
{
    [SerializeField]
    private GameObject HeadGO;
    [SerializeField]
    private GameObject LavaGO;
    private float xStart;

    public static bool HasGameStarted;
    private void Start()
    {
        this.enabled = false;
        HasGameStarted = false;
    }

    void OnMouseDown()
    {
        HasGameStarted = true;
        HeadHop.HasStarted = true;
        xStart = (Input.mousePosition).x;
    }
    void OnMouseDrag()
    {
        xStart = Camera.main.ScreenToWorldPoint(new Vector2(xStart, 0)).x;
        float x2 = (Input.mousePosition).x;
        float movement = (Camera.main.ScreenToWorldPoint(new Vector2(x2, 0)).x - xStart) * 1.5f;

        HeadGO.transform.position -= new Vector3(movement, 0);
        LavaGO.transform.position -= new Vector3(movement, 0);
        transform.position -= new Vector3(movement, 0);
        
        xStart = x2;
    }
}
