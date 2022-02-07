using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.Rendering.LWRP;

public class ObstacleGeom : MonoBehaviour
{
    public float EndPoint;
    private List<SpriteRenderer> _sprRens = new List<SpriteRenderer>();

    private List<Light2D> _lights = new List<Light2D>();

    Color clr;
    private List<Color> _baseColors = new List<Color>() { Color.red, Color.green, Color.yellow};//{ new Color32(255, 53, 94, 255), new Color32(255, 96, 55,255), new Color32(255, 153, 51, 255), new Color32(255, 255, 102,255), new Color32(102, 255, 102,255), new Color32(170, 240, 209,255), new Color32(80, 191, 230,255)};
    private static int _colorId;
    [SerializeField]
    public bool IsFlipped;
    public static Color ActualColor; //static
   

    protected void Start()
    {
        int mode = PlayerPrefs.GetInt("GeomLevel", 1) % 3; //lv 1 - 1, lv 2 - 2, lv 3 - 0 -> list{red, green, orange}
        ActualColor = _baseColors[mode];

        HeadGeom.OnBorderBump += Coloring;

        var sprRen = GetComponent<SpriteRenderer>();
        if (sprRen)
        {
            _sprRens.Add(sprRen);
        }
        foreach (var item in GetComponentsInChildren<SpriteRenderer>())
        {
            if (item.name != "behind")
                _sprRens.Add(item);
        }

        if (GeomManager.Instance.ShouldGenerateLevel)
        {

            List<SaveableGO> children = new List<SaveableGO>();
            foreach (Transform t in transform)
            {
                if (t.name == "spike(Clone)")
                    children.Add(new SaveableGO() { PrefabId = 0, PositionX = t.position.x, PositionY = t.position.y, PositionZ = t.position.z, QuaternionX = t.rotation.x, QuaternionY = t.rotation.y, QuaternionZ = t.rotation.z, });
                if (t.name == "stair(Clone)")
                    children.Add(new SaveableGO() { PrefabId = 1, PositionX = t.position.x, PositionY = t.position.y, PositionZ = t.position.z, QuaternionX = t.rotation.x, QuaternionY = t.rotation.y, QuaternionZ = t.rotation.z, });
            }
            if (children.Count > 0)
            {
                GeomManager.Instance.SaveableGOs[(int)transform.position.z].Children = new List<SaveableGO>();
                GeomManager.Instance.SaveableGOs[(int)transform.position.z].Children = children;
            }

        }

        Coloring();
    }
    private void Coloring() //MODIFY LIGHT2d COLOR
    {
        try
        {
            float alpha;
            switch (transform.position.z)
            {
                case 1:
                    alpha = 0.66f;
                    break;
                case 0:
                    alpha = 1f;
                    break;
                default:
                    alpha = 0.33f;
                    break;
            }
            foreach (var item in _sprRens)
            {
                item.color = new Color(ActualColor.r, ActualColor.g, ActualColor.b, alpha);
            }

        }
        catch
        {
            HeadGeom.OnBorderBump -= Coloring;
        }

    }
    private void ModifyTransparency()
    {
        try
        {
            foreach (var item in _lights)
            {
                
                switch (transform.position.z)
                {
                    case 0:
                        item.intensity = 1f;
                        item.lightOrder = -5;
                        break;

                    case 1:
                        item.intensity = 0.8f;
                        break;

                    case 2:
                        item.intensity = 0.4f;
                        break;

                    default: //case -1
                        item.intensity = 0.8f;

                        //var sprRens = item.transform.parent.GetComponentsInChildren<SpriteRenderer>();
                        //float a = 0.25f;
                        //foreach (var sprite in sprRens)
                        //{
                        //    sprite.color = new Color(sprite.color.r, sprite.color.g, sprite.color.b, a);
                        //}

                        break;
                }
                //if (transform.position.z == 0 || transform.position.z == 1)
                //{
                //    item.intensity = 1;
                //}
                //else
                //{
                //    item.intensity = 0.2f;
                //}
                //if (item.transform.parent.parent.name == "BoardSpkObstacle(Clone)")
                //    item.lightOrder = -(int)transform.position.z;
                //else
                if (item.transform.position.z >= 0)
                    item.lightOrder = -Mathf.Abs((int)transform.position.z);
            }
            //if (transform.position.z == 0 || transform.position.z == 1)
            //{
            //    //for (int i = 0; i < _sprRens.Count; i++)
            //    //{
            //    //    if (gameObject.name != "mid")
            //    //        _sprRens[i].color = _baseColors[i];
            //    //}
            //}
            //else
            //{
            //    for (int i = 0; i < _sprRens.Count; i++)
            //    {
            //        if (gameObject.name != "mid")
            //            _sprRens[i].color = new Color(_sprRens[i].color.r, _sprRens[i].color.g, _sprRens[i].color.b, 0.25f);//clr;
            //    }
            //}
            //Debug.Log("pos: " + transform.position.z + "    obj:" + gameObject.name + "   alpha:" + _sprRens[0].color.a);
        }
        catch
        {
            HeadGeom.OnBorderBump -= ModifyTransparency;
        }
    }
    void OnDestroy()
    {
        HeadGeom.OnBorderBump -= ModifyTransparency;
    }
}
