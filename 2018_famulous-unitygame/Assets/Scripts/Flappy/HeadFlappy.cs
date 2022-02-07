using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.Rendering.LWRP;

public class HeadFlappy : HeadBase

{
    private Rigidbody2D _rigid;
    private Collider2D _col;
    public Cinemachine.CinemachineImpulseSource Impulse;

    public Sprite Spr;
    public float VelocityY = 7.5f;
    public float RotateVelocity;

    private float z;
    public static bool PowerUpChange;
    private float _timer;
    private int _timesBlicked;
    public static bool IsDead;

    public GameObject Particles;
    void Start()
    {
        IsDead = false;
        _rigid = GetComponent<Rigidbody2D>();
        _col = GetComponent<Collider2D>();
        RotateVelocity = 200;
        _rigid.constraints = RigidbodyConstraints2D.FreezeAll;
        _sprRen = GetComponentInChildren<SpriteRenderer>();
        _sprRen.sprite = Manager.HeadSprite == null ? Spr : Manager.HeadSprite;
        _sprRen.color = Color.white;
        PowerUpChange = false;
        isInPowerUp = false;
    }
    
    public static bool isInPowerUp = false;
    
    void Update()
    {

        Movement();

        if (FlappyManager.Instance.IsGameOn)
            Rotate();
        //else 

        //if (PowerUpChange)
        //{
        //    Color c = Color.yellow;
        //    _sprRen.color = Color.yellow;
        //    _timer += Time.deltaTime;
        //    _col.enabled = false;
        //    if (_timer > 0.25f)
        //    {
        //        if (_sprRen.color == Color.white)
        //            _sprRen.color = c;
        //        else
        //            _sprRen.color = Color.white;

        //        _timesBlicked += 1;
        //        _timer = 0;


        //    }
        //    if (_timesBlicked > 3)
        //    {
        //        isInPowerUp = !isInPowerUp;
        //        PowerUpChange = false;
        //        _timesBlicked = 0;
        //        if (isInPowerUp)
        //        {
        //            _sprRen.color = c;
        //            Particles.SetActive(true);
        //        }
        //        else
        //        {
        //            _sprRen.color = Color.white;
        //            Particles.SetActive(false);
        //        }
        //        _col.enabled = true ;
        //    }

        //}
   
 }
    public override void KeepGoing()
    {
        FlappyManager.Instance.IsGameOn = false;
        transform.position = new Vector2(transform.position.x, 1);
        IsDead = false;
        StartCoroutine(ActuallyKeepGoing());
    }
    private IEnumerator ActuallyKeepGoing()
    {
        while (!FlappyManager.Instance.IsGameOn)
            yield return 0;

        base.KeepGoing();
        //_rigid.bodyType = RigidbodyType2D.Static;
        _rigid.freezeRotation = false;
    }
    public void Ko()
    {
        if (_ignoreKO)
            return;

        FlappyManager.Instance.AudioManager.Play("Break");
        IsDead = true;
        _rigid.bodyType = RigidbodyType2D.Static;
        _rigid.freezeRotation = true;
        Impulse.GenerateImpulse();
        FlappyManager.Instance.PauseGame(true);
    }
    private void Movement()
    {
        //if (Input.GetKeyDown(KeyCode.Space))
        if (!IsDead && Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began || Input.GetKeyDown(KeyCode.Space))
        {
            FlappyManager.Instance.AudioManager.Play("Tap");
            _rigid.constraints = RigidbodyConstraints2D.None;
            _rigid.velocity = new Vector2(_rigid.velocity.x, VelocityY);
            RotateVelocity *= -1;
            
        }
    }

    private void Rotate()
    {
        z += (RotateVelocity * Time.deltaTime);
        transform.rotation = Quaternion.Euler(0, 0, z);
    }

    void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.gameObject.GetComponent<ObstacleFlappy>() || collider.gameObject.name == "Borders")//(collider.name != "ObstacleGenerator" && collider.name != "initCol")
            Ko();
        
    }
    private void OnTriggerExit2D(Collider2D collider)
    {
        if (collider.transform.name == "passCollider" && !IsDead)
        {
            FlappyManager.Instance.TotalObstacles--;
            FlappyManager.Instance.Score += FlappyManager.Instance.ScorePerPass;
            FlappyManager.Instance.ScoreAnimator.SetTrigger("add");
}
    }

}
