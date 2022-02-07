using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class FlappyManager : GameManager
{
    private static FlappyManager _instance;
    public static FlappyManager Instance
    {
        get
        {
            if (_instance == null)
                return new FlappyManager();
            return _instance;
        }
    }
    public bool IsGameOn;
    public bool ShouldGenerate = false;
    public static float SpawnTime = 2f;
    private float _spawnTimeLeft = SpawnTime;


    public GameObject VerticalPipeObstacle;
    public GameObject Head;
    //public GameObject ObstacleGM4Cross;
    //public GameObject ObstacleGM2Cross;
    //public GameObject ObstacleGM1Snow;
    //public GameObject ObstacleGM3Head;


    public GameObject ObstacleBG;
    private ObstacleFlappy _obstacleScript;

    //timefor

    private GameObject _enemyHeadObject;
    private GameObject _lastObstacle;
    private bool _obstacleReady;


    public int GameMode; //vrtule, balls
    public float CurrentGameTime = 9;
    
    
    public float BasicGameChangeTime = 2f;

    private GameObject bgObstacle;

    public int ScorePerPass;

    public Animator LevelUpAnimator;
    public TextMeshProUGUI LevelText;
    public TextMeshProUGUI ScoreAddNumber;

    public int TotalObstacles;
    public int Mode;
    private int _modesCount = 6;
    void Start()
    {
        base.Start();
        IsPaused = false;
        KoUI.ScoreSaveName = "FlappyScore";
        //Score = PlayerPrefs.GetInt("FlappyScoreTemp",0);
        _instance = this;
        _obstacleScript = VerticalPipeObstacle.GetComponent<ObstacleFlappy>();
        _obstacleScript._spawnTimeLeft = ObstacleFlappy._spawnTime;
        CurrentGameTime = 9;
        GameMode = 0;

        Level = PlayerPrefs.GetInt("FlappyLevel", 1);
        ScorePerPass = Level * 10;
        TotalObstacles = Level;
        MakeLevel();
        Score = 0;
        _scoreText.text = "0";
    }
        float Scale = 2;
    void MakeLevel()
    {
        ScorePerPass = Level * 10;
        Head.transform.position = new Vector3(Head.transform.position.x, 0);
        //LevelText.gameObject.SetActive(false);
        int startModding = 2;
        float delayAfterNewLevel = 2f;
        ScoreAddNumber.text = "+" + ScorePerPass ;
        if (Level <= startModding)
            TotalObstacles = Level;
        else
        {
            TotalObstacles = (Level - 1 + 5)/5 + 1;//startModding + (Level - startModding) / 5;
            Mode = ((float)Level) % 5 == 0 ? ((Level / 5) % _modesCount + 1) : 0;
            print("Level:  " + Level);
            print("mode constant:  " + (((float)Level) % 5f));
        } 

        if (Mode != 0)
        {
            //HeadFlappy.PowerUpChange = true;
            
            switch (Mode)
            {
                case 1: //hi-gravity
                    Physics2D.gravity *= Scale;

                    Head.GetComponent<HeadFlappy>().VelocityY += Scale;

                    var cols = GetComponentsInParent<Collider2D>();
                    foreach (var item in cols)
                        item.enabled = false; //-> DISABLE THE OBSTACLE
                    break;

                case 2: //quicker
                    ObstacleFlappy.Speed += Scale;
                    break;

                case 3: //slowe
                    ObstacleFlappy.Speed /= Scale;
                    break;
                case 4: //moving obstacles
                    ObstacleFlappy.AreMoving = true;
                    cols = GetComponentsInParent<Collider2D>();
                    foreach (var item in cols)
                        item.enabled = false;
                    break;

                case 5: //tight obstacles
                    ObstacleFlappy.Scale = new Vector2(0.3f, 0.7f);
                    break;

                case 6: //bigger head
                    ObstacleFlappy.Scale = new Vector2(1f, 1.7f);
                    Head.transform.localScale *= 3;
                    break;
            }
        }
        float distanceBonus = Level % 5 == 0 ? 1 : 1 - (Level % 5) / 4;
        for (int i = 1; i < TotalObstacles + 1; i++)
        {
            _lastObstacle = Instantiate(VerticalPipeObstacle, new Vector2((delayAfterNewLevel - distanceBonus)+ (3.25f + distanceBonus) * i, Random.Range(3, -3)), new Quaternion(), this.transform);
            float scaleBonus = 0.5f / (1f + ((i - 1f)/ 5f));
            _lastObstacle.transform.localScale = new Vector3(_lastObstacle.transform.localScale.x, _lastObstacle.transform.localScale.y + scaleBonus);
        }
        
    }
    void NormalizeLevel()
    {
        try
        {
            switch (Mode)
            {
                case 1: //hi-gravity
                    Physics2D.gravity /= Scale;
                    Head.GetComponent<HeadFlappy>().VelocityY -= Scale;
                    break;

                case 2:
                    ObstacleFlappy.Speed -= Scale;
                    FlappyManager.SpawnTime = 2;
                    break;
                case 3:
                    ObstacleFlappy.Speed *= Scale;
                    break;
                case 4:
                    ObstacleFlappy.AreMoving = false;
                    break;
                case 5:
                    ObstacleFlappy.Scale = new Vector2(1, 1f);
                    break;
                case 6:
                    ObstacleFlappy.Scale = new Vector2(1f, 1f);
                    Head.transform.localScale /= 3;
                    break;

            }

        }
        catch { }
        Mode = 0;
    }

    void Update()
    {
        bool input = (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began || Input.GetKey(KeyCode.Space));
        if (!HeadFlappy.IsDead && input)
        {
            if (!IsGameOn)
            {
                ShouldGenerate = true;
                Head.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
            }
            IsGameOn = true;
        }
        if (!IsGameOn)
            return;

        //if (ShouldGenerate)
        //{
        //    GameObject obstacle = VerticalPipeObstacle;
        //    Instantiate(obstacle, new Vector2(3, Random.Range(3, -3)), new Quaternion(), this.transform);
        //    ShouldGenerate = false;
        //}


        //if (_spawnTimeLeft < 0 && _totalObstacles > 0)
        //{
        //    _spawnTimeLeft = SpawnTime;
        //    ShouldGenerate = true;
        //    _totalObstacles--;
        //}
        //else 
        if (TotalObstacles <= 0)
        {
            LevelText.gameObject.SetActive(true);
            LevelText.text = "Level " + (Level + 1);
            Rigidbody2D _rigid = Head.GetComponent<Rigidbody2D>();
            //if (!_rigid.freezeRotation)
                LevelUpAnimator.SetTrigger("levelUp");
            _rigid.freezeRotation = true;
            _rigid.bodyType = input ? RigidbodyType2D.Dynamic : RigidbodyType2D.Static;
            if (!input)// || LevelUpAnimator.)
                return;

            FlappyManager.Instance.AudioManager.Play("Harder");
            _rigid.freezeRotation = false;
            _spawnTimeLeft = SpawnTime;
            Level++;
            PlayerPrefs.SetInt("FlappyLevel", Level);
            NormalizeLevel();
            MakeLevel();
            //playerprefs
        }
        if (TotalObstacles != 0)
        {
            _spawnTimeLeft -= Time.deltaTime;
            if (!_lastObstacle)
                TotalObstacles = 0;
        }
        CurrentGameTime += Time.deltaTime;
        _scoreText.text = Score.ToString("0");

    }

    private void OnDestroy()
    {

        NormalizeLevel();
    }

    
    public new void PauseGame(bool death)
    {
        IsGameOn = false;
        base.PauseGame(death);
    }
    //private void Dementia()
    //{

        
        

    //    //if (HasHeadCollided)
    //    //{
    //    //    SceneManager.LoadScene("FlappyScene");
    //    //}

    //    CurrentGameTime -= Time.deltaTime;

    //    if (GameMode == 0) //FlappyBirb
    //    {
    //        _obstacleScript._spawnTimeLeft -= Time.deltaTime;
    //        if (_obstacleScript._spawnTimeLeft < 0)
    //        {
    //            _obstacleScript._spawnTimeLeft = global::ObstacleFlappy._spawnTime;
    //            IncrementFlappyObstacle(5);
    //        }
    //    }


    //    if ((bgObstacle == null || bgObstacle.transform.position.x < -1.77f) && IsGameOn)
    //    {
    //        bgObstacle = Instantiate(ObstacleBG, new Vector3(2.15f, -4.63f), new Quaternion(), this.transform);

    //    }

    //    if (GameMode == 1) //snow
    //    {
    //        if (_obstacleReady == false && GameObject.Find("obstacle_square(Clone)") == null)
    //        {
    //            CurrentGameTime = 9;
    //            _obstacleReady = true;
    //        }
    //        _obstacleScript._spawnTimeLeft -= Time.deltaTime;
    //        if (_obstacleScript._spawnTimeLeft < 0 && CurrentGameTime > 2)
    //        {
    //            _obstacleScript._spawnTimeLeft = 1;
    //            if (Random.Range(0, 2) == 0)
    //                Instantiate(ObstacleGM1Snow, new Vector3(Random.Range(1, 4), Random.Range(6, 9)), new Quaternion(), this.transform);
    //            else
    //                Instantiate(ObstacleGM1Snow, new Vector3(Random.Range(4, 7), Random.Range(6, 9)), new Quaternion(), this.transform);

    //        }
    //    }

    //    if (GameMode == 2) //cross
    //    {
    //        if (!_obstacleReady)
    //        {
    //            CurrentGameTime = CrossScriptFlappy.TimeAlive;
    //            if (GameObject.Find("Cross1") == null)
    //            {
    //                GameObject cross1 = Instantiate(ObstacleGM2Cross, new Vector3(7, 4), new Quaternion(), this.transform);
    //                cross1.name = "Cross1";
    //                GameObject cross2 = Instantiate(ObstacleGM2Cross, new Vector3(7, -4), new Quaternion(), this.transform);
    //                cross2.name = "Cross2";

    //            }
    //            _obstacleReady = true;
    //        }
    //    }

    //    if (GameMode == 3) //shooting heads
    //    {
    //        if (!_obstacleReady)
    //        {
    //            CurrentGameTime = EnemyHeadFlappy.TimeAlive;
    //            _enemyHeadObject = Instantiate(ObstacleGM3Head);
    //            _obstacleReady = true;
    //        }
    //    }

    //    if (GameMode == 4)
    //    {
    //        if (!_obstacleReady)
    //        {
    //            CurrentGameTime = 26f;
    //            _obstacleReady = true;
    //        }
    //        _obstacleScript._spawnTimeLeft -= Time.deltaTime;
    //        if (_obstacleScript._spawnTimeLeft < 0 && CurrentGameTime > 7)
    //        {
    //            Instantiate(ObstacleGM2Cross, new Vector3(Random.Range(4, 6), 0), new Quaternion(), this.transform);
    //            _obstacleScript._spawnTimeLeft = 2f;
    //        }

    //    }

    //    if (GameMode > 0 && CurrentGameTime < 0 && !IsInvoking("ChangeGameMode"))
    //    {
    //        Invoke("ChangeGameMode", BasicGameChangeTime);

    //        Debug.Log("universal change called");
    //    }
    //}

    //private void IncrementFlappyObstacle(int repeatCount)
    //{
    //    if (_baseObstaclesSpawned < repeatCount)
    //    {
    //        _baseObstaclesSpawned++;
    //        Instantiate(VerticalPipeObstacle, new Vector2(3, Random.Range(3, -3)), new Quaternion(), this.transform);
    //    }
    //    else if (_baseObstaclesSpawned >= repeatCount && !IsInvoking("ChangeGameMode"))
    //    {
    //        Debug.Log("change on flappy called");
    //        Invoke("ChangeGameMode", BasicGameChangeTime);
    //    }
    //}
}
