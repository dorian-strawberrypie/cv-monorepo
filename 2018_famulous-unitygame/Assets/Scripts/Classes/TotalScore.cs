using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class TotalScore : MonoBehaviour
{
    public static int TotalScores = 0;

    public static Dictionary<string, int> scores = new Dictionary<string, int>() {
        {"Flappy", 0},
    {"Geom", 0},
    {"Hop", 0}};

    void Start()
    {
        TotalScores = 0;
        scores["Flappy"] = PlayerPrefs.GetInt("FlappyScore");
        scores["Geom"] = PlayerPrefs.GetInt("GeomScore");
        scores["Hop"] = PlayerPrefs.GetInt("HopScore");

        foreach (var item in scores)
        {
            TotalScores += item.Value;
        }
        GetComponentInChildren<TextMeshProUGUI>().text = TotalScores.ToString();
    }
}
