using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class SaveableGO
{
    public int PrefabId;

    public float PositionX;
    public float PositionY;
    public float PositionZ;

    public float QuaternionX;
    public float QuaternionY;
    public float QuaternionZ;

    public List<SaveableGO> Children;
}

[System.Serializable]
public class SaveableHolder
{
    public List<SaveableGO> GOsToBeSaved;
}
