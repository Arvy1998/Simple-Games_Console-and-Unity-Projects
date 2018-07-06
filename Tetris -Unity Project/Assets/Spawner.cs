using UnityEngine;
using System.Collections.Generic;
using System.Collections;

public class Spawner : MonoBehaviour {
    public GameObject[] groups; // turesime daug objektu, dalyvaujanciu zaidime

    public void Start() {
        spawnNext(); // is kart pradejus zaidima, figuros pradeda kristi
    }

    public void spawnNext() {
        int i = Random.Range(0, groups.Length); // kvieciame figuras kristi random tvarka

        Instantiate(groups[i], // figura atsiranda tam tikroje pozicijoje
                    transform.position,
                    Quaternion.identity);
    }
    
}