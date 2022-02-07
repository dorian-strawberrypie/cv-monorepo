using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GamesPanel : MonoBehaviour
{
    public List<GameObject> Games;
    public float TranslationSpeed = 1600;

    
    private Collider2D _col;
    private Vector2 _point2;
    private Vector2 _point1;
    private float _total;
    private bool _firstDown = true;
    [SerializeField]
    public static int CurrentGameId;

    void Start()
    {
        _col = GetComponent<Collider2D>();
    }

    void Update()
    {
        if (Input.GetMouseButton(0))
        {
            Vector2 touch = (Input.mousePosition);
            
            if (_col.OverlapPoint(touch))
            {

                _point1 = (Input.mousePosition);


                float shift = (_point1.x - _point2.x);
                if (_point2.x != 0 && !_firstDown)
                {

                    _total += shift;
                    transform.position += new Vector3(shift, 0);
                }

                _point2 = _point1;
                _firstDown = false;
            }
        }
        else if (!_firstDown)
        {
            //_firstDown = true;
            _point2.x = 0;

            int dragLengthToShift = 50;
            if (_total > dragLengthToShift)
            {
                //float translationX;
                //if (_total < _point1.x) //and current not max
                //    translationX = -1 * TranslationSpeed;
                //else
                //    translationX = 1 * TranslationSpeed;
                
                    Shift(-1);

            }
            else if (_total < -dragLengthToShift)
            {
                    Shift(+1);
            }
                    _firstDown = true;
                    _total = 0;

            if (Mathf.Abs(_total) < 300)
                Shift(0);
        }
        else
        {
            float chosenMiniPosX = Camera.main.ScreenToWorldPoint(Games[CurrentGameId].transform.position).x;
            if (Mathf.Abs(chosenMiniPosX) > 0.02f)
            {
                TranslationSpeed = Mathf.Abs(chosenMiniPosX) * 400;
                int neg = chosenMiniPosX > 0 ? -1 : 1;
                transform.Translate(Vector3.right * TranslationSpeed * Time.deltaTime * neg * 3);
            }
        }
    }

    void Shift(int Add)
    {

        if (CurrentGameId + Add < Games.Count && CurrentGameId + Add >= 0)
            CurrentGameId += Add;

        //float CurrentGamePosX = /*Camera.main.ScreenToWorldPoint(Games[CurrentGameId].transform.position).x;*/
        //print("GameID: " + CurrentGameId + ",  GamePos: " + CurrentGamePosX);
        
        //transform.position = new Vector3(_startPt + CurrentGameId * -_gameIconsDistance, transform.position.y);

    }
    //IEnumerator SetGamePosition() //NOT REFERENCE!!!!
    //{
    //    float currentX = Camera.main.ScreenToWorldPoint(Games[CurrentGameId].transform.position).x;
    //    print("crtn started");
    //    while (Mathf.Abs(currentX) > 0.1f)
    //    {
    //        int neg = currentX < 0 ? -1 : 1;
    //        print("GameID: " + CurrentGameId + ",  GamePos: " + currentX + ",  neg: " + neg);
    //        transform.Translate(Vector3.right * TranslationSpeed * Time.deltaTime * neg);
    //        yield return 0;
    //    }
    //}
}
