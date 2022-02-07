using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tunel : ObstacleGeom
{
    public static float _obstVelocity;
    [SerializeField]
    private bool _headLanded;
    private float _flipper;
    private bool _wasLandedBefore;
    private bool _obstChanged;
    private float _baseHeadVelocity;

    private List<GameObject> _obstacles = new List<GameObject>();

    private const float _timerConst = 1.5f;
    private float _timer = 0;
    private bool _startTimer;

    [SerializeField]
    private GameObject _spikeBigger;
    [SerializeField]
    private GameObject _spikeSmaller;
    [SerializeField]
    private GameObject _box;
    [SerializeField]
    private GameObject _catapult;

    public GameObject _endlineCol;
    public SpriteRenderer Behind;
    void Awake()
    {
        if (!GeomManager.Instance.ShouldGenerateLevel)
            return;

        _baseHeadVelocity = HeadGeom.XVelocity ;
        EndPoint += 1f; //randdom 1 to 2?
        GeomManager.Instance.LastEndPosition += 0;
        //_endlineCol = transform.Find("endline").gameObject;
    }
    void Start()
    {
        base.Start();

        //if (!GeomManager.Instance.ShouldGenerateLevel)
        //    return;

        if (IsFlipped)
            _flipper = -1;
        else
            _flipper = 1;

        _endlineCol.SetActive(true);
        _endlineCol.transform.position = new Vector3(-0.5f * _flipper, _endlineCol.transform.position.y); //-

        _timer = 0;

    }
    
    void Update()
    {
        //Debug.Log("time: " + _timer);
        if (_headLanded)
        {
            _timer -= Time.deltaTime;
            if (_timer < 0)
            {
                _timer = _timerConst;

                float randomObst = Random.Range(0, 5);
                switch (randomObst)
                {
                    case 0:
                        _timer += 0.75f;
                        _obstacles.Add(Instantiate(_spikeSmaller, transform.position + new Vector3(_flipper * -3, -0.75f), Quaternion.Euler(0, 0, -90 * _flipper), transform)); //if needed use lastpos + x
                        _obstacles.Add(Instantiate(_box, transform.position + new Vector3(_flipper * -3.25f, -0.75f), new Quaternion(), transform));
                        _obstacles.Add(Instantiate(_box, transform.position + new Vector3(_flipper * -3.75f, -0.75f), new Quaternion(), transform));
                        _obstacles.Add(Instantiate(_box, transform.position + new Vector3(_flipper * -4.25f, -0.75f), new Quaternion(), transform));
                        if (Random.Range(0,2) == 0)
                            _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * -4.75f, -1f), Quaternion.Euler(0, 0, 0), transform));
                        else
                        {
                            _obstacles.Add(Instantiate(_box, transform.position + new Vector3(_flipper * -4.75f, -0.75f), new Quaternion(), transform));
                            _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * -4.75f, -0.5f), Quaternion.Euler(0, 0, 0), transform)); //make it easier

                        }

                        _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * -3.75f, 1.2f,1), Quaternion.Euler(0, 0, 180), transform));
                        break;

                    case 1:
                        int[] positions = new int[Random.Range(2, 4)]; //space
                        bool shouldBeBottom = false;
                        for (int i = 0; i < positions.Length; i++)
                        {
                            positions[i] = i;
                            if (Random.Range(0, 2) == 0 || shouldBeBottom)
                                _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * (-3f - (i * 1.125f)), -1.125f), Quaternion.Euler(0, 0, 0),transform));
                            else
                            {
                                _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * (-3f - (i * 1.125f)), 1f), Quaternion.Euler(0, 0, 180), transform));
                                shouldBeBottom = true;
                            }

                            _timer += 0.33f;
                        }
                        break;
                        
                    case 2:
                        _obstacles.Add(Instantiate(_catapult, transform.position + new Vector3(_flipper * -3f, -1f), new Quaternion(), transform));
                        _obstacles[_obstacles.Count - 1].transform.Find("collider").localPosition = new Vector3( - (0.05f * _flipper), 0, 0);
                        
                        if (Random.Range(0, 2) == 0)
                            _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * -3.8f, 1f), Quaternion.Euler(0, 0, 180), transform));
                        else
                            _obstacles.Add(Instantiate(_spikeBigger, transform.position + new Vector3(_flipper * -3.5f, -1f), new Quaternion(),transform));
                        break;
                }
                //Temp();
            }

        }

        foreach (var item in _obstacles)
        {

                item.transform.Translate(new Vector3(_obstVelocity, 0) * Time.deltaTime, Space.World);
            //if (!_headLanded)
            //    break;

            if (_obstChanged)
            {
                _obstChanged = false;
                break;
            }
            if (_flipper == 1 && item.transform.position.x > 5 || _flipper == -1 && item.transform.position.x < -5)
            {
                    Destroy(item);
                    _obstacles.Remove(item);
                    break;
            }
        }

    }
    void Temp()
    {
        foreach (var item in _obstacles)
        {
            item.transform.position = new Vector3(item.transform.position.x, item.transform.position.y - 1, item.transform.position.z);
        }
    }
    void OnCollisionEnter2D(Collision2D collision) 
    {
        if (transform.position.z == 0 && collision.collider.GetComponent<HeadGeom>() && !_headLanded && 
            collision.collider.GetComponent<HeadGeom>() && _endlineCol.activeInHierarchy)
        {
            StartCoroutine(FadeInOut(true));
            _headLanded = true;
            _obstVelocity = HeadGeom.XVelocity * 0.9f; //CRITICAL
            HeadGeom.XVelocity *= 0.1f;
        }
    }
    void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.gameObject.name == "Head" && _headLanded && collider.IsTouching(transform.Find("endline").GetComponent<Collider2D>()))
        {
            StartCoroutine(NormalizeHeadSpeed());
            _headLanded = false;
            _endlineCol.SetActive(false);

            Transform[] children = gameObject.GetComponentsInChildren<Transform>();
            _timer += 100;
        }
    }
    bool delayed;
    IEnumerator NormalizeHeadSpeed()
    {
        if (!delayed)
        {
            delayed = true;
            yield return new WaitForSeconds(2f);
        }
        HeadGeom.XVelocity *= 10;
        StartCoroutine(FadeInOut(false));
        //while (HeadGeom.XVelocity != _baseHeadVelocity)
        //{
        //    print("velociry set  " + HeadGeom.XVelocity);
        //    HeadGeom.XVelocity += _baseHeadVelocity * 0.1f * _flipper;
        //    yield return new WaitForSeconds(0.1f);
        //}
    }
    IEnumerator FadeInOut(bool start) //wtf board spikes again
    {
        while ((Behind.color.a != 0 && !start) || (Behind.color.a != 1 && start))
        {
            if (start)
            {
                Behind.color = new Color(Behind.color.r, Behind.color.g, Behind.color.b, Behind.color.a + 0.0625f);
            }
            else
            {
                Behind.color = new Color(Behind.color.r, Behind.color.g, Behind.color.b, Behind.color.a - 0.0625f);
            }

            yield return new WaitForSeconds(0.05f);

        }
    }
}
