using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrossScriptFlappy : ObstacleFlappy
{
    public Vector3 PositionA;
    public Vector3 PositionB;
    private Vector3 _startPosition;

    private float _rotationZ = 0;
    private Vector3 _moveTo;
    [SerializeField]
    private float _xSpd = 2.75f;

    public static float TimeAlive = 25f;
    void Start()
    {
        _startPosition = transform.position;
        _spawnTimeLeft = TimeAlive - 5; //time to go awae 

        if (FlappyManager.Instance.GameMode == 2)
        {
            if (this.gameObject.name == "Cross1")
                PositionA = new Vector3(2, 4);
            else
                PositionA = new Vector3(-2, -4);
        }
        if (FlappyManager.Instance.GameMode == 4)
        {
            PositionA = new Vector3(this.transform.position.x, Random.Range(-1, 5));
            PositionB = new Vector3(this.transform.position.x, PositionA.y - 3);
            TimeAlive = 13;
        }
        Destroy(this.gameObject, TimeAlive);
    }


    protected override void Update()
    {
        _rotationZ += (350 * Time.deltaTime);
        transform.rotation = Quaternion.Euler(0, 0, _rotationZ);

        if (FlappyManager.Instance.GameMode == 2)
        {
            _spawnTimeLeft -= Time.deltaTime;

            if (_spawnTimeLeft < 0)
            {
                transform.Translate(Vector3.left * Time.deltaTime, Space.World);
                return;
            }

            if (transform.position == _startPosition)
            {
                _moveTo = PositionA;
            }
            else if (transform.position == PositionA)
            {
                PositionB = new Vector3(-transform.position.x, Random.Range(-4, 5));
                _moveTo = PositionB;
            }
            else if (transform.position == PositionB) //Y only
                _moveTo = PositionA;

            transform.position = Vector3.MoveTowards(transform.position, _moveTo, 2.5f * Time.deltaTime);

        }
        
        else if (FlappyManager.Instance.GameMode == 4)
        {
            //base.Update();

            if (transform.position.y == _moveTo.y)
            {
                _moveTo = new Vector3(transform.position.x - _xSpd * 0.8f , PositionB.y);
                Debug.Log("_moveto = PosB");
            }
            if (transform.position.y == _moveTo.y || transform.position == _startPosition)
            {
                _moveTo = new Vector3(transform.position.x - _xSpd * 0.8f, PositionA.y);
                Debug.Log("_moveto = PosA   ");
            }
           /// transform.Translate(new Vector3(-2.5f * Time.deltaTime, 0), Space.World);
            transform.position = Vector3.MoveTowards(transform.position, _moveTo, (_xSpd * 1.25f) * Time.deltaTime);
            //transform.position = Vector3.MoveTowards(transform.position, transform.position + new Vector3(-0.05f, 0), 2.5f * Time.deltaTime);
            //Debug.Log(_moveTo + "    " + transform.position);
        }

    }
}
