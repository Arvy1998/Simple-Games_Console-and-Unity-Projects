using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class Group : MonoBehaviour {

    
    public bool isValidGridPos() {
        foreach (Transform child in transform) {
            Vector2 v = Grid.roundVec2(child.position);
            if (!Grid.insideBorder(v)) // ne viduje uz borderio
                return false;

            if (Grid.grid[(int)v.x, (int)v.y] != null &&
                Grid.grid[(int)v.x, (int)v.y].parent != transform)
                return false;
        }
        return true;
    }

    public void updateGrid() {
        for (int y = 0; y < Grid.h; ++y) // numetami nereikalingi objektai is grid'o
            for (int x = 0; x < Grid.w; ++x)
                if (Grid.grid[x, y] != null)
                    if (Grid.grid[x, y].parent == transform)
                        Grid.grid[x, y] = null;
        // nauji objektai i grid'a
        foreach (Transform child in transform) {
            Vector2 v = Grid.roundVec2(child.position);
            Grid.grid[(int)v.x, (int)v.y] = child;
        }
    }

    public void Start() {
        if (!isValidGridPos()) {
            Debug.Log("GAME OVER");
            Destroy(gameObject);
        }
    }

    public void Update() {
        // i kaire
        if (Input.GetKeyDown(KeyCode.LeftArrow)) {
            transform.position += new Vector3(-1, 0, 0);
            if (isValidGridPos())
                updateGrid();
            else
                transform.position += new Vector3(1, 0, 0);
        }

        // i desine
        else if (Input.GetKeyDown(KeyCode.RightArrow)) {
            transform.position += new Vector3(1, 0, 0);
            if (isValidGridPos())
                updateGrid();
            else
                transform.position += new Vector3(-1, 0, 0);
        }

        else if (Input.GetKeyDown(KeyCode.UpArrow)) { // sukinejimas
            transform.Rotate(0, 0, -90);
            if (isValidGridPos())
                updateGrid();
            else
                transform.Rotate(0, 0, 90);
        }

        else if (Input.GetKeyDown(KeyCode.DownArrow) ||
                 Time.time - lastFall >= 1) {
            transform.position += new Vector3(0, -1, 0);
            if (isValidGridPos()) {
                updateGrid();
            }
            else {
                transform.position += new Vector3(0, 1, 0);
                Grid.deleteFullRows();
                FindObjectOfType<Spawner>().spawnNext();
                enabled = false;
            }
            lastFall = Time.time;
        }
    }

    float lastFall = 0;
}
