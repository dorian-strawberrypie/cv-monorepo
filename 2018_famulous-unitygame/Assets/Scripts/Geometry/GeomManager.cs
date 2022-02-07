using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;
using TMPro;
using UnityEditor;
using UnityEngine;

public class GeomManager : GameManager
{
    private static GeomManager _instance;
    public static GeomManager Instance
    {
        get
        {
            if (_instance == null)
            {
                Debug.Log("Manager null"); //nestíhá?
                Debug.Break();
                _instance = new GeomManager();
            }

            return _instance;
        }
    }

    public GameObject[] Obstacles = { };
    public GameObject[] SubObstacles = { };
    public GameObject ObstaclesGameObject;
    public GameObject Player;
    public GameObject HeadGhost;
    public List<GameObject> ActiveObstacles = new List<GameObject>();
    public float LastEndPosition;

    private static int ScorePerBump;

    public List<SaveableGO> SaveableGOs = new List<SaveableGO>();
    public bool ShouldGenerateLevel
    {
        get
        {
            return PlayerPrefs.GetInt("ShouldGenerateLevelGeom", 1) == 0 ? false : true;
            //return false;
        }
    }

    void Start()
    {
        base.Start();
        KoUI.ScoreSaveName = "GeomScore";
        //Score = 1;
        ObstacleGeom.ActualColor = new Color(0, 0.08f, 1);

        _instance = this;
        ObstaclesGameObject = GameObject.Find("Obstacles");
        HeadGeom.OnBorderBump += OnBump;
        LastEndPosition = 2;

        possibleObstaclesByLevel = new List<int>();
        Level = PlayerPrefs.GetInt("GeomLevel", 1);
        Score = PlayerPrefs.GetInt("GeomScoreTemp", 0);
        _scoreText.text = Score.ToString("0");
        Debug.Log("Level " + Level);
        ScorePerBump = 10 * Level;
        GPUI.ScorePlus.text = "+" + ScorePerBump;
        //if (PlayerPrefs.GetString("LevelSaveGeom",null) == null || PlayerPrefs.GetString("LevelSaveGeom", null) == "")
        //    SetPossibleObstaclesByLevel();
        //else
        //{
        //    Destroy(ObstaclesGameObject);
        //    ObstaclesGameObject = LoadLevel();
        //}
        if (ShouldGenerateLevel)
            SetPossibleObstaclesByLevel();
        else
        {
            Destroy(ObstaclesGameObject);
            ObstaclesGameObject = LoadLevel();

        }
        KoUI.CanKeepGoing = true;
    }
    
