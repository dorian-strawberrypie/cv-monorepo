using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyHeadFlappy : MonoBehaviour
{
    public GameObject SquareBullet;
    public GameObject TriangleBullet;
    public GameObject Player;

    [SerializeField]
    public static float TimeAlive = 16f;

    private const float _cooldownTime = 1f;
    private float _cooldownLeft;

    private float _activeTime = 15f;

    private float _savedY;
    private bool _isReady;
    void Start()
    {
        Player = GameObject.FindWithTag("Player");
        _cooldownLeft = _cooldownTime;
        Destroy(this.gameObject, TimeAlive);    //destroy flappymanager var- change here too
        _savedY = 0;
    }
    
    void Update()
    {
        if (_activeTime < 0)
        {
            transform.Translate(Vector3.right * 3f * Time.deltaTime);
            return;
        }
        if (transform.position.x > 2.3f)
        {
            transform.Translate(Vector3.left * 3f * Time.deltaTime);
            return;
        }
        _cooldownLeft -= Time.deltaTime;
        _activeTime -= Time.deltaTime;
        //like it came from beyond
        if (Player.transform.position.y - transform.position.y != 0)
            transform.Translate(new Vector3(0, Player.transform.position.y - transform.position.y) * Time.deltaTime, Space.World);
        if (_cooldownLeft < 0)
        {
            Instantiate(TriangleBullet, new Vector3(transform.position.x, transform.position.y), new Quaternion(), FlappyManager.Instance.transform);
            _cooldownLeft = _cooldownTime;
        }

        if (Mathf.Abs(_savedY - transform.position.y) > 1.5f)
        {
            Instantiate(SquareBullet, new Vector3(transform.position.x, transform.position.y), new Quaternion(), FlappyManager.Instance.transform);
            _savedY = transform.position.y;
        }
    }
}
