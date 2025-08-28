using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class CubeController : MonoBehaviour
{
    [SerializeField] MessageController messageListener;

    [HideInInspector] public string lastMessage_array;
    [HideInInspector] public string rgbSolved;

    public GameObject obj;

    [HideInInspector] public Vector4 quaternion;
    private Vector4 smoothedQuaternion;
    [SerializeField, Range(0f, 1f)] private float smoothingFactor = 0.1f;

    [SerializeField] Texture Snake, Turtle, Snail, Fox, Chicken, Cat, Green;
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
        smoothedQuaternion = quaternion;
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

        smoothedQuaternion = Vector4.Lerp(smoothedQuaternion, quaternion, smoothingFactor);
        obj.transform.rotation = new Quaternion(smoothedQuaternion.w, smoothedQuaternion.x, smoothedQuaternion.z, smoothedQuaternion.y);

        if (rgbSolved == "s")
        {
            buttons[0].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            buttons[1].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            buttons[2].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            buttons[3].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            buttons[4].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            buttons[5].GetComponent<MeshRenderer>().materials[0].color = Color.green;
        }

        if (lastMessage_array == "s")
        {
            animalImage.texture = Green;
        }
    }
}
