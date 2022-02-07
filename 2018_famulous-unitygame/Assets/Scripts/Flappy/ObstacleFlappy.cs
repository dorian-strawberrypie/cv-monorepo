using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.Rendering.LWRP;

public class ObstacleFlappy : MonoBehaviour
{
    [SerializeField]
    public const float _spawnTime = 2;
    //can be set in unity??
    //other constants for other modes
    public float _spawnTimeLeft;
    public static Vector2 Scale = new Vector2(1,1);
    public Light2D light1, light2;
    public Color blue, gold;
    public static Color LightsColor;

    public static float Speed = 2.5f;
    public static bool AreMoving;


    private float _startY;
    float _transition = 1.3f;
    void Start()
    {


        _startY = transform.position.y;
        _transition *= Random.Range(0, 2) == 0 ? 1f : -1f;
        transform.localScale *= Scale;

    }


    protected virtual void Update()
    {
            light2.color = FlappyManager.Instance.Mode == 0 ? blue : Color.red;
            light1.color = FlappyManager.Instance.Mode == 0 ? blue : Color.red;

        if (FlappyManager.Instance.IsGameOn)
            transform.Translate(new Vector3(-Speed, 0) * Time.deltaTime, Space.World);
        if (AreMoving)
        {
            if (transform.position.y > _startY + 2.01f || transform.position.y < _startY - 2.01f)
            {
                transform.position = new Vector3(transform.position.x, _startY + (2 * _transition / Mathf.Abs(_transition)));
                _transition *= -1;
            }
            else
            transform.Translate(new Vector3(0, _transition) * Time.deltaTime, Space.World);

            if (transform.position.y < -5f)
                Destroy(gameObject);
        }
    }
}
