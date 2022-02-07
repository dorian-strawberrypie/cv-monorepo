using Cinemachine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.Rendering.LWRP;
using UnityEngine.SceneManagement;

public class HeadHop : HeadBase
{
    public static Rigidbody2D Rigid;

    public Sprite Spr;
    public static float JumpVelocity;
    public const float HorizontalConst = 6;
    private float _horizontalVelocity;
    private Vector3 _scale;
    private float _scaleTime, _downTime;
    private bool _isTouchingBoard;
    private float _moveWorldPoint = -3.5f;
    [SerializeField]
    private GameObject _hoppedOn;
    public CinemachineVirtualCamera _cam;
    //public Light2D GlobalLight;
    public static bool HasStarted;
    private BoxCollider2D _col;
    void Start()
    {
        //Time.timeScale = 0;
        _sprRen = GetComponentInChildren<SpriteRenderer>();
        _sprRen.sprite = Manager.HeadSprite == null ? Spr : Manager.HeadSprite;
        _scale = transform.lossyScale;
        Rigid = GetComponent<Rigidbody2D>();

        JumpVelocity = 9f;
        _col = GetComponent<BoxCollider2D>();
        _col.enabled = false;

        Rigid.simulated = false;

        //_hoppedOn = new GameObject("Hopped on");
        _hoppedOn.transform.position = new Vector3(0, -4.25f);
    }
    public float AddSize, SubSize;
    void Update()
    {
        if (SlideObstaclesHop.HasGameStarted)
        {
            JumpLogic();
            transform.Translate(new Vector3(_horizontalVelocity * HorizontalConst, Rigid.velocity.y / 2) * Time.deltaTime); //why does it work??

            if (!_col.enabled)
            {
                _col.enabled = true;
                Rigid.simulated = true;
                lavaHop.Animator.enabled = true;
            }


            if (Rigid.velocity.y > 0)
            {
                _cam.m_Lens.OrthographicSize += (Rigid.velocity.y)/ AddSize;
                _downTime = 0;
            }
            else if (Rigid.velocity.y < 0.5f)//if orto > 5
            {
                _cam.m_Lens.OrthographicSize -= (_cam.m_Lens.OrthographicSize - 5) / SubSize;
                _downTime += Time.deltaTime;
                //if (_downTime > 0.8f)
                //{
                //    KoUI.CanKeepGoing = false;
                //    Ko();
                //    print("DOWNTIME DEATH");
                //    _downTime = 0;
                //}
            }
        }
    }

    private void JumpLogic()
    {
        if (_isTouchingBoard)
        {

            _scaleTime = Time.deltaTime * 4f;
            if (Rigid.velocity.y < 0 && transform.localScale.y - _scaleTime > 0.3f) 
            {
                transform.localScale += new Vector3(_scaleTime, -_scaleTime);
                //HopManager.ShouldWorldMove = false;
            }
            if (Rigid.velocity.y > 0 && transform.localScale.y < 0.8f)
            {
                transform.localScale += new Vector3(-_scaleTime, _scaleTime);
            }

        }
        else
        {
            if (_hoppedOn.transform.position.y > _moveWorldPoint)//(transform.position.y > -1.25f)
                HopManager.ShouldWorldMove = true;

            else //if (transform.position.y <= -1)
                HopManager.ShouldWorldMove = false;

            //print(_hoppedOn.transform.pos)
        }
        //if (transform.localScale.y < 0)
        //    Ko();
    }
    public void Jump()
    {
        HopManager.Instance.AudioManager.Play("Jump");
        Rigid.velocity = new Vector3(Rigid.velocity.x, JumpVelocity);
    }

    void OnTriggerEnter2D(Collider2D collider)
    {
        if (Rigid.velocity.y < -0.2f && collider.GetComponent<BoardHop>() != null)
        {
            _isTouchingBoard = true;
            //float invokeTime = 1 / Rigid.velocity.y * 0.2f;
            _scaleTime = 0;
            Rigid.velocity = new Vector3(Rigid.velocity.x, 0);
            Invoke("Jump", 0.05f);
            if (collider.GetComponent<CloudHop>())
                collider.GetComponent<CloudHop>().Destruction();

            _hoppedOn.transform.position = new Vector3(0, collider.transform.position.y);
            
        }
        
        if (collider.tag == "Spike" && !_ignoreKO)
        {
            Ko();
            if (collider.transform.name == "Lava")
                KoUI.CanKeepGoing = false;
            else
                print("SPIKE DEATH");

        }
        if (collider.transform.name == "finishLine(Clone)")
        {
            HopManager.Instance.NextLevel();
        }
    }
    
    void OnTriggerExit2D(Collider2D collider)
    {
        _isTouchingBoard = false;
        if (transform.localScale.y != _scale.y)
        {
            transform.localScale = new Vector3(_scale.x, _scale.y);
        }
    }
    public GameObject Particles;
    private void Ko()
    {
        HopManager.ShouldWorldMove = false;
        SlideObstaclesHop.HasGameStarted = false;
        Particles.SetActive(true);
        if (Particles.active)
            HopManager.Instance.AudioManager.Play("Break");
        _sprRen.enabled = false;
        HopManager.Instance.PauseGame(true);
    }
    public override void KeepGoing()
    {
        base.KeepGoing();
        _sprRen.enabled = true;
        SlideObstaclesHop.HasGameStarted = true;
        Particles.SetActive(false);
    }
}
