using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class HeadGeom : HeadBase
{
    public Sprite Spr;
    public static Rigidbody2D Rigid;
    [SerializeField]
    private GameObject _particles;

    public static float XVelocity;
    public float JumpVelocity;
    public float GravityScale = 4; //8??

    public delegate void BorderBumpAction();
    public static event BorderBumpAction OnBorderBump;
    
    public static bool IsGrounded;
    public static bool ShouldMove;
    private Vector3 _horizontalDir = new Vector3();

    private float _time; // test

    public GameObject HeadGhost;
    //Jump = 0.5 sec
    void Start()
    {
        _sprRen = GetComponentInChildren<SpriteRenderer>();
        _sprRen.sprite = Manager.HeadSprite == null ? Spr : Manager.HeadSprite;

        Rigid = GetComponent<Rigidbody2D>();

        Physics2D.gravity *= GravityScale;
        XVelocity = 2.083f;     // TO BE RELATIVIZED
        JumpVelocity = Mathf.Sqrt(-2f * Physics2D.gravity.y * 1.5f);
        ShouldMove = false;

        //_ignoreKO = true;
    }

    void Update()
    {
        _time -= Time.deltaTime;
        if (((Input.touchCount > 0) || Input.GetKey(KeyCode.S)) && IsGrounded)
        {
            Rigid.velocity = new Vector3(Rigid.velocity.x, JumpVelocity);
            ShouldMove = true;

            GeomManager.Instance.AudioManager.Play("Jump");
        }

        if (ShouldMove && !_particles.activeSelf)
        {
            //print(_horizontalDir.normalized * XVelocity + " " + Time.deltaTime);
            transform.Translate(_horizontalDir.normalized * XVelocity * Time.deltaTime, Space.World);
        }


        if (Input.GetKeyDown(KeyCode.R)) //transform.position.y < -5 || 
        {
            SceneManager.LoadScene("GeometryScene");
        }

        RaycastHit2D ray = Physics2D.Raycast(transform.position, Vector2.down, 0.5f);
        if (!ray)
            IsGrounded = false;
        else
            IsGrounded = true;
    }

    void FixedUpdate()
    {
        Rigid.velocity = new Vector3(0, Rigid.velocity.y); //x -> 0 if transform mvmt
        if (transform.position.y < -6)
        {
            KoUI.CanKeepGoing = false;
            Ko();
        }
        
    }

    private void Ko()
    {
        GeomManager.Instance.AudioManager.Play("Break");
        _sprRen.gameObject.SetActive(false);
        _particles.SetActive(true);
        GeomManager.Instance.PauseGame(true);
    }
    public override void KeepGoing()
    {
        //GeomManager.Instance.PauseGame(false);
        _sprRen.gameObject.SetActive(true);
        HeadGeom.Rigid.simulated = true;
        _particles.SetActive(false);
        ShouldMove = true;
        _horizontalDir = (LastCol.transform.rotation * Vector2.right);
        transform.rotation = LastCol.transform.rotation;
        //_ignoreKO = true;


        base.KeepGoing();
    }

    string previousBorder = "";
    void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.tag == "border" && collider.name != previousBorder)
        {
            Rigid.velocity = new Vector3(Rigid.velocity.x, JumpVelocity); // + _rigid.velocity.y * 0.5f);

            OnBorderBump?.Invoke();

            if ((XVelocity < 0 && transform.position.x > 0) || (XVelocity > 0 && transform.position.x < 0))
                XVelocity *= -1;

            previousBorder = collider.name;
        }
        if (collider.transform.parent != null && collider.transform.parent.name == "catapult(Clone)")
            Rigid.velocity = new Vector3(Rigid.velocity.x, JumpVelocity);
        //when lands -> normalize if needed
        if (((collider.tag == "Spike"  && !(Rigid.velocity.y > 0)) || collider.name == "spikeT2(Clone)") && !_ignoreKO)
        {
            Ko();
        }
        //if (collider.transform.name == "FinishLine" && collider.transform.position.z == 0)
        //{
        //    PlayerPrefs.SetInt("GeomLevel", GeomManager.Instance.Level + 1);
        //    StartCoroutine(GeomManager.Instance.GPUI.NextLevel());
        //}
    }
    Collider2D LastCol;
    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.tag != "border" && collision.collider.tag != "Spike") //NORMALIZE VELOCITY, HIGHER DIFFICULTY
        {
            LastCol = collision.collider;

            _horizontalDir = (collision.transform.rotation * Vector2.left);
            transform.rotation = collision.transform.rotation;
            
            
            //IsGrounded = true;

        }
        if (collision.collider.tag == "border")
            collision.collider.transform.GetComponent<SpriteRenderer>().color = ObstacleGeom.ActualColor;
    }
    
    void OnCollisionExit2D(Collision2D collision)
    {
        //IsGrounded = false;
        _time = 0;
        //Debug.Break();
        if (collision.collider.tag == "border")
            collision.collider.transform.GetComponent<SpriteRenderer>().color = Color.white;
    }
    void OnDestroy()
    {
        Physics2D.gravity = new Vector2(0, -9.8f);
    }
}

//TODO:
//stairs move after touchdown
// more obstacles
//implement speed increasement