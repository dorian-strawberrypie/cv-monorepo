using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using TMPro;
using UnityEngine.SceneManagement;

public class HopManager : GameManager
{
    private static HopManager _instance;
    public static HopManager Instance
    {
        get
        {
            if (_instance == null)
            {
                //Debug.LogWarning("Hop Manager NULL");
                _instance = GameObject.Find("GameManager").GetComponent<HopManager>();
            }
            return _instance;

        }
    }
    public static bool ShouldWorldMove;
    //public bool startingTiles;

    public GameObject Head;
    public GameObject Obstacle;
    public GameObject FinishLine;
    public GameObject DragGO;

    public GameObject FirstObstacle;
    public static GameObject LastObstacle;

    private int _totalGeneratings; 
    void Start()
    {
        ObstacleHop.HarderObstacleChanceDecrement = 0;
        ShouldWorldMove = false;
        LastObstacle = FirstObstacle;
        base.Start();
        Score = PlayerPrefs.GetInt("HopScoreTemp", 0);
        KoUI.ScoreSaveName = "HopScore";
        Level = PlayerPrefs.GetInt("HopLevel", 1);
        _totalGeneratings = 10 + Level; //last = 
        KoUI.CanKeepGoing = true;
        print(Level);
    }


    void Update()
    {
        if (ShouldWorldMove)
        {
            MoveWorld();
            //startingTiles = true;
        }
        
        if (LastObstacle.transform.position.y <= 7f && _totalGeneratings > 0)
        {

            float posY = 4;
            if (LastObstacle != null)
                posY = LastObstacle.transform.position.y;
            //OldUpdateGenerating(posY);

                Generate(posY);
            //_lastObstaclePos.y = _lastObstacle.transform.position.y;
        }
        //else
            //print(LastObstacle + ":   " +LastObstacle.transform.position.y);
    }
    public void NextLevel()
    {
        ObstacleHop.HarderObstacleChanceDecrement = 0;
        KoUI.CanKeepGoing = true;
        PlayerPrefs.SetInt("HopLevel", Level + 1);
        PlayerPrefs.SetInt("HopScoreTemp", (int)Score);
        StartCoroutine(GPUI.NextLevel());
    }
    private void Generate(float posY)
    {
        _totalGeneratings--;

        if (_totalGeneratings == 0)
        {
            Instantiate(FinishLine, new Vector3(DragGO.transform.position.x, posY + 1.5f), new Quaternion(), DragGO.transform);
            return;
        }
        int yIncrement = Random.Range(0, 3);

        Camera cam = Camera.main;
        float worldWidth = cam.ScreenToWorldPoint(new Vector3(cam.pixelWidth, 0)).x * 2;
        float maxRight = new Vector3(worldWidth / 2 - 1f,0).x; //0.75
        float maxLeft = new Vector3(- worldWidth / 2 + 1f, 0).x;

        Instantiate(Obstacle, new Vector3(Random.Range(maxLeft, maxRight) + Head.transform.position.x, posY + yIncrement), new Quaternion());
        Instantiate(Obstacle, new Vector3(Random.Range(maxLeft, maxRight) + worldWidth / 1.5f + Head.transform.position.x, posY + yIncrement), new Quaternion());
        Instantiate(Obstacle, new Vector3(Random.Range(maxLeft, maxRight) - worldWidth / 1.5f + Head.transform.position.x, posY + yIncrement), new Quaternion());

    }

    public void MoveWorld()
    {
        GameObject[] obstacles = GameObject.FindGameObjectsWithTag("Obstacle");
        foreach (var obstacle in obstacles)
        {
            obstacle.transform.Translate(Vector3.down * 6 * Time.deltaTime);
        }
        Head.transform.Translate(Vector3.down  * 6 * Time.deltaTime);

        Score += Time.deltaTime * 5 * Level;
        _scoreText.text = Score.ToString("0");

    }
    private int _tempTempScore;
    public new void PauseGame(bool death)
    {
        if (death)
        {
            PlayerPrefs.SetInt("HopScoreTemp",0);
            HeadHop.Rigid.velocity = new Vector2();
            HeadHop.Rigid.simulated = false;
        }
        base.PauseGame(death);
    }
    public override void KeepGoing()
    {
        base.KeepGoing();
        HeadHop.Rigid.simulated = true;
    }
}