    private void SaveLevel()
    {
        SaveableHolder sh = new SaveableHolder { GOsToBeSaved = SaveableGOs };
        string json = JsonUtility.ToJson(sh);
        PlayerPrefs.SetString("LevelSaveGeom", json);
    }
    private GameObject LoadLevel()
    {
        GameObject newObstaclesGO = new GameObject();
        newObstaclesGO.name = "Obstacles";

        string s = PlayerPrefs.GetString("LevelSaveGeom");
        List<SaveableGO> gameObjects = JsonUtility.FromJson<SaveableHolder>(s).GOsToBeSaved;
        foreach (var obstacle in gameObjects)
        {
            GameObject go = Instantiate(Obstacles[obstacle.PrefabId], new Vector3(obstacle.PositionX, obstacle.PositionY, obstacle.PositionZ), new Quaternion(), newObstaclesGO.transform);
            ActiveObstacles.Add(go);
            int id = (int)go.transform.position.z;
            if (id > 0)
                ActiveObstacles[id].GetComponent<ObstacleGeom>().IsFlipped = !ActiveObstacles[id - 1].GetComponent<ObstacleGeom>().IsFlipped;

            if (obstacle.Children == null)
                continue;
            foreach (var child in obstacle.Children)
            {
                Instantiate(SubObstacles[child.PrefabId], new Vector3(child.PositionX, child.PositionY, child.PositionZ), new Quaternion(child.QuaternionX, child.QuaternionY, child.QuaternionZ,0), go.transform);
            }
        }

        return newObstaclesGO;
    }
    private void ObstacleGeneration()//(bool fromStart)
    {
        int id = ActiveObstacles.Count;
        GameObject obj;
        int obstacleId = 0;
        //float randomIncrementY = 0;
        if (id == 0)
        {
            obj = Obstacles[0];
        }
        else
        {
            obstacleId = Random.Range(0, possibleObstaclesByLevel.Count);
            obj = Obstacles[possibleObstaclesByLevel[obstacleId]];
        }
        //obj = maxRandomObstacle == 1 ? Obstacles[1] : Obstacles[Random.Range(1, maxRandomObstacle+1)]; //+1
        while ((obj.GetComponent<Stairs>() && ActiveObstacles[id - 1].GetComponent<Stairs>()) ||
            (obj.GetComponent<Tunel>() && ActiveObstacles[id - 1].GetComponent<Tunel>() && ActiveObstacles[id - 2].GetComponent<Stairs>()) ||
            obj.GetComponent<Stairs>() && ActiveObstacles.Count == 1)
        {
            obstacleId = Random.Range(0, possibleObstaclesByLevel.Count);
            obj = Obstacles[possibleObstaclesByLevel[obstacleId]];
        }

        if (id != 0)
            LastEndPosition += 1;

        ActiveObstacles.Add(Instantiate(obj, new Vector3(0, obj.transform.localPosition.y + LastEndPosition + 1), obj.transform.rotation, ObstaclesGameObject.transform));

        if (id == 0) //if (fromStart)
            ActiveObstacles[id].transform.position = new Vector3(ActiveObstacles[id].transform.position.x, ActiveObstacles[id].transform.position.y, id);
        else
            ActiveObstacles[id].transform.position = new Vector3(ActiveObstacles[id].transform.position.x, ActiveObstacles[id].transform.position.y, ActiveObstacles[id - 1].transform.position.z + 1);

        if (id > 0) 
                ActiveObstacles[id].GetComponent<ObstacleGeom>().IsFlipped = !ActiveObstacles[id - 1].GetComponent<ObstacleGeom>().IsFlipped; //fkin late

        SaveableGOs.Add(new SaveableGO()
        {
            PrefabId = id == 0 ? 0 : obstacleId+ 1,
            PositionX = ActiveObstacles[id].transform.position.x,
            PositionY = ActiveObstacles[id].transform.position.y,
            PositionZ = ActiveObstacles[id].transform.position.z,
            
        });
    }
    public List<int> possibleObstaclesByLevel; //PO ŘADĚ
    async void SetPossibleObstaclesByLevel()
    {
        int toughness = Level;
        int obstacleCount = (toughness - 1) / 3 + 2;
        int mode = (toughness - 1) % 3;


        if(mode >= 0)
        {
            possibleObstaclesByLevel.Add(1);
            possibleObstaclesByLevel.Add(2);
        }
        if (mode >= 1)
            possibleObstaclesByLevel.Add(3);
        if (mode >= 2)
            possibleObstaclesByLevel.Add(4);

        while (ActiveObstacles.Count < obstacleCount + 1)
        {
            ObstacleGeneration();
        }
        await Task.Delay(1000);
        SaveLevel();
        PlayerPrefs.SetInt("ShouldGenerateLevelGeom", 0);
    }
    void OnBump()
    {
        Score += ScorePerBump;
        ScoreAnimator.SetTrigger("add");
        _scoreText.text = Score.ToString("0");
        if (ActiveObstacles[ActiveObstacles.Count - 1].transform.position.z <= 0)
        {
            PlayerPrefs.SetInt("GeomScoreTemp", (int)Score);
            PlayerPrefs.SetInt("GeomLevel", GeomManager.Level + 1);
            StartCoroutine(GPUI.NextLevel());
            PlayerPrefs.DeleteKey("LevelSaveGeom");
            PlayerPrefs.SetInt("ShouldGenerateLevelGeom", 1);
        }

        StartCoroutine(MoveWorldDown());
        foreach (GameObject obj in ActiveObstacles)
        {
            if (obj != null)
                obj.transform.position = new Vector3(obj.transform.position.x, obj.transform.position.y, obj.transform.position.z - 1);
        }
        //LastEndPosition -= decreaseBy;
    }
    IEnumerator MoveWorldDown()
    {
        float decreaseByTotal = 0;
        while (!HeadGeom.IsGrounded)
            yield return new WaitForSeconds(0.1f);

        float startWorldMovement = -1.5f;
        float decrementLeft = -(Player.transform.position.y - startWorldMovement);
        while (Player.transform.position.y > startWorldMovement)
        {
            //try putting decrementleft here
            float decreaseSpeed = -2*Time.deltaTime;//decrementLeft * Time.deltaTime * 2;
            //Player.transform.Translate(0, decreaseSpeed, 0);
            Player.transform.position += new Vector3(0, decreaseSpeed);
            foreach (GameObject obj in ActiveObstacles)
            {
                if (obj != null)
                    obj.transform.Translate(0,decreaseSpeed, 0);
            }
            decreaseByTotal += decreaseSpeed;
            yield return null;
        }
        LastEndPosition += decreaseByTotal;
    }
    
    void OnDestroy()
    {
        HeadGeom.OnBorderBump -= OnBump;
    }

    public void PauseGame(bool death)
    {
        if (death)
        {
            //HeadGeom.XVelocity = 0;
            HeadGeom.Rigid.simulated = false;
            PlayerPrefs.SetInt("GeomScoreTemp", 0);
        }
        base.PauseGame(death);
    }
    public RewardedAd1 RewardedAd;
    public void ReGenerate()
    {
        RewardedAd1.RewardId = 1;
        RewardedAd.UserChoseToWatchAd();
    }
}
 
