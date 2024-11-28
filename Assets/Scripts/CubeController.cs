using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CubeController : MonoBehaviour
{
    [SerializeField] MessageListener messageListener;

    [SerializeField] Texture Snake, Turtle, Snail, Fox, Chicken, Cat;
    [SerializeField] RawImage animalImage;

    [SerializeField] GameObject[] buttons;

    private void Start()
    {
        string s = "";
        for (int i = 0; i < buttons.Length; i++)
        {
            Color color = Color.black;
            int r = Random.Range(0, 3);
            switch (r)
            {
                case 0: color = Color.red; break;
                case 1: color = Color.blue; break;
                case 2: color = Color.magenta; break;
            }
            buttons[i].GetComponent<MeshRenderer>().materials[0].color = color;
            s += r;
        }
        messageListener.SendTextData("$" + s);
    }


    private void Update()
    {
        if (messageListener.lastMessage == "Snake") animalImage.texture = Snake;
        else if (messageListener.lastMessage == "Turtle") animalImage.texture = Turtle;
        else if (messageListener.lastMessage == "Snail") animalImage.texture = Snail;
        else if (messageListener.lastMessage == "Fox") animalImage.texture = Fox;
        else if (messageListener.lastMessage == "Chicken") animalImage.texture = Chicken;
        else if (messageListener.lastMessage == "Cat") animalImage.texture = Cat;


    }
}
