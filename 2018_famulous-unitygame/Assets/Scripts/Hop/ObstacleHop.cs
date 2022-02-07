using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObstacleHop : MonoBehaviour
{
    public static GameObject GameManager;
    public static GameObject AllObstacles;
    public static float HarderObstacleChanceDecrement;
    private List<GameObject> _possibleObjects= new List<GameObject>();

    public GameObject BoardPrefab;
    public GameObject CloudPrefab;
    public GameObject BoardSpikePrefab;
    public GameObject MovingBoardPrefab;
    public GameObject BarricadeBoardPrefab;

    public static int Test;

    private int _layer = 1 << 0;
    void Start()
    {

        if (!GameManager)
        {
            GameManager = GameObject.Find("GameManager");
        }
        if (!AllObstacles)
        {
            AllObstacles = GameObject.Find("AllObstacles");
        }

        DecideObstacle();

    }

    private void DecideObstacle()
    {
        var rayInfo = Physics2D.Raycast(transform.position - Vector3.right, Vector2.right, 2f, _layer);
        Debug.DrawRay(transform.position - Vector3.right, Vector2.right * 2);
        if (!rayInfo)
        {
            _possibleObjects.Add(BoardPrefab);
            _possibleObjects.Add(CloudPrefab);

            rayInfo = Physics2D.Raycast(transform.position, Vector2.down, 1.5f, _layer);
            Debug.DrawRay(transform.position - (Vector3.left * 0.4f), Vector2.down * 2.1f);
            var ray1 = Physics2D.Raycast(transform.position - (Vector3.right * 1.5f), Vector2.right, 3f, _layer);
            var ray2 = Physics2D.Raycast(transform.position - (Vector3.right * 0.4f), Vector2.down, 2.1f, _layer);
            var ray3 = Physics2D.Raycast(transform.position - (Vector3.left * 0.4f), Vector2.down, 2.1f, _layer);
            if (!rayInfo && (!ray1 || ray1.transform.name != "spikey_board(Clone)") && (!ray2 || ray2.transform.name != "barricadeBoard(Clone)") && (!ray3 || ray3.transform.name != "barricadeBoard(Clone)"))
                _possibleObjects.Add(BoardSpikePrefab);

            //rayInfo = Physics2D.Raycast(transform.position - (Vector3.right * 3), Vector2.right, 6f);
            //Debug.DrawRay(transform.position - (Vector3.right * 3), Vector2.right * 6f);
            //if (!rayInfo)
            //    _possibleObjects.Add(MovingBoardPrefab);

            float bbpRadius = 2;
            rayInfo = Physics2D.Raycast(transform.position - (Vector3.right * bbpRadius), Vector2.right, bbpRadius, _layer);
            ray1 = Physics2D.Raycast(transform.position, Vector2.down, 1.5f, _layer);
            Debug.DrawRay(transform.position - (Vector3.right * bbpRadius), Vector2.right * bbpRadius);
            if (!rayInfo && (!ray1 || ray1.transform.name != "barricadeBoard(Clone)"))
                _possibleObjects.Add(BarricadeBoardPrefab);

            GameObject newGO;

            //
            int harderObstaclesCount = _possibleObjects.Count - 2;
            float harderChance = (20f - HopManager.Level / 4f - HarderObstacleChanceDecrement); //1 z 25 je harder
            if (harderChance < 0)
                harderChance = 0;
            print("1 in " + harderChance + " is harder");
            if (harderObstaclesCount > 0)
            {
                if (Random.Range(1, (int)harderChance + 3) == 1)
                {
                    //print("possible obstacle[2]: " + _possibleObjects[2].name + ", possible obstacle[3]: " + _possibleObjects[3].name);
                    if (harderObstaclesCount == 2)
                        newGO = Instantiate(_possibleObjects[Random.Range(2, 4)], transform.position, new Quaternion(), AllObstacles.transform);
                    else
                        newGO = Instantiate(_possibleObjects[2], transform.position, new Quaternion(), AllObstacles.transform);
                }
                else
                    newGO = Instantiate(_possibleObjects[Random.Range(0, 2)], transform.position, new Quaternion(), AllObstacles.transform);
            }
            else
            {
                if (Random.Range(0, 4) == 0)
                    newGO = Instantiate(_possibleObjects[1], transform.position, new Quaternion(), AllObstacles.transform);
                else 
                    newGO = Instantiate(_possibleObjects[0], transform.position, new Quaternion(), AllObstacles.transform);
            }

            if (harderChance != 0)
                HarderObstacleChanceDecrement += 2.5f / harderChance;

            
            HopManager.LastObstacle = newGO;
        }
        Destroy(gameObject);
    }
}
