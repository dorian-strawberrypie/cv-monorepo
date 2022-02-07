using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.Rendering.LWRP;

public class PowerUp : MonoBehaviour
{
    //powerups: chance in middle of obsts
    //+ hi-gravity mode
    //+ quick mode
    //+ slow mode
    //+ moving obstacles
    //+ closer&thinner obstacles
    //+ bigger head & space

    //+ mirror mode
    //+ reverse gravity
    //+ smaller head
    //+ horizontal obst. -> step going up&down, moving /w spaces

    public GameObject Head;
    public GameObject ObstacleInit; // not needed
    public GameObject Particles;
    public GameObject Sprite;
    public Light2D Light;
    private int buff = 0;
    
    public float Scale = 2;
    void Start()
    {
        ObstacleInit = GameObject.Find("ObstacleGenerator"); 
        Head = GameObject.Find("Head");
        //gameObject.SetActive(Random.Range(0, 3) != 0 ? true : false);
        if (FlappyManager.Instance.CurrentGameTime > 10f && Random.Range(0, 3) == 0)
            FlappyManager.Instance.CurrentGameTime = 0;
        else
            gameObject.SetActive(false);
        //GetComponentInChildren<SpriteRenderer>().color = Random.ColorHSV();
        //gameObject.SetActive(true);
        Destroy(gameObject, 8f);
    }
    
    void OnTriggerEnter2D(Collider2D col)
    {
        if (col.name == "Head")
        {
            //FlappyManager.Instance.GUIBoostAnimator.SetBool("isBoosting", true);
            Sprite.SetActive(false);
            Particles.SetActive(true);
            buff = Random.Range(1, 7);
            HeadFlappy.PowerUpChange = true;
            Light.enabled = false;
            FlappyManager.Instance.AudioManager.Play("Harder");
            switch (buff)
            {
                case 1: //hi-gravity
                    Physics2D.gravity *= Scale;

                    Head.GetComponent<HeadFlappy>().VelocityY += Scale;

                    var cols = GetComponentsInParent<Collider2D>();
                    foreach (var item in cols)
                        item.enabled = false; //-> DISABLE THE OBSTACLE
                    //Destroy(gameObject, 7f);
                    break;

                case 2: //quicker
                    ObstacleFlappy.Speed += Scale;
                    //ObstacleInit.transform.position -= new Vector3(2, 0);
                    //FlappyManager.SpawnTime = 3;
                    //Destroy(gameObject, 7f);
                    break;

                case 3: //slowe
                    ObstacleFlappy.Speed /= Scale;
                    //ObstacleInit.transform.position += new Vector3(1, 0);
                    //Destroy(gameObject, 8f);
                    break;
                case 4: //moving obstacles
                    ObstacleFlappy.AreMoving = true;
                    cols = GetComponentsInParent<Collider2D>();
                    foreach (var item in cols)
                        item.enabled = false;
                    //Destroy(gameObject, Random.Range(5f, 7f));
                    break;

                case 5: //tight obstacles
                    ObstacleFlappy.Scale = new Vector2(0.3f, 0.7f);
                    //Destroy(gameObject, Random.Range(5f, 7f));
                    break;

                case 6: //bigger head
                    ObstacleFlappy.Scale = new Vector2(1f, 1.7f);
                    Head.transform.localScale *= 3;
                    //Destroy(gameObject, Random.Range(6f, 7f));
                    break;
            }
            // hide, stop moving, DESTROY AFTER SOME TIME -> after that, revert changes
            //Destroy(this.gameObject);
        }
    }
    void OnDestroy()
    {
        if (buff != 0)
            Debuff();
    }

    private void Debuff()
    {
        //FlappyManager.Instance.ScorePerSecond /= 2;
        //FlappyManager.Instance.GUIBoostAnimator.SetBool("isBoosting", false);
        switch (buff)
        {
            case 1: //hi-gravity
                Physics2D.gravity /= Scale;
                Head.GetComponent<HeadFlappy>().VelocityY -= Scale;
                break;

            case 2:
                ObstacleFlappy.Speed -= Scale;
                FlappyManager.SpawnTime = 2;
                if (ObstacleInit != null)
                {
                    ObstacleInit.SetActive(false);
                    ObstacleInit.transform.position += new Vector3(2, 0);
                    ObstacleInit.SetActive(true);
                }
                break;
            case 3:
                ObstacleFlappy.Speed *= Scale;
                if (ObstacleInit != null)
                    ObstacleInit.transform.position -= new Vector3(1, 0);
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
            case 7:

                break;
            default:
                break;

        }
        if (buff > 0)
            HeadFlappy.PowerUpChange = true;
    }
}
