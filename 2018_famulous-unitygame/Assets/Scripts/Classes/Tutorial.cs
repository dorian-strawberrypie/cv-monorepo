using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tutorial : MonoBehaviour
{
    public string SceneName;
    public Animator Animator;
    void Start()
    {
        
        switch (SceneName)
        {
            case "flappy":
                Animator.Play("hand_tap", 0);
                break;

            case "hop":
                Destroy(gameObject, 5f);
                Animator.Play("hand_side-to-side", 0);
                break;

            case "geometry":
                Animator.Play("hand_touch-and-hold", 0);
                Animator.Play("text_enabled", 1);
                break;

            default:
                break;
        }
                //Destroy(this.gameObject, 5f);
    }
    private void OnMouseDown()
    {
        Destroy(gameObject);
    }

}
