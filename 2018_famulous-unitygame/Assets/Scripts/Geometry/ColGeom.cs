using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ColGeom : MonoBehaviour
{
    private Transform _parent;
    private Collider2D _col;
    void Start()
    {
        HeadGeom.OnBorderBump += SetColActive;
        _col = GetComponent<Collider2D>();
        if (_col == null)
            _col = GetComponentInChildren<Collider2D>();

        if (transform.parent.parent.name == "Obstacles")
            _parent = transform.parent;
        else if (transform.parent.parent.parent.name == "Obstacles")
            _parent = transform.parent.parent;
        else
            Debug.LogWarning("_parent nor found!");

        SetColActive();
    }
    private void SetColActive()
    {
        if (_parent.position.z == 0)
            _col.enabled = true;
        else
            _col.enabled = false;
    }
    void OnDestroy()
    {
        HeadGeom.OnBorderBump -= SetColActive;
    }
}
