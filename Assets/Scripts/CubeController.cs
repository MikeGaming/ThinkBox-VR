using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class CubeController : MonoBehaviour
{
    [SerializeField] MessageController messageListener;

    [HideInInspector] public string lastMessage_array;

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
        StartCoroutine(SendText("$" + s));
    }

    IEnumerator SendText(string text)
    {
        yield return new WaitForSeconds(5f);
        messageListener.SendTextData(text);
        StopAllCoroutines();
    }


    private void Update()
    {
        //Debug.Log(messageListener.lastMessage);
        if (lastMessage_array == "Snake") animalImage.texture = Snake;
        else if (lastMessage_array == "Turtle") animalImage.texture = Turtle;
        else if (lastMessage_array == "Snail") animalImage.texture = Snail;
        else if (lastMessage_array == "Fox") animalImage.texture = Fox;
        else if (lastMessage_array == "Chicken") animalImage.texture = Chicken;
        else if (lastMessage_array == "Cat") animalImage.texture = Cat;


    }
}
